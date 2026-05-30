# RAG Knowledge Bot — 技术设计

## 设计目标

基于 LangChain 构建模块化的 RAG 问答系统，支持多格式、多语言文档，LLM 可插拔切换。

## 方案概述

采用 LangChain 框架搭建 RAG 管线：文档加载（LangChain Loaders）→ 文本分块（RecursiveCharacterTextSplitter）→ 多语言向量嵌入（bge-m3）→ ChromaDB 存储 → 语义检索 → LLM 生成回答。通过 FastAPI 暴露 REST API。

## 架构流程

```
┌─────────────────── 文档导入管线 ──────────────────────────┐
│                                                           │
│  文档上传 → 格式识别 → LangChain Loader → 文本分块 → bge-m3 嵌入 → ChromaDB │
│              ↓                                            │
│     PDF / Word / MD / TXT / Excel / CSV                   │
│     中文 / 英文 / 日文                                      │
└───────────────────────────────────────────────────────────┘

┌─────────────────── 问答管线 ──────────────────────────────┐ 
│                                                           │
│  用户提问 → bge-m3 向量化 → ChromaDB 相似度检索             │
│                                  ↓                        │
│                       Top-K 相关文档片段                    │
│                                  ↓                        │
│                       Prompt 组装（问题 + 上下文）           │
│                                  ↓                        │
│                       LLM 生成回答（Ollama / 云端）          │
│                                  ↓                        │
│                       返回答案 + 引用来源                    │
└───────────────────────────────────────────────────────────┘
```

## 关键技术选型

| 组件      | 选择                                       | 理由                                               |
|:------- |:---------------------------------------- |:------------------------------------------------ |
| RAG 框架  | LangChain                                | 主公指定；内置多格式加载器和分割器                                |
| API 框架  | FastAPI                                  | 异步、自动文档、Python 生态主流                              |
| 向量数据库   | ChromaDB                                 | Python 原生嵌入式，LangChain 原生支持，中型规模足够，大型可迁移至 Milvus |
| 嵌入模型    | BAAI/bge-m3                              | 中英日多语言检索效果最佳，支持 100+ 语言                          |
| LLM（默认） | Ollama（qwen2 等）                          | 本地离线运行，隐私安全                                      |
| 文档解析    | LangChain Loaders                        | 内置 PDF / Word / CSV 等加载器                         |
| 文本分块    | LangChain RecursiveCharacterTextSplitter | 可配置 chunk_size / overlap，支持多语言                   |

## 关键接口

```python
# LLM 抽象接口
class BaseLLM(ABC):
    async def generate(self, prompt: str) -> str: ...

# API 接口
POST /api/documents/upload     # 上传文档
GET  /api/documents            # 文档列表
DELETE /api/documents/{id}     # 删除文档
POST /api/chat                 # 问答
```

## 项目结构

```
rag-kb/
├── app/
│   ├── main.py                # FastAPI 入口
│   ├── api/
│   │   ├── routes.py          # API 路由
│   │   └── schemas.py         # Pydantic 模型
│   ├── core/
│   │   ├── config.py          # 配置管理
│   │   └── rag_engine.py      # RAG 核心引擎（基于 LangChain）
│   ├── llm/
│   │   ├── base.py            # LLM 抽象接口
│   │   ├── ollama.py          # Ollama 实现
│   │   └── cloud.py           # 云端 API 实现（预留）
│   ├── loader/
│   │   └── document_loader.py # 统一文档加载（LangChain 加载器封装）
│   └── store/
│       └── vector_store.py    # ChromaDB 封装（LangChain 集成）
├── data/                      # 知识库文档存放目录
├── config.yaml                # 配置文件
└── requirements.txt
```

## 实施步骤

1. 项目初始化：创建目录结构、`requirements.txt`、`config.yaml`、FastAPI 入口
2. 文档加载模块：基于 LangChain 加载器封装多格式解析
3. 文本分块：使用 LangChain RecursiveCharacterTextSplitter
4. 嵌入模块：集成 BAAI/bge-m3 多语言嵌入模型
5. 向量存储：基于 LangChain 封装 ChromaDB 操作
6. LLM 模块：实现 Ollama 本地接口 + 云端 API 抽象预留
7. RAG 引擎：基于 LangChain 串联检索→上下文组装→LLM 生成
8. API 路由：实现文档上传/列表/删除 + 问答接口
9. 集成测试：端到端验证完整 RAG 流程

## 决策记录

| 决策点    | 选择              | 理由             | 排除方案                           |
|:------ |:--------------- |:-------------- |:------------------------------ |
| RAG 框架 | LangChain       | 主公指定；生态成熟      | 自建（主公要求 LangChain）、LlamaIndex  |
| 嵌入模型   | bge-m3          | 中英日多语言检索效果最佳   | bge-small-zh（仅中文）、MiniLM（精度不足） |
| 向量数据库  | ChromaDB        | 嵌入式无需额外服务，中型足够 | Milvus（中型过重）、FAISS（缺持久化管理）     |
| LLM    | 可插拔 Ollama + 云端 | 灵活部署，默认离线可用    | 单一绑定                           |

## 验证方式

1. 单元测试：各格式文档加载器解析正确性
2. 集成测试：完整管线（上传→分块→存储→检索→回答）端到端验证
3. 性能测试：500 份文档场景下检索响应时间
4. 多语言测试：分别上传中/英/日文档，验证检索与回答准确性

## TODO List

- [ ] 1. 项目初始化：创建目录结构、`requirements.txt`、`config.yaml`、FastAPI 入口
- [ ] 2. 文档加载模块：基于 LangChain 加载器封装 PDF / Word / Markdown-TXT / Excel-CSV 多格式解析
- [ ] 3. 文本分块：使用 LangChain `RecursiveCharacterTextSplitter`，配置适合多语言的分块参数
- [ ] 4. 嵌入模块：集成 `BAAI/bge-m3` 多语言嵌入模型
- [ ] 5. 向量存储：基于 LangChain 封装 ChromaDB 的存储、检索、删除操作
- [ ] 6. LLM 模块：实现 Ollama 本地接口 + 云端 API 抽象预留
- [ ] 7. RAG 引擎：基于 LangChain 串联检索→上下文组装→LLM 生成的核心管线
- [ ] 8. API 路由：实现文档上传/列表/删除 + 问答接口
- [ ] 9. 集成测试：端到端验证完整 RAG 流程
