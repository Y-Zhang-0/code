"""统一文档加载器，封装 LangChain 多格式加载器。"""
from pathlib import Path
from typing import List

from langchain_core.documents import Document
from langchain_community.document_loaders import (
    PyPDFLoader,
    Docx2txtLoader,
    TextLoader,
    UnstructuredMarkdownLoader,
    UnstructuredExcelLoader,
    CSVLoader,
)


_LOADERS = {
    ".pdf": PyPDFLoader,
    ".docx": Docx2txtLoader,
    ".md": UnstructuredMarkdownLoader,
    ".txt": TextLoader,
    ".xlsx": UnstructuredExcelLoader,
    ".xls": UnstructuredExcelLoader,
    ".csv": CSVLoader,
}


def load_document(file_path: str) -> List[Document]:
    """根据文件扩展名选择对应加载器，返回 Document 列表。"""
    path = Path(file_path)
    suffix = path.suffix.lower()
    loader_cls = _LOADERS.get(suffix)
    if loader_cls is None:
        raise ValueError(f"不支持的文件类型: {suffix}")

    # TextLoader 需指定编码，避免中文乱码
    if loader_cls is TextLoader:
        loader = loader_cls(str(path), encoding="utf-8")
    else:
        loader = loader_cls(str(path))

    docs = loader.load()
    # 补充来源元数据
    for doc in docs:
        doc.metadata.setdefault("source", path.name)
        doc.metadata.setdefault("file_path", str(path))
    return docs
