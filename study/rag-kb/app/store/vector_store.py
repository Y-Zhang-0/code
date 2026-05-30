"""ChromaDB 向量存储封装，含文本分块与 bge-m3 嵌入。"""
import uuid
from typing import List, Dict, Any

import chromadb
from langchain_core.documents import Document
from langchain.text_splitter import RecursiveCharacterTextSplitter
from langchain_community.embeddings import HuggingFaceBgeEmbeddings
from langchain_chroma import Chroma

from app.core.config import get_settings


def _build_embedding(cfg):
    """构造 bge-m3 多语言嵌入模型。"""
    return HuggingFaceBgeEmbeddings(
        model_name=cfg.model,
        model_kwargs={"device": cfg.device},
        encode_kwargs={"normalize_embeddings": cfg.normalize},
    )


def _build_splitter(cfg):
    return RecursiveCharacterTextSplitter(
        chunk_size=cfg.chunk_size,
        chunk_overlap=cfg.chunk_overlap,
        # 支持中文句号、问号等作为分隔符
        separators=["\n\n", "\n", "。", "！", "？", ".", "!", "?", " ", ""],
    )


class VectorStore:
    """封装 ChromaDB 的增删查操作。"""

    def __init__(self):
        settings = get_settings()
        self._vs_cfg = settings.vector_store
        self._emb_cfg = settings.embedding
        self._spl_cfg = settings.splitter

        self._embedding = _build_embedding(self._emb_cfg)
        self._splitter = _build_splitter(self._spl_cfg)

        self._store = Chroma(
            collection_name=self._vs_cfg.collection,
            embedding_function=self._embedding,
            persist_directory=self._vs_cfg.persist_dir,
        )

    def add_documents(self, docs: List[Document], doc_id: str) -> int:
        """分块并存储文档，返回分块数量。"""
        chunks = self._splitter.split_documents(docs)
        for chunk in chunks:
            chunk.metadata["doc_id"] = doc_id
        ids = [str(uuid.uuid4()) for _ in chunks]
        self._store.add_documents(chunks, ids=ids)
        return len(chunks)

    def search(self, query: str, top_k: int = None) -> List[Document]:
        """语义相似度检索，返回 Top-K 文档片段。"""
        k = top_k or self._vs_cfg.top_k
        return self._store.similarity_search(query, k=k)

    def delete_document(self, doc_id: str) -> None:
        """按 doc_id 删除所有相关分块。"""
        collection = self._store._collection
        results = collection.get(where={"doc_id": doc_id})
        if results["ids"]:
            collection.delete(ids=results["ids"])

    def list_documents(self) -> List[Dict[str, Any]]:
        """返回已存储的文档元数据列表（去重 doc_id）。"""
        collection = self._store._collection
        results = collection.get(include=["metadatas"])
        seen: Dict[str, Dict] = {}
        for meta in results["metadatas"]:
            doc_id = meta.get("doc_id")
            if doc_id and doc_id not in seen:
                seen[doc_id] = {
                    "doc_id": doc_id,
                    "source": meta.get("source", ""),
                    "file_path": meta.get("file_path", ""),
                }
        return list(seen.values())


# 单例
_store_instance: VectorStore | None = None


def get_vector_store() -> VectorStore:
    global _store_instance
    if _store_instance is None:
        _store_instance = VectorStore()
    return _store_instance
