# Phase 4：工程化基础

> **时间**：Week 8-9（第 57-63 天）
> **总学时**：44 小时
> **目标**：将 RAG 应用容器化部署上线，建立测试与 CI/CD 体系，实现生产就绪

---

## 本阶段里程碑

RAG API 生产就绪：
- Docker 容器化，一行命令启动
- 部署到云服务器，公网可访问
- 有基本的 API 认证和访问限制
- 有完整的测试覆盖和 CI/CD 流程
- 有基础的日志和监控

---

## Week 8（第 57-63 天）：Docker 容器化 + 部署

### Day 57（周一，2h）：Docker 基础概念

#### 为什么需要 Docker？
```
问题：在我电脑能跑,在服务器跑不了
原因：环境不同（Python 版本、依赖库版本、系统配置）

Docker 解决方案：
把整个运行环境（代码 + 依赖 + 配置）打包成"镜像"
镜像可以在任何装了 Docker 的机器上运行,环境完全一致
```

#### 核心概念
```
镜像（Image）：类比"菜谱",定义如何构建环境
容器（Container）：类比"做出来的菜",镜像运行后的实例
Dockerfile：描述如何构建镜像的脚本
docker-compose：同时管理多个容器
```

#### 安装 Docker
- 下载 Docker Desktop：https://docs.docker.com/get-started/get-docker/
- 安装后验证：`docker --version`

#### 第一个 Docker 容器
```bash
# 运行 Hello World
docker run hello-world

# 运行一个 Python 容器
docker run -it python:3.11 python

# 查看运行中的容器
docker ps

# 查看所有容器（包括已停止）
docker ps -a

# 停止容器
docker stop <容器ID>

# 删除容器
docker rm <容器ID>
```

#### 今日检查点
- [ ] Docker Desktop 安装并运行成功
- [ ] `docker run hello-world` 输出正确
- [ ] 理解镜像和容器的区别

---

### Day 58（周二，2h）：编写 Dockerfile

```dockerfile
# Dockerfile — 放在项目根目录

# 基础镜像（选择带 Python 3.11 的精简版）
FROM python:3.11-slim

# 设置工作目录
WORKDIR /app

# 先复制依赖文件（利用 Docker 缓存层优化构建速度）
COPY requirements.txt .

# 安装依赖
RUN pip install --no-cache-dir -r requirements.txt \
    && pip install --no-cache-dir uvicorn

# 复制项目代码
COPY . .

# 创建必要目录
RUN mkdir -p uploads chroma_db logs

# 暴露端口
EXPOSE 8000

# 启动命令
CMD ["uvicorn", "app.main:app", "--host", "0.0.0.0", "--port", "8000"]
```

```bash
# 构建镜像
docker build -t rag-kb:latest .

# 运行容器
docker run -d \
  --name rag-kb \
  -p 8000:8000 \
  -e ZHIPU_API_KEY=你的key \
  -v $(pwd)/data:/app/data \
  rag-kb:latest

# 查看日志
docker logs rag-kb -f

# 进入容器调试
docker exec -it rag-kb bash
```

```dockerfile
# .dockerignore — 排除不需要的文件
__pycache__/
*.pyc
.env
*.egg-info/
.git/
venv/
chroma_db/
uploads/
```

#### 今日检查点
- [ ] 能写 Dockerfile 并成功构建镜像
- [ ] 容器能正常运行并访问 API

---

### Day 59（周三，2h）：Docker Compose

```yaml
# docker-compose.yml

version: "3.8"

services:
  # AI 应用
  rag-kb:
    build: .
    container_name: rag-kb
    ports:
      - "8000:8000"
    environment:
      - ZHIPU_API_KEY=${ZHIPU_API_KEY}
      - CHROMA_PATH=/app/data/chroma_db
    volumes:
      - ./data:/app/data        # 持久化数据
      - ./logs:/app/logs        # 持久化日志
    restart: unless-stopped     # 崩溃自动重启
    healthcheck:
      test: ["CMD", "curl", "-f", "http://localhost:8000/health"]
      interval: 30s
      timeout: 10s
      retries: 3

  # Nginx 反向代理（可选）
  nginx:
    image: nginx:alpine
    ports:
      - "80:80"
    volumes:
      - ./nginx.conf:/etc/nginx/conf.d/default.conf
    depends_on:
      - rag-kb
```

```bash
# 启动所有服务
docker-compose up -d

# 停止
docker-compose down

# 查看日志
docker-compose logs -f rag-kb

# 重启单个服务
docker-compose restart rag-kb
```

---

### Day 60（周四，2h）：环境变量与配置管理

```python
# config.py — 生产环境配置管理
from pydantic_settings import BaseSettings
from functools import lru_cache

class Settings(BaseSettings):
    # LLM 配置
    zhipu_api_key: str
    llm_model: str = "glm-4-flash"
    llm_temperature: float = 0.7

    # 向量库配置
    chroma_path: str = "./chroma_db"
    embedding_model: str = "BAAI/bge-m3"

    # 服务配置
    api_key: str = ""  # API 认证密钥
    max_file_size_mb: int = 50
    allowed_origins: list[str] = ["*"]

    class Config:
        env_file = ".env"
        env_file_encoding = "utf-8"

@lru_cache()
def get_settings() -> Settings:
    return Settings()
```

```
# .env.example（提交到 Git 的模板,不含真实值）
ZHIPU_API_KEY=your_key_here
LLM_MODEL=glm-4-flash
CHROMA_PATH=./chroma_db
API_KEY=your_api_auth_key_here

# .env（本地/服务器实际配置,加入 .gitignore！）
ZHIPU_API_KEY=zhipu-xxxxx-真实key
```

---

### Day 61（周五，2h）：API 认证与限流

```python
# middleware/auth.py
from fastapi import HTTPException, Security
from fastapi.security import APIKeyHeader

api_key_header = APIKeyHeader(name="X-API-Key", auto_error=False)

async def verify_api_key(api_key: str = Security(api_key_header)):
    settings = get_settings()
    if settings.api_key and api_key != settings.api_key:
        raise HTTPException(status_code=403, detail="无效的 API Key")
    return api_key

# 在路由上使用
@app.post("/chat", dependencies=[Depends(verify_api_key)])
async def chat(request: ChatRequest):
    ...
```

```python
# 简单限流（使用 slowapi）
pip install slowapi
```

```python
from slowapi import Limiter, _rate_limit_exceeded_handler
from slowapi.util import get_remote_address
from slowapi.errors import RateLimitExceeded

limiter = Limiter(key_func=get_remote_address)
app.state.limiter = limiter
app.add_exception_handler(RateLimitExceeded, _rate_limit_exceeded_handler)

@app.post("/chat")
@limiter.limit("10/minute")  # 每分钟最多 10 次请求
async def chat(request: Request, body: ChatRequest):
    ...
```

---

### Day 62-63（周末，6h×2）：部署到云服务器

#### 准备服务器

推荐选择：
- **Railway**（最简单,有免费额度）：https://railway.app/
- **阿里云 ECS**（国内访问快）：2 核 2G 约 ¥80/月
- **腾讯云 CVM**：类似阿里云

#### Railway 部署（推荐新手）
```bash
# 安装 Railway CLI
npm i -g @railway/cli

# 登录
railway login

# 在项目目录初始化
railway init

# 部署
railway up

# 查看部署日志
railway logs

# 设置环境变量
railway variables set ZHIPU_API_KEY=你的key
```

#### 手动部署到 Linux 服务器
```bash
# 连接服务器
ssh root@your-server-ip

# 安装 Docker
curl -fsSL https://get.docker.com | sh
systemctl start docker
systemctl enable docker

# 安装 Docker Compose
apt-get install docker-compose-plugin

# 克隆代码
git clone https://github.com/你的用户名/你的项目.git
cd 你的项目

# 配置环境变量
cp .env.example .env
nano .env  # 填写真实的 API Key

# 启动
docker-compose up -d

# 验证
curl http://localhost:8000/health
```

---

## Week 9（第 64-70 天）：测试与 CI/CD

### Day 64-65（周一-周二，各 2h）：pytest 单元测试体系

> AI 应用的测试有别于普通后端：重型依赖（LLM、向量库）必须 mock,否则测试慢且费钱。

```bash
pip install pytest pytest-asyncio pytest-mock
```

**测试文件结构**

```
tests/
├── conftest.py          # 共享 fixtures（mock 重型依赖）
├── test_rag_engine.py   # RAG 引擎单元测试
├── test_routes.py       # API 路由单元测试
└── test_integration.py  # 集成测试（可选,需真实依赖）
```

**conftest.py — Mock 重型依赖**

```python
# tests/conftest.py
import pytest
from unittest.mock import MagicMock, AsyncMock
from fastapi.testclient import TestClient

@pytest.fixture
def mock_embeddings():
    """Mock 嵌入模型,避免下载 2GB 模型"""
    mock = MagicMock()
    mock.embed_query.return_value = [0.1] * 1024
    mock.embed_documents.return_value = [[0.1] * 1024, [0.2] * 1024]
    return mock

@pytest.fixture
def mock_llm():
    """Mock LLM,避免真实 API 调用"""
    mock = AsyncMock()
    mock.ainvoke.return_value = MagicMock(content="这是模拟的 AI 回答")
    return mock

@pytest.fixture
def mock_vector_store(mock_embeddings):
    """Mock 向量库"""
    from unittest.mock import patch
    mock = MagicMock()
    mock.similarity_search.return_value = [
        MagicMock(page_content="相关文档片段1", metadata={"source": "test.pdf"}),
        MagicMock(page_content="相关文档片段2", metadata={"source": "test.pdf"}),
    ]
    mock.add_documents.return_value = ["id1", "id2"]
    return mock

@pytest.fixture
def test_client(mock_vector_store, mock_llm):
    """测试用的 FastAPI 客户端"""
    from unittest.mock import patch
    with patch("app.store.vector_store.get_vector_store", return_value=mock_vector_store):
        with patch("app.llm.factory.get_llm", return_value=mock_llm):
            from app.main import app
            return TestClient(app)
```

**单元测试示例**

```python
# tests/test_rag_engine.py
import pytest
from app.core.rag_engine import RAGEngine

class TestRAGEngine:
    def test_query_returns_answer(self, mock_vector_store, mock_llm):
        engine = RAGEngine(vector_store=mock_vector_store, llm=mock_llm)
        result = engine.query("Python 是什么？")

        assert result["answer"] is not None
        assert len(result["sources"]) > 0
        mock_vector_store.similarity_search.assert_called_once()

    def test_query_with_empty_kb_returns_graceful_message(self, mock_llm):
        """知识库为空时应给出友好提示"""
        empty_store = MagicMock()
        empty_store.similarity_search.return_value = []

        engine = RAGEngine(vector_store=empty_store, llm=mock_llm)
        result = engine.query("任意问题")

        assert "没有找到" in result["answer"] or result["sources"] == []

    @pytest.mark.asyncio
    async def test_async_query(self, mock_vector_store, mock_llm):
        """异步查询测试"""
        engine = RAGEngine(vector_store=mock_vector_store, llm=mock_llm)
        result = await engine.aquery("Python 是什么？")
        assert result is not None

# tests/test_routes.py
class TestChatRoute:
    def test_chat_success(self, test_client):
        response = test_client.post(
            "/api/chat",
            json={"question": "Python 是什么？"}
        )
        assert response.status_code == 200
        data = response.json()
        assert "answer" in data
        assert "sources" in data

    def test_chat_empty_question_rejected(self, test_client):
        response = test_client.post("/api/chat", json={"question": ""})
        assert response.status_code == 422  # Pydantic 校验失败

    def test_upload_unsupported_format(self, test_client):
        response = test_client.post(
            "/api/documents/upload",
            files={"file": ("test.exe", b"content", "application/octet-stream")}
        )
        assert response.status_code == 400
```

**运行测试**

```bash
# 运行全部测试
pytest tests/ -v

# 运行指定测试类
pytest tests/test_routes.py::TestChatRoute -v

# 显示覆盖率
pip install pytest-cov
pytest tests/ --cov=app --cov-report=term-missing

# 只运行快速测试（排除集成测试）
pytest tests/ -m "not integration" -v
```

---

### Day 66（周三，2h）：GitHub Actions CI

```yaml
# .github/workflows/ci.yml
name: CI

on:
  push:
    branches: [main, master, develop]
  pull_request:
    branches: [main, master]

jobs:
  test:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Set up Python
        uses: actions/setup-python@v5
        with:
          python-version: "3.11"
          cache: "pip"

      - name: Install dependencies
        run: |
          pip install -r requirements.txt
          pip install pytest pytest-asyncio pytest-mock pytest-cov

      - name: Run tests
        run: pytest tests/ -v --cov=app --cov-report=xml
        env:
          # 测试时用 mock,不需要真实 key
          ZHIPU_API_KEY: "test_key"
          LLM_PROVIDER: "mock"

      - name: Upload coverage report
        uses: codecov/codecov-action@v4
        with:
          file: ./coverage.xml
          fail_ci_if_error: false

  lint:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - uses: actions/setup-python@v5
        with:
          python-version: "3.11"
      - name: Install Ruff
        run: pip install ruff
      - name: Run linter
        run: ruff check app/ tests/
```

**PR 保护配置（GitHub 仓库设置）**

```
Settings → Branches → Add branch protection rule:
- Branch name: main
- ✓ Require status checks to pass before merging
  - 选择: test, lint
- ✓ Require pull request reviews before merging
```

今日效果：每次 push 或 PR 自动跑测试,测试不通过无法合并,作品集代码质量有保障。

---

### Day 67（周四，2h）：Ollama 本地模型集成

> Ollama 让你在本地运行 LLM,零 API 费用,开发调试首选。
> 项目 rag-kb 已支持 Ollama,此处系统学习接入方式。

```bash
# 安装 Ollama（Windows/Mac/Linux）
# 访问 https://ollama.ai/ 下载安装包

# 下载并运行模型
ollama run qwen2.5:7b          # 阿里通义千问 7B（中文效果好）
ollama run llama3.2:3b         # Meta Llama 3.2 3B（轻量）
ollama run deepseek-r1:7b      # DeepSeek R1（推理能力强）

# 查看已下载的模型
ollama list

# Ollama 默认在 http://localhost:11434 提供 API
```

**LangChain 接入 Ollama**

```python
from langchain_ollama import ChatOllama, OllamaEmbeddings

# LLM
llm = ChatOllama(
    model="qwen2.5:7b",
    base_url="http://localhost:11434",
    temperature=0.7,
)

response = llm.invoke("你好,请用一句话介绍自己")
print(response.content)

# 嵌入模型（本地,完全免费）
embeddings = OllamaEmbeddings(
    model="nomic-embed-text",
    base_url="http://localhost:11434",
)
```

**config.yaml 切换（rag-kb 项目）**

```yaml
llm:
  provider: ollama        # 切换到本地模型
  model: qwen2.5:7b
  base_url: http://localhost:11434
  temperature: 0.7
```

**开发效率建议**

| 场景 | 推荐 |
|:---|:---|
| 日常开发/调试 | Ollama 本地（零费用） |
| Prompt 调优验证 | 先 Ollama,效果好再用云端验证 |
| 生产环境 | 云端 API |

---

### Day 68（周五，2h）：日志系统

```python
# logging_config.py
import logging
import sys
from pathlib import Path

def setup_logging(log_level: str = "INFO"):
    log_dir = Path("logs")
    log_dir.mkdir(exist_ok=True)

    logging.basicConfig(
        level=getattr(logging, log_level),
        format="%(asctime)s | %(levelname)s | %(name)s | %(message)s",
        handlers=[
            logging.StreamHandler(sys.stdout),  # 控制台输出
            logging.FileHandler(               # 文件输出
                log_dir / "app.log",
                encoding="utf-8"
            )
        ]
    )

# 在路由中使用
logger = logging.getLogger(__name__)

@app.post("/chat")
async def chat(request: ChatRequest):
    logger.info(f"收到问题：{request.question[:50]}...")

    try:
        result = await process_query(request)
        logger.info(f"回答完成,长度：{len(result.answer)}")
        return result
    except Exception as e:
        logger.error(f"处理失败：{e}", exc_info=True)
        raise
```

---

### Day 69-70（周末，6h×2）：全面测试 + 文档与演示

**Day 69（6h）**：
- 完整部署 RAG 知识库 API 到公网
- 配置 Nginx + HTTPS（用 Let's Encrypt）
- 测试各个接口的公网访问

**Day 70（6h）**：
- 整理所有项目代码
- 写完整的部署文档（README）
- 录制演示视频（可选）

---

## Phase 4 总结

完成本阶段后,你将具备：

| 能力 | 水平 |
|:---|:---|
| Docker 容器化 | 能编写 Dockerfile 和 docker-compose.yml |
| 服务部署 | 能将 AI 服务部署到公网 |
| 测试与 CI/CD | 能写单元测试,配置 GitHub Actions |
| 本地模型集成 | 能使用 Ollama 进行开发调试 |
| 日志与监控 | 能配置基础的日志系统 |

**下一步**：Phase 5 Agent 开发,构建智能体系统。



---

## Week 9（第 64-70 天）：数据库与持久化

### Day 64（周一，2h）：PostgreSQL 基础

**为什么需要数据库？**
- Redis 适合缓存，但不适合持久化用户数据
- 需要存储：用户信息、会话历史、文档元数据、API 调用记录

```bash
# 安装 PostgreSQL（Docker）
docker run -d \
  --name postgres \
  -e POSTGRES_PASSWORD=mysecret \
  -e POSTGRES_DB=rag_db \
  -p 5432:5432 \
  postgres:15

# Python 客户端
pip install psycopg2-binary sqlalchemy
```

```python
import psycopg2

# 连接数据库
conn = psycopg2.connect(
    host="localhost",
    database="rag_db",
    user="postgres",
    password="mysecret"
)

# 创建表
cur = conn.cursor()
cur.execute("""
    CREATE TABLE users (
        id SERIAL PRIMARY KEY,
        username VARCHAR(50) UNIQUE NOT NULL,
        email VARCHAR(100) UNIQUE NOT NULL,
        created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
    )
""")
conn.commit()

# 插入数据
cur.execute(
    "INSERT INTO users (username, email) VALUES (%s, %s)",
    ("zhangsan", "zhang@example.com")
)
conn.commit()

# 查询
cur.execute("SELECT * FROM users")
print(cur.fetchall())
```

**今日检查点**：
- [ ] PostgreSQL 容器运行正常
- [ ] 能用 Python 连接并执行 SQL

---

### Day 65-66（周二-周三，各 2h）：SQLAlchemy ORM

```python
from sqlalchemy import create_engine, Column, Integer, String, DateTime, Text
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker
from datetime import datetime

# 数据库连接
DATABASE_URL = "postgresql://postgres:mysecret@localhost/rag_db"
engine = create_engine(DATABASE_URL)
SessionLocal = sessionmaker(bind=engine)
Base = declarative_base()

# 定义模型
class User(Base):
    __tablename__ = "users"
    
    id = Column(Integer, primary_key=True, index=True)
    username = Column(String(50), unique=True, nullable=False)
    email = Column(String(100), unique=True, nullable=False)
    created_at = Column(DateTime, default=datetime.utcnow)

class ChatSession(Base):
    __tablename__ = "chat_sessions"
    
    id = Column(Integer, primary_key=True)
    user_id = Column(Integer, nullable=False)
    question = Column(Text, nullable=False)
    answer = Column(Text, nullable=False)
    created_at = Column(DateTime, default=datetime.utcnow)

# 创建表
Base.metadata.create_all(engine)

# 使用 ORM
db = SessionLocal()

# 创建用户
new_user = User(username="lisi", email="li@example.com")
db.add(new_user)
db.commit()
db.refresh(new_user)

# 查询
user = db.query(User).filter(User.username == "lisi").first()
print(user.id, user.email)

# 保存对话历史
session = ChatSession(
    user_id=user.id,
    question="什么是 RAG？",
    answer="RAG 是检索增强生成..."
)
db.add(session)
db.commit()
```

**今日检查点**：
- [ ] 能用 ORM 定义模型并创建表
- [ ] 能执行增删改查操作

---

### Day 67（周四，2h）：数据库设计与索引

```python
from sqlalchemy import Index, ForeignKey
from sqlalchemy.orm import relationship

class Document(Base):
    __tablename__ = "documents"
    
    id = Column(Integer, primary_key=True)
    user_id = Column(Integer, ForeignKey("users.id"), nullable=False)
    filename = Column(String(255), nullable=False)
    file_size = Column(Integer)
    status = Column(String(20), default="processing")  # processing/completed/failed
    created_at = Column(DateTime, default=datetime.utcnow)
    
    # 关系
    user = relationship("User", backref="documents")
    
    # 索引
    __table_args__ = (
        Index('idx_user_created', 'user_id', 'created_at'),
        Index('idx_status', 'status'),
    )

# 查询优化示例
# 慢查询：全表扫描
docs = db.query(Document).filter(Document.status == "completed").all()

# 快查询：使用索引
docs = db.query(Document).filter(
    Document.user_id == 1,
    Document.status == "completed"
).order_by(Document.created_at.desc()).limit(10).all()
```

**数据库设计原则**：
- 主键：每张表必须有主键（通常用自增 ID）
- 外键：关联表之间用外键约束
- 索引：频繁查询的字段加索引（user_id, created_at, status）
- 规范化：避免数据冗余

**今日检查点**：
- [ ] 理解索引的作用
- [ ] 能设计用户-文档-会话的表结构

---

### Day 68-69（周五-周六，2h+6h）：集成到 FastAPI

```python
# database.py
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker, Session
from fastapi import Depends

DATABASE_URL = "postgresql://postgres:mysecret@localhost/rag_db"
engine = create_engine(DATABASE_URL, pool_pre_ping=True)
SessionLocal = sessionmaker(bind=engine)

def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

# main.py
from fastapi import FastAPI, Depends
from sqlalchemy.orm import Session

@app.post("/chat")
async def chat(request: ChatRequest, db: Session = Depends(get_db)):
    # 保存对话历史
    session = ChatSession(
        user_id=request.user_id,
        question=request.question,
        answer=answer
    )
    db.add(session)
    db.commit()
    
    return {"answer": answer}

@app.get("/history")
async def get_history(user_id: int, db: Session = Depends(get_db)):
    sessions = db.query(ChatSession).filter(
        ChatSession.user_id == user_id
    ).order_by(ChatSession.created_at.desc()).limit(20).all()
    
    return [{"question": s.question, "answer": s.answer} for s in sessions]
```

**今日检查点**：
- [ ] FastAPI 能连接数据库
- [ ] 对话历史能持久化并查询

---

### Day 70（周日，6h）：数据库迁移与备份

```bash
# 安装 Alembic（数据库迁移工具）
pip install alembic

# 初始化
alembic init alembic

# 生成迁移脚本
alembic revision --autogenerate -m "add user table"

# 执行迁移
alembic upgrade head

# 回滚
alembic downgrade -1
```

**数据备份**：
```bash
# 备份
docker exec postgres pg_dump -U postgres rag_db > backup.sql

# 恢复
docker exec -i postgres psql -U postgres rag_db < backup.sql
```

**Week 9 总结检查点**：
- [ ] 理解关系型数据库的作用
- [ ] 能用 SQLAlchemy ORM 操作数据库
- [ ] 能设计用户/文档/会话表结构
- [ ] FastAPI 集成数据库，对话历史持久化
- [ ] 里程碑 4 达成：RAG API 生产就绪（含数据库）

---

## Phase 4 总结

完成本阶段后，你将具备：

| 能力 | 水平 |
|:---|:---|
| Docker 容器化 | 能编写 Dockerfile 和 docker-compose.yml |
| 服务部署 | 能将 AI 服务部署到公网 |
| 测试与 CI/CD | 能写单元测试，配置 GitHub Actions |
| 数据库设计 | 能用 PostgreSQL + SQLAlchemy 设计表结构 |
| 数据持久化 | 用户数据、对话历史、文档元数据持久化 |

**下一步**：Phase 5 Agent 系统，构建能自主完成多步任务的 AI 智能体。
