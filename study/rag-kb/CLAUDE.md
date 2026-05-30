# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 项目概述

本仓库为 **RAG Knowledge Bot** — 基于 LangChain + FastAPI + ChromaDB 构建的内部知识库问答 API 服务，支持多格式（PDF/Word/MD/TXT/Excel/CSV）、多语言（中英日）文档导入与智能检索问答。

应用代码位于 `app/`，技术文档位于 `docs/`。

## 常用命令

所有命令在项目根目录（本文件所在的 `rag-kb/`）下执行。

```bash
# 安装依赖
pip install -r requirements.txt

# 启动服务
python -m app.main
# 或
uvicorn app.main:app --reload

# 运行全部测试
pytest tests/ -v

# 运行单个测试类
pytest tests/test_integration.py::TestAC2_Chat -v

# 运行单个测试用例
pytest tests/test_integration.py::TestConfig::test_load_from_yaml -v
```

## 架构说明

```
rag-kb/
├── app/
│   ├── main.py              # FastAPI 入口，挂载 /api 路由
│   ├── core/
│   │   ├── config.py        # Settings（pydantic）从 config.yaml 加载，lru_cache 单例
│   │   └── rag_engine.py    # RAG 核心：ChromaDB 检索 → Prompt 组装 → LLM 生成
│   ├── api/
│   │   ├── routes.py        # 4 个端点：POST /documents/upload, GET /documents,
│   │   │                    #           DELETE /documents/{id}, POST /chat
│   │   └── schemas.py       # Pydantic 请求/响应模型
│   ├── loader/
│   │   └── document_loader.py  # 按扩展名分派 LangChain Loader，统一返回 List[Document]
│   ├── store/
│   │   └── vector_store.py  # ChromaDB 封装：add_documents / search / delete / list
│   └── llm/
│       ├── base.py          # BaseLLM 抽象接口
│       ├── ollama.py        # Ollama HTTP 实现（默认）
│       ├── cloud.py         # OpenAI 兼容云端实现（预留）
│       └── factory.py       # get_llm() 按 config.yaml llm.provider 返回实例
├── config.yaml              # 主配置文件（LLM/嵌入/向量库/分块/上传参数）
└── tests/
    └── test_integration.py  # 所有测试；顶部用 sys.modules mock 重型依赖，无需真实模型
```

**关键设计点**：
- `VectorStore` 和 `RAGEngine` 均为模块级单例（`get_vector_store()` / `get_rag_engine()`）
- 嵌入模型固定 `BAAI/bge-m3`（100+ 语言），分块参数在 `config.yaml splitter` 节配置
- 切换 LLM：修改 `config.yaml` 中 `llm.provider = ollama | cloud` 即可，无需改代码
- 测试不依赖 langchain/chromadb 安装：测试文件顶部预先将重型依赖注入 `sys.modules` 为 MagicMock

## 文档索引

| 类型 | 路径 |
|:----|:-----|
| 需求文档 | `docs/requirements.md` |
| 技术设计 | `docs/design.md` |
| 测试报告 | `docs/test-report.md` |
