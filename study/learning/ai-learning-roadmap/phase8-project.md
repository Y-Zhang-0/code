# Phase 8：综合项目实战

> **时间**：Week 17-20（第 113-140 天）
> **总学时**：88 小时
> **目标**：完成 1-2 个完整作品集项目，具备求职或接单的实战能力

---

## 项目选择建议

根据目标方向选择一个主项目深入完成：

| 方向 | 项目 | 技术栈 | 难度 |
|:---|:---|:---|:---|
| 企业应用 | 智能客服系统 | RAG + FastAPI + Gradio | ⭐⭐⭐ |
| 个人工具 | AI 阅读助手 | RAG + Electron/Web | ⭐⭐⭐ |
| 自动化 | 内容生产 Agent | CrewAI + 搜索 + 写作 | ⭐⭐⭐⭐ |
| 数据分析 | 数据问答系统 | Text2SQL + Agent | ⭐⭐⭐⭐ |
| **垂直行业（强烈推荐）** | **AGV 智能运维助手** | **RAG + Agent + 工业知识库** | ⭐⭐⭐⭐ |

> **为什么推荐 AGV+AI 项目**：工业背景是你相对于纯互联网转行者的核心差异化优势。
> 用行业知识（设备故障排查、调度规则、运维手册）搭建一个面向 AGV 场景的 RAG 问答系统，
> 能直接体现"领域 AI 落地"能力，面试加分显著，同时也是真实的市场需求。

---

## 推荐主项目：智能客服系统

### 功能需求

```
用户功能：
- 通过 Web 界面提问
- AI 基于知识库回答
- 展示信息来源
- 支持多轮对话

管理功能：
- 上传/管理知识库文档
- 查看对话历史
- 监控系统状态
```

### 技术架构

```
前端（Gradio/Streamlit）
    ↓
FastAPI 后端
    ├── 文档管理模块（上传/删除/列表）
    ├── RAG 检索模块（向量库 + 混合检索）
    ├── LLM 生成模块（流式输出）
    └── 会话管理模块（历史记录）
    ↓
存储层
    ├── ChromaDB（向量数据）
    ├── SQLite（会话历史）
    └── 本地文件系统（原始文档）
```

---

## Week 13（第 85-91 天）：项目初始化与核心功能

### Day 85（周一，2h）：项目规划与架构设计

```
创建项目结构：
smart-cs/                   # 智能客服系统
├── backend/
│   ├── app/
│   │   ├── main.py         # FastAPI 入口
│   │   ├── config.py       # 配置管理
│   │   ├── api/
│   │   │   ├── chat.py     # 聊天接口
│   │   │   └── documents.py # 文档管理接口
│   │   ├── core/
│   │   │   ├── rag.py      # RAG 引擎
│   │   │   └── session.py  # 会话管理
│   │   └── store/
│   │       ├── vector.py   # 向量存储
│   │       └── database.py # SQLite 存储
├── frontend/
│   └── app.py              # Gradio/Streamlit UI
├── docker-compose.yml
├── requirements.txt
└── README.md
```

任务：
1. 创建上述目录结构
2. 初始化 Git 仓库
3. 创建 `requirements.txt`
4. 设计 API 接口文档（Swagger）

---

### Day 86-87（周二-周三，各 2h）：核心 RAG 引擎

整合前面学到的所有 RAG 技术：
- 多格式文档解析（PDF/Word/MD/TXT）
- 分块 + 向量化
- 混合检索（向量 + BM25）
- Rerank 重排序

```python
# backend/app/core/rag.py
class RAGEngine:
    def __init__(self, settings: Settings):
        self.embeddings = HuggingFaceBgeEmbeddings(
            model_name=settings.embedding_model
        )
        self.vectordb = Chroma(
            persist_directory=settings.chroma_path,
            embedding_function=self.embeddings
        )
        self.llm = ZhipuAI(api_key=settings.zhipu_api_key)
        self.reranker = CrossEncoder("BAAI/bge-reranker-v2-m3")

    def add_document(self, filepath: str) -> int:
        """导入文档，返回 chunk 数量"""
        docs = self._load(filepath)
        chunks = self._split(docs)
        self.vectordb.add_documents(chunks)
        return len(chunks)

    def query(self, question: str, top_k: int = 3) -> dict:
        """检索并生成回答"""
        # 混合检索
        docs = self._hybrid_retrieve(question, top_k * 3)
        # Rerank
        docs = self._rerank(question, docs, top_k)
        # 组装上下文
        context = "\n\n".join([d.page_content for d in docs])
        # 生成回答（流式）
        return {"context": context, "sources": [d.metadata for d in docs]}
```

---

### Day 88-89（周四-周五，各 2h）：会话管理

```python
# backend/app/store/database.py
import sqlite3
from dataclasses import dataclass
from datetime import datetime

@dataclass
class Message:
    session_id: str
    role: str
    content: str
    created_at: str

class SessionStore:
    def __init__(self, db_path: str = "sessions.db"):
        self.db_path = db_path
        self._init_db()

    def _init_db(self):
        with sqlite3.connect(self.db_path) as conn:
            conn.execute("""
                CREATE TABLE IF NOT EXISTS messages (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    session_id TEXT NOT NULL,
                    role TEXT NOT NULL,
                    content TEXT NOT NULL,
                    created_at TEXT NOT NULL
                )
            """)
            conn.execute("CREATE INDEX IF NOT EXISTS idx_session ON messages(session_id)")

    def add_message(self, session_id: str, role: str, content: str):
        with sqlite3.connect(self.db_path) as conn:
            conn.execute(
                "INSERT INTO messages (session_id, role, content, created_at) VALUES (?, ?, ?, ?)",
                (session_id, role, content, datetime.now().isoformat())
            )

    def get_history(self, session_id: str, limit: int = 10) -> list[Message]:
        with sqlite3.connect(self.db_path) as conn:
            rows = conn.execute(
                "SELECT session_id, role, content, created_at FROM messages "
                "WHERE session_id = ? ORDER BY id DESC LIMIT ?",
                (session_id, limit)
            ).fetchall()
        return [Message(*row) for row in reversed(rows)]
```

---

### Day 90-91（周末，6h×2）：前端界面

```python
# frontend/app.py — Gradio 界面
import gradio as gr
import requests
import json

API_URL = "http://localhost:8000"

def chat_with_bot(message, history, session_id):
    if not session_id:
        session_id = f"session_{len(history)}"

    response = requests.post(
        f"{API_URL}/chat",
        json={"question": message, "session_id": session_id},
        stream=True
    )

    partial = ""
    for line in response.iter_lines():
        if line.startswith(b"data: "):
            data = line[6:].decode()
            if data == "[DONE]":
                break
            partial += data
            yield partial

def upload_doc(file):
    with open(file.name, "rb") as f:
        response = requests.post(
            f"{API_URL}/documents/upload",
            files={"file": (file.name, f)}
        )
    return response.json().get("message", "上传失败")

with gr.Blocks(title="智能客服系统", theme=gr.themes.Soft()) as demo:
    gr.Markdown("# 🤖 智能客服系统")

    with gr.Tab("💬 对话"):
        session_id = gr.State("")
        chatbot = gr.Chatbot(height=500, show_label=False)
        with gr.Row():
            msg = gr.Textbox(placeholder="输入你的问题...", scale=4)
            submit = gr.Button("发送", scale=1, variant="primary")

        submit.click(chat_with_bot, [msg, chatbot, session_id], [chatbot])
        msg.submit(chat_with_bot, [msg, chatbot, session_id], [chatbot])

    with gr.Tab("📄 知识库管理"):
        file_upload = gr.File(label="上传文档", file_types=[".pdf", ".docx", ".txt", ".md"])
        upload_btn = gr.Button("导入知识库", variant="primary")
        upload_result = gr.Textbox(label="结果")

        upload_btn.click(upload_doc, [file_upload], [upload_result])

demo.launch(server_port=7860)
```

---

## Week 14（第 92-98 天）：功能完善与测试

### Day 92-93（周一-周二，各 2h）：错误处理与边界情况

- 文件上传失败处理
- 知识库为空时的提示
- 网络超时重试
- 并发请求处理

### Day 94-95（周三-周四，各 2h）：性能优化

```python
# 文档异步导入（避免阻塞 API）
from fastapi import BackgroundTasks

@app.post("/documents/upload")
async def upload(file: UploadFile, background_tasks: BackgroundTasks):
    # 立即返回
    task_id = save_file(file)
    # 后台处理
    background_tasks.add_task(process_document, task_id)
    return {"task_id": task_id, "status": "processing"}

@app.get("/documents/status/{task_id}")
async def get_status(task_id: str):
    return {"status": get_task_status(task_id)}
```

### Day 96（周五，2h）：安全加固

- SQL 注入防护（已用参数化查询）
- 文件上传安全（类型检查、大小限制、文件名清理）
- API Key 认证
- CORS 配置

### Day 97-98（周末，6h×2）：集成测试

```python
# tests/test_e2e.py
import pytest
import httpx

BASE_URL = "http://localhost:8000"

@pytest.mark.asyncio
async def test_full_workflow():
    async with httpx.AsyncClient() as client:
        # 1. 上传文档
        with open("test_doc.pdf", "rb") as f:
            response = await client.post(
                f"{BASE_URL}/documents/upload",
                files={"file": f}
            )
        assert response.status_code == 200

        # 2. 提问
        response = await client.post(
            f"{BASE_URL}/chat",
            json={"question": "文档的主要内容是什么？"}
        )
        assert response.status_code == 200
        assert len(response.json()["answer"]) > 0
```

---

## Week 15（第 99-105 天）：GitHub 与作品集准备

### Day 99-100（周一-周二，各 2h）：README 撰写

```markdown
# 智能客服系统

> 基于 RAG + LangChain + FastAPI 的企业级知识库问答系统

## ✨ 功能特性

- 📄 多格式文档支持（PDF/Word/MD/TXT）
- 🔍 混合检索（向量 + BM25）+ Rerank 重排序
- 💬 流式对话，逐字显示
- 🌐 多语言支持（中英日）
- 🐳 Docker 一键部署

## 🚀 快速开始

```bash
git clone https://github.com/你的用户名/smart-cs
cd smart-cs
cp .env.example .env  # 填写 API Key
docker-compose up -d
# 访问 http://localhost:7860
```

## 🏗 技术架构

（图表）

## 📊 效果演示

（截图或 GIF）
```

### Day 101-102（周三-周四，各 2h）：项目优化与 Code Review

- 代码整理，删除调试代码
- 统一注释风格
- 检查敏感信息（确保没有 API Key 泄漏）
- 补充缺失的类型注解

### Day 103（周五，2h）：部署最终版本

- 更新 `docker-compose.yml`
- 部署到公网服务器
- 记录公网访问地址

### Day 104-105（周末，6h×2）：第二个项目 — Text2SQL 数据问答系统

> 针对**求职 AI 工程师**：第二个项目选 Text2SQL，与第一个 RAG 项目形成技术互补，覆盖企业最常见的两类 AI 应用场景。

**为什么是 Text2SQL？**
- 与 RAG（非结构化）形成对比，展示对**结构化数据**场景的理解
- 企业数据分析需求极大，面试加分
- 技术栈完全复用（LangGraph + FastAPI + Vue 前端可复用）

**项目功能**

```
用户：帮我查一下上个月各部门的销售额排名
 ↓
AI 生成 SQL：
SELECT dept, SUM(amount) AS total
FROM orders
WHERE date >= DATE_TRUNC('month', NOW() - INTERVAL '1 month')
GROUP BY dept ORDER BY total DESC
 ↓
执行 SQL → 返回结果表格
 ↓
AI 解读：上个月销售部排名第一，金额 280 万，同比增长 15%...
```

**技术架构**

```
用户问题
    ↓
LangGraph Agent
    ├── 获取数据库 Schema（工具）
    ├── 生成 SQL（LLM）
    ├── 校验 SQL 安全性（只允许 SELECT）
    ├── 执行 SQL（工具）
    └── 解读结果（LLM）
    ↓
FastAPI 后端 → 返回 {sql, data, analysis}
    ↓
前端表格展示（你的 Vue 技能派上用场）
```

**Day 104（6h）**：实现 Text2SQL 核心

```python
# text2sql_agent.py
from langchain_core.tools import tool
import sqlalchemy
import pandas as pd

@tool
def get_schema(table_names: list[str] = None) -> str:
    """获取数据库表结构，帮助 LLM 理解数据"""
    engine = sqlalchemy.create_engine("sqlite:///./sales.db")
    inspector = sqlalchemy.inspect(engine)

    schema_parts = []
    tables = table_names or inspector.get_table_names()

    for table in tables:
        columns = inspector.get_columns(table)
        col_desc = ", ".join([f"{c['name']} ({c['type']})" for c in columns])
        schema_parts.append(f"表 {table}: {col_desc}")

    return "\n".join(schema_parts)

@tool
def execute_sql(sql: str) -> str:
    """执行 SQL 查询，返回结果"""
    # 安全检查：只允许 SELECT
    if not sql.strip().upper().startswith("SELECT"):
        return "错误：只允许执行 SELECT 查询"

    engine = sqlalchemy.create_engine("sqlite:///./sales.db")
    try:
        df = pd.read_sql(sql, engine)
        return df.to_markdown(index=False)  # 返回 Markdown 表格
    except Exception as e:
        return f"SQL 执行错误：{e}"
```

**Day 105（6h）**：
- 前端页面（Vue + Element Plus 表格展示）
- 部署到公网
- 录制演示视频（2-3分钟，展示从问题到 SQL 到结果的完整流程）

---

## Week 16（第 106-112 天）：总结与求职准备

### Day 106-107（周一-周二，各 2h）：技术栈总结

梳理并能流利表达：
1. **RAG 检索增强**：为什么分块、如何选择 chunk_size、混合检索的优势
2. **Agent 工具调用**：ReAct 框架、如何保证稳定性
3. **工程化**：Docker 的价值、FastAPI 异步的优势

### Day 108-109（周三-周四，各 2h）：常见面试题准备

**技术问题（必会）**
- RAG 的完整流程是什么？
- Embedding 和关键词搜索有什么区别？各自适合什么场景？
- 如何评估 RAG 系统的质量？RAGAs 的四个指标分别是什么？
- Agent 和传统程序有什么区别？ReAct 框架的核心思想是什么？
- 如何处理 LLM 的幻觉问题？
- **LangGraph 相比 AgentExecutor 的优势是什么？**（2025 年高频）
- **HyDE 是什么？什么场景下使用？**
- **混合检索的原理和权重如何调优？**
- Function Calling 的工作流程？

**系统设计问题（中高级岗位）**
- 如果 RAG 系统要支持 100 万用户，如何扩展？
- 如何设计一个 Agent 系统的监控告警体系？
- 向量数据库如何选型（Chroma vs Milvus vs Pinecone）？
- 大文件（100MB PDF）的 RAG 方案如何设计？

**项目问题**
- 介绍你做的 RAG 项目，核心挑战是什么？
- 你的 Text2SQL 如何保证 SQL 安全性？
- 如何量化证明你的 RAG 系统质量提升？（RAGAs 评分）

### Day 110-112（周末 + 最后一天，6h+6h+2h）：作品集完善

**最终检查清单**
- [ ] 2 个项目代码托管在 GitHub
- [ ] 每个项目有清晰的 README
- [ ] 至少 1 个项目有公网 Demo
- [ ] 能独立讲清楚任意技术点
- [ ] 简历上的 AI 技术栈描述准确

---

## 16 周学习成果

完成本路线后，你将具备：

| 能力 | 水平 |
|:---|:---|
| Python 编程 | 能写 200-500 行的工程化代码 |
| LLM API 调用 | 熟练，包括流式、多轮、结构化输出 |
| RAG 系统 | 能独立从零搭建生产级 RAG 服务 |
| Agent 开发 | 能构建多工具 Agent 和多 Agent 协作 |
| FastAPI 服务 | 能设计和实现 RESTful API |
| Docker 部署 | 能容器化部署到公网 |
| 工程思维 | 知道如何评估、调优、监控 AI 系统 |

**求职方向**
- AI 应用开发工程师
- LLM 工程师
- 后端工程师（AI 方向）
- 独立开发者 / 接外包项目
