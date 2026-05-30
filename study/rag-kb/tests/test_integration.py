"""集成测试 — 覆盖核心验收标准及边界场景。

所有 langchain/chromadb 等重型依赖在 sys.modules 中提前 mock，
测试无需真实模型即可运行。

运行方式（在 rag-kb 目录下）：
    pytest tests/ -v
"""
import sys
import io
import types
from unittest.mock import MagicMock, AsyncMock, patch, call
import pytest

# ──────────────────────────────────────────────
# 在任何 app 模块导入前 mock 重型依赖
# ──────────────────────────────────────────────

def _make_mod(*parts):
    """递归创建伪模块并注入 sys.modules。"""
    name = ""
    for part in parts:
        name = f"{name}.{part}" if name else part
        if name not in sys.modules:
            sys.modules[name] = MagicMock()
    return sys.modules[name]


_heavy = [
    "langchain", "langchain.text_splitter",
    "langchain_core", "langchain_core.documents",
    "langchain_community",
    "langchain_community.document_loaders",
    "langchain_community.embeddings",
    "langchain_chroma",
    "chromadb",
    "sentence_transformers",
    "FlagEmbedding",
    "pypdf", "docx2txt", "openpyxl", "unstructured",
]
for _m in _heavy:
    _make_mod(*_m.split("."))

# Document 类需要可实例化
class _FakeDocument:
    def __init__(self, page_content="", metadata=None):
        self.page_content = page_content
        self.metadata = metadata or {}

sys.modules["langchain_core.documents"].Document = _FakeDocument

# RecursiveCharacterTextSplitter mock
class _FakeSplitter:
    def __init__(self, **kwargs): pass
    def split_documents(self, docs):
        return docs  # 直接返回，不分块

sys.modules["langchain.text_splitter"].RecursiveCharacterTextSplitter = _FakeSplitter

# HuggingFaceBgeEmbeddings mock
sys.modules["langchain_community.embeddings"].HuggingFaceBgeEmbeddings = MagicMock

# Chroma mock
class _FakeChroma:
    def __init__(self, **kwargs):
        self._data = {}  # doc_id -> [chunk]
        self._collection = _FakeCollection()
    def add_documents(self, docs, ids=None): pass
    def similarity_search(self, query, k=5): return []

class _FakeCollection:
    def get(self, where=None, include=None):
        return {"ids": [], "metadatas": []}
    def delete(self, ids): pass

sys.modules["langchain_chroma"].Chroma = _FakeChroma

# Loaders mock
for _loader in [
    "PyPDFLoader", "Docx2txtLoader", "TextLoader",
    "UnstructuredMarkdownLoader", "UnstructuredExcelLoader", "CSVLoader",
]:
    setattr(sys.modules["langchain_community.document_loaders"], _loader, MagicMock)

# ──────────────────────────────────────────────
# 现在可以安全导入 app 模块
# ──────────────────────────────────────────────

from app.core.config import Settings, get_settings
from app.loader.document_loader import load_document, _LOADERS
from app.llm.factory import get_llm
from app.llm.ollama import OllamaLLM
from app.llm.cloud import CloudLLM
from app.main import app
from fastapi.testclient import TestClient


# ──────────────────────────────────────────────
# Fixtures
# ──────────────────────────────────────────────

@pytest.fixture(scope="module")
def mock_vs():
    vs = MagicMock()
    vs.add_documents.return_value = 5
    vs.list_documents.return_value = []
    vs.search.return_value = []
    vs.delete_document.return_value = None
    return vs


@pytest.fixture(scope="module")
def mock_engine():
    eng = MagicMock()
    eng.query = AsyncMock(return_value={
        "answer": "这是测试回答",
        "sources": [{"source": "test.txt", "doc_id": "abc", "content": "片段内容"}],
    })
    return eng


@pytest.fixture(scope="module")
def upload_dir(tmp_path_factory):
    return str(tmp_path_factory.mktemp("uploads"))


@pytest.fixture(scope="module")
def client(mock_vs, mock_engine, upload_dir):
    settings = Settings()
    settings.upload.dir = upload_dir

    fake_doc = _FakeDocument(page_content="测试内容", metadata={"source": "test.txt"})

    with patch("app.api.routes.get_vector_store", return_value=mock_vs), \
         patch("app.api.routes.get_rag_engine", return_value=mock_engine), \
         patch("app.api.routes.get_settings", return_value=settings), \
         patch("app.api.routes.load_document", return_value=[fake_doc]):
        yield TestClient(app), mock_vs, mock_engine


# ──────────────────────────────────────────────
# AC1: 文档上传
# ──────────────────────────────────────────────

class TestAC1_DocumentUpload:
    @pytest.mark.parametrize("filename,content_type", [
        ("sample.txt", "text/plain"),
        ("sample.md", "text/markdown"),
        ("sample.csv", "text/csv"),
        ("sample.pdf", "application/pdf"),
        ("sample.docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document"),
        ("sample.xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"),
    ])
    def test_upload_supported_formats(self, client, filename, content_type):
        tc, mock_vs, _ = client
        resp = tc.post("/api/documents/upload",
                       files={"file": (filename, io.BytesIO(b"test content"), content_type)})
        assert resp.status_code == 200, resp.text
        body = resp.json()
        assert body["doc_id"]
        assert "成功" in body["message"]

    def test_upload_unsupported_format(self, client):
        tc, _, _ = client
        resp = tc.post("/api/documents/upload",
                       files={"file": ("bad.exe", io.BytesIO(b"bin"), "application/octet-stream")})
        assert resp.status_code == 400


# ──────────────────────────────────────────────
# AC2: 问答接口
# ──────────────────────────────────────────────

class TestAC2_Chat:
    def test_chat_returns_answer_and_sources(self, client):
        tc, _, _ = client
        resp = tc.post("/api/chat", json={"question": "什么是RAG？"})
        assert resp.status_code == 200, resp.text
        body = resp.json()
        assert body["answer"]
        assert isinstance(body["sources"], list)
        assert len(body["sources"]) > 0

    def test_chat_empty_question(self, client):
        tc, _, _ = client
        resp = tc.post("/api/chat", json={"question": ""})
        assert resp.status_code == 400

    def test_chat_whitespace_question(self, client):
        tc, _, _ = client
        resp = tc.post("/api/chat", json={"question": "   "})
        assert resp.status_code == 400


# ──────────────────────────────────────────────
# AC5: 文档管理
# ──────────────────────────────────────────────

class TestAC5_DocumentManagement:
    def test_list_documents(self, client):
        tc, mock_vs, _ = client
        mock_vs.list_documents.return_value = [
            {"doc_id": "id1", "source": "a.txt", "file_path": "/tmp/a.txt"}
        ]
        resp = tc.get("/api/documents")
        assert resp.status_code == 200
        assert isinstance(resp.json(), list)

    def test_delete_document(self, client):
        tc, mock_vs, _ = client
        mock_vs.reset_mock()
        resp = tc.delete("/api/documents/some-doc-id")
        assert resp.status_code == 200
        assert resp.json()["doc_id"] == "some-doc-id"
        mock_vs.delete_document.assert_called_once_with("some-doc-id")


# ──────────────────────────────────────────────
# 边界与异常场景
# ──────────────────────────────────────────────

class TestEdgeCases:
    def test_chat_no_relevant_docs(self, client):
        tc, _, mock_engine = client
        mock_engine.query = AsyncMock(return_value={
            "answer": "知识库中未找到相关内容。",
            "sources": [],
        })
        resp = tc.post("/api/chat", json={"question": "完全不相关的问题xyz"})
        assert resp.status_code == 200
        assert resp.json()["sources"] == []

    def test_delete_nonexistent_doc(self, client):
        tc, mock_vs, _ = client
        mock_vs.delete_document.return_value = None
        resp = tc.delete("/api/documents/nonexistent-id")
        assert resp.status_code == 200

    def test_upload_parse_failure(self, client, upload_dir):
        """文档解析异常时返回 422。"""
        tc, _, _ = client
        settings = Settings()
        settings.upload.dir = upload_dir
        with patch("app.api.routes.get_settings", return_value=settings), \
             patch("app.api.routes.load_document", side_effect=Exception("parse error")):
            resp = tc.post("/api/documents/upload",
                           files={"file": ("fail.txt", io.BytesIO(b"x"), "text/plain")})
            assert resp.status_code == 422


# ──────────────────────────────────────────────
# 文档加载器单元测试
# ──────────────────────────────────────────────

class TestDocumentLoader:
    def test_unsupported_type_raises(self):
        with pytest.raises(ValueError, match="不支持的文件类型"):
            load_document("file.unknown")

    def test_all_supported_extensions_registered(self):
        for ext in [".pdf", ".docx", ".md", ".txt", ".xlsx", ".xls", ".csv"]:
            assert ext in _LOADERS, f"{ext} 未注册"


# ──────────────────────────────────────────────
# LLM 工厂单元测试
# ──────────────────────────────────────────────

class TestLLMFactory:
    def test_get_ollama_llm(self):
        with patch("app.llm.factory.get_settings") as m:
            s = Settings(); s.llm.provider = "ollama"
            m.return_value = s
            assert isinstance(get_llm(), OllamaLLM)

    def test_get_cloud_llm(self):
        with patch("app.llm.factory.get_settings") as m:
            s = Settings(); s.llm.provider = "cloud"
            m.return_value = s
            assert isinstance(get_llm(), CloudLLM)

    def test_unknown_provider_raises(self):
        with patch("app.llm.factory.get_settings") as m:
            s = Settings(); s.llm.provider = "unknown"
            m.return_value = s
            with pytest.raises(ValueError, match="未知 LLM provider"):
                get_llm()


# ──────────────────────────────────────────────
# 配置加载单元测试
# ──────────────────────────────────────────────

class TestConfig:
    def test_default_settings(self):
        s = Settings()
        assert s.llm.provider == "ollama"
        assert s.embedding.model == "BAAI/bge-m3"
        assert s.vector_store.top_k == 5
        assert s.splitter.chunk_size == 512

    def test_load_from_yaml(self, tmp_path):
        import yaml
        cfg = {"llm": {"provider": "cloud"}, "splitter": {"chunk_size": 256}}
        p = tmp_path / "config.yaml"
        p.write_text(yaml.dump(cfg))
        get_settings.cache_clear()
        s = get_settings(str(p))
        assert s.llm.provider == "cloud"
        assert s.splitter.chunk_size == 256
        get_settings.cache_clear()

    def test_llm_switch_ollama_to_cloud(self):
        """AC3: 修改配置切换 LLM 后端后工厂返回对应实例。"""
        with patch("app.llm.factory.get_settings") as m:
            s = Settings(); s.llm.provider = "cloud"
            m.return_value = s
            llm = get_llm()
            assert isinstance(llm, CloudLLM)
