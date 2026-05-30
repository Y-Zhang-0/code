# Phase 6：并发优化

> **时间**：Week 13（第 92-98 天）
> **总学时**：22 小时
> **目标**：掌握 Python 并发编程,对现有 RAG/Agent 项目进行性能优化

---

## 本阶段里程碑

现有 RAG/Agent 项目性能优化完成：
- 批量文档处理速度提升 3 倍以上
- 理解 asyncio/threading/multiprocessing 的适用场景
- 能正确使用连接池和并发控制
- 能识别和解决常见并发问题

---

## Week 13（第 92-98 天）：Python 并发编程

### Day 92（周一，2h）：asyncio 深入

Python 并发三驾马车：

| 方式 | 适用场景 | AI 应用场景 |
|:---|:---|:---|
| `asyncio` | I/O 密集型（等待网络/磁盘）| 并发调用多个 LLM API |
| `threading` | I/O 密集型,需要 blocking 库 | 调用不支持 async 的第三方库 |
| `multiprocessing` | CPU 密集型（绕过 GIL）| 批量向量计算、PDF 解析 |

```python
import asyncio

# 顺序调用（慢）
async def ask_sequential(questions: list[str]) -> list[str]:
    results = []
    for q in questions:
        result = await llm_client.ask(q)  # 每个等待约 2 秒
        results.append(result)
    return results  # 10 个问题 = 20 秒

# 并发调用（快）
async def ask_concurrent(questions: list[str]) -> list[str]:
    tasks = [llm_client.ask(q) for q in questions]
    return await asyncio.gather(*tasks)  # 10 个问题 ≈ 2 秒

# 带并发限制（避免触发 API 限流）
async def ask_with_semaphore(questions: list[str], max_concurrent=5):
    semaphore = asyncio.Semaphore(max_concurrent)

    async def ask_one(q):
        async with semaphore:
            return await llm_client.ask(q)

    return await asyncio.gather(*[ask_one(q) for q in questions])
```

**今日检查点**：
- [ ] 理解 asyncio.gather 的并发执行原理
- [ ] 能用 Semaphore 限制并发数

---

### Day 93（周二，2h）：GIL 与 threading

```python
import threading
from queue import Queue

# 场景：用 sentence-transformers 批量计算 embedding（库不支持 async）
def batch_embed_threaded(texts: list[str], num_workers=4):
    result_queue = Queue()
    chunk_size = len(texts) // num_workers

    def worker(chunk, offset):
        vectors = embedding_model.encode(chunk)
        result_queue.put((offset, vectors))

    threads = []
    for i in range(num_workers):
        chunk = texts[i * chunk_size: (i + 1) * chunk_size]
        t = threading.Thread(target=worker, args=(chunk, i * chunk_size))
        threads.append(t)
        t.start()

    for t in threads:
        t.join()

    # 按顺序合并结果
    results = [None] * len(texts)
    while not result_queue.empty():
        offset, vectors = result_queue.get()
        for j, v in enumerate(vectors):
            results[offset + j] = v

    return results
```

**GIL（全局解释器锁）**：
- Python 同一时刻只有一个线程执行 Python 字节码
- I/O 等待期间 GIL 会释放,所以 threading 对 I/O 密集有效
- CPU 密集型必须用 multiprocessing 绕过 GIL

---

### Day 94（周三，2h）：连接池

```python
# HTTP 连接池（调用外部 API 时复用连接）
import httpx

# 错误：每次请求都创建新的客户端（不复用连接）
async def bad_call():
    async with httpx.AsyncClient() as client:
        return await client.get(url)

# 正确：全局共享一个客户端实例
http_client = httpx.AsyncClient(limits=httpx.Limits(max_connections=100))

async def good_call():
    return await http_client.get(url)
```

```python
# 数据库连接池（以 PostgreSQL 为例）
from sqlalchemy.ext.asyncio import create_async_engine, AsyncSession
from sqlalchemy.orm import sessionmaker

# 创建引擎时配置连接池
engine = create_async_engine(
    "postgresql+asyncpg://user:pass@localhost/db",
    pool_size=20,           # 连接池大小
    max_overflow=10,        # 超出 pool_size 时最多额外创建的连接数
    pool_timeout=30,        # 获取连接的超时时间
    pool_recycle=3600,      # 连接回收时间（秒）
)

async_session = sessionmaker(
    engine, class_=AsyncSession, expire_on_commit=False
)

# 使用
async def get_data():
    async with async_session() as session:
        result = await session.execute(query)
        return result.scalars().all()
```

**今日检查点**：
- [ ] 理解连接池的作用（复用连接,避免频繁创建销毁）
- [ ] 能配置 HTTP 和数据库连接池

---

### Day 95（周四，2h）：并发问题与锁

```python
import asyncio

# 竞态条件示例
counter = 0

async def increment_unsafe():
    global counter
    val = counter
    await asyncio.sleep(0)
    counter = val + 1  # 可能基于旧值

# 解决：使用 asyncio.Lock
lock = asyncio.Lock()

async def increment_safe():
    global counter
    async with lock:
        val = counter
        await asyncio.sleep(0)
        counter = val + 1
```

```python
# 死锁示例（两个锁互相等待）
lock_a = asyncio.Lock()
lock_b = asyncio.Lock()

async def task1():
    async with lock_a:
        await asyncio.sleep(0.1)
        async with lock_b:  # 等待 lock_b
            pass

async def task2():
    async with lock_b:
        await asyncio.sleep(0.1)
        async with lock_a:  # 等待 lock_a
            pass

# 避免死锁：统一锁的获取顺序
```

**常见并发问题**：
- **竞态条件**：多个协程/线程同时修改共享变量
- **死锁**：两个任务互相等待对方释放资源
- **资源泄漏**：连接/文件未正确关闭

**解决方案**：
- 使用锁保护共享资源
- 统一锁的获取顺序
- 使用 `async with` 确保资源释放

---

### Day 96-98（周五-周末，2h+6h+6h）：实战 — 批量文档处理加速

**目标**：改造 RAG 项目的文档摄入流程,实现批量处理加速。

#### Day 96（周五，2h）：性能基准测试

```python
# benchmark.py — 测试当前性能
import time
from pathlib import Path

def benchmark_ingest(doc_paths: list[Path]):
    start = time.time()

    # 当前实现（顺序处理）
    for path in doc_paths:
        loader = get_loader(path)
        docs = loader.load()
        chunks = text_splitter.split_documents(docs)
        vector_store.add_documents(chunks)

    elapsed = time.time() - start
    print(f"处理 {len(doc_paths)} 个文档耗时：{elapsed:.2f} 秒")
    return elapsed

# 准备测试数据（10 个 PDF）
test_docs = list(Path("test_data").glob("*.pdf"))
baseline = benchmark_ingest(test_docs)
```

**今日检查点**：
- [ ] 记录当前性能基准（10 个文档的处理时间）
- [ ] 识别性能瓶颈（文档解析 vs 向量计算 vs 数据库写入）

---

#### Day 97（周六，6h）：并发优化实现

**策略 1：并发文档解析（I/O 密集）**

```python
import asyncio
from concurrent.futures import ThreadPoolExecutor

# 文档解析通常是 I/O 密集（读取文件）
async def load_documents_concurrent(doc_paths: list[Path]) -> list:
    loop = asyncio.get_event_loop()
    executor = ThreadPoolExecutor(max_workers=4)

    def load_one(path):
        loader = get_loader(path)
        return loader.load()

    tasks = [
        loop.run_in_executor(executor, load_one, path)
        for path in doc_paths
    ]

    results = await asyncio.gather(*tasks)
    return [doc for docs in results for doc in docs]  # 展平
```

**策略 2：批量向量计算（CPU 密集）**

```python
# 使用 sentence-transformers 的批量接口
def embed_documents_batch(texts: list[str], batch_size=32):
    """批量计算 embedding,利用 GPU 加速"""
    all_embeddings = []

    for i in range(0, len(texts), batch_size):
        batch = texts[i:i + batch_size]
        embeddings = embedding_model.encode(
            batch,
            batch_size=batch_size,
            show_progress_bar=False
        )
        all_embeddings.extend(embeddings)

    return all_embeddings
```

**策略 3：批量写入向量库**

```python
# 改造 VectorStore.add_documents
def add_documents_batch(self, documents: list[Document], batch_size=100):
    """批量写入,减少数据库往返次数"""
    doc_ids = []

    for i in range(0, len(documents), batch_size):
        batch = documents[i:i + batch_size]
        texts = [doc.page_content for doc in batch]
        metadatas = [doc.metadata for doc in batch]

        # 批量计算 embedding
        embeddings = self.embedding_function.embed_documents(texts)

        # 批量写入
        ids = self.collection.add(
            documents=texts,
            embeddings=embeddings,
            metadatas=metadatas,
        )
        doc_ids.extend(ids)

    return doc_ids
```

**整合优化后的流程**

```python
async def ingest_documents_optimized(doc_paths: list[Path]):
    # 1. 并发加载文档（I/O 密集）
    all_docs = await load_documents_concurrent(doc_paths)

    # 2. 分块
    chunks = text_splitter.split_documents(all_docs)

    # 3. 批量向量化 + 写入
    vector_store.add_documents_batch(chunks, batch_size=100)

# 性能测试
start = time.time()
asyncio.run(ingest_documents_optimized(test_docs))
optimized_time = time.time() - start

print(f"优化前：{baseline:.2f} 秒")
print(f"优化后：{optimized_time:.2f} 秒")
print(f"加速比：{baseline / optimized_time:.2f}x")
```

**今日检查点**：
- [ ] 实现并发文档加载
- [ ] 实现批量向量计算和写入
- [ ] 性能提升至少 2 倍

---

#### Day 98（周日，6h）：压测与调优

**压力测试**

```python
# stress_test.py
import asyncio
import time
from pathlib import Path

async def stress_test_concurrent_uploads(num_files=50):
    """模拟 50 个用户同时上传文档"""
    test_files = [Path(f"test_data/doc_{i}.pdf") for i in range(num_files)]

    start = time.time()

    tasks = [ingest_documents_optimized([f]) for f in test_files]
    await asyncio.gather(*tasks)

    elapsed = time.time() - start
    print(f"处理 {num_files} 个文档耗时：{elapsed:.2f} 秒")
    print(f"平均每个文档：{elapsed / num_files:.2f} 秒")

asyncio.run(stress_test_concurrent_uploads())
```

**监控与调优**

```python
# 添加性能监控
import logging
from functools import wraps

def log_performance(func):
    @wraps(func)
    async def wrapper(*args, **kwargs):
        start = time.time()
        result = await func(*args, **kwargs)
        elapsed = time.time() - start
        logging.info(f"{func.__name__} 耗时：{elapsed:.2f} 秒")
        return result
    return wrapper

@log_performance
async def load_documents_concurrent(doc_paths):
    ...
```

**调优参数**

| 参数 | 建议值 | 说明 |
|:---|:---|:---|
| ThreadPoolExecutor workers | 4-8 | 文档解析并发数 |
| embedding batch_size | 32-64 | 向量计算批次大小 |
| vector_store batch_size | 100-500 | 数据库写入批次大小 |
| asyncio Semaphore | 5-10 | API 调用并发限制 |

**今日检查点**：
- [ ] 完成压力测试
- [ ] 调优参数,达到最佳性能
- [ ] 文档化优化方案和性能数据

---

## Phase 6 总结

完成本阶段后,你将具备：

| 能力 | 水平 |
|:---|:---|
| asyncio 并发 | 能正确使用 gather/Semaphore 实现并发控制 |
| GIL 理解 | 能根据场景选择 asyncio/threading/multiprocessing |
| 连接池 | 能配置 HTTP 和数据库连接池 |
| 并发问题 | 能识别和解决竞态条件、死锁等问题 |
| 性能优化 | 能对 AI 应用进行性能分析和优化 |

**实战成果**：
- RAG 批量文档处理速度提升 3 倍以上
- 理解 AI 应用的性能瓶颈和优化策略
- 掌握并发编程的最佳实践

**下一步**：Phase 7 分布式架构,学习如何设计可扩展的 AI 服务。


---

## Week 14（第 99-105 天）：认证授权与安全

### Day 99（周一，2h）：JWT 认证基础

```bash
pip install python-jose[cryptography] passlib[bcrypt]
```

```python
from datetime import datetime, timedelta
from jose import JWTError, jwt
from passlib.context import CryptContext

SECRET_KEY = "your-secret-key-keep-it-safe"
ALGORITHM = "HS256"
ACCESS_TOKEN_EXPIRE_MINUTES = 30

pwd_context = CryptContext(schemes=["bcrypt"], deprecated="auto")

def create_access_token(data: dict):
    to_encode = data.copy()
    expire = datetime.utcnow() + timedelta(minutes=ACCESS_TOKEN_EXPIRE_MINUTES)
    to_encode.update({"exp": expire})
    return jwt.encode(to_encode, SECRET_KEY, algorithm=ALGORITHM)

def verify_token(token: str):
    try:
        payload = jwt.decode(token, SECRET_KEY, algorithms=[ALGORITHM])
        return payload
    except JWTError:
        return None

def hash_password(password: str):
    return pwd_context.hash(password)

def verify_password(plain_password: str, hashed_password: str):
    return pwd_context.verify(plain_password, hashed_password)
```

**今日检查点**：
- [ ] 理解 JWT 的结构（Header.Payload.Signature）
- [ ] 能生成和验证 JWT token

---

### Day 100-101（周二-周三，各 2h）：用户注册与登录

```python
from fastapi import FastAPI, Depends, HTTPException, status
from fastapi.security import OAuth2PasswordBearer, OAuth2PasswordRequestForm
from pydantic import BaseModel, EmailStr

oauth2_scheme = OAuth2PasswordBearer(tokenUrl="token")

class UserCreate(BaseModel):
    username: str
    email: EmailStr
    password: str

class Token(BaseModel):
    access_token: str
    token_type: str

@app.post("/register")
async def register(user: UserCreate, db: Session = Depends(get_db)):
    # 检查用户是否存在
    existing = db.query(User).filter(User.username == user.username).first()
    if existing:
        raise HTTPException(status_code=400, detail="用户名已存在")
    
    # 创建用户
    hashed_pwd = hash_password(user.password)
    new_user = User(
        username=user.username,
        email=user.email,
        hashed_password=hashed_pwd
    )
    db.add(new_user)
    db.commit()
    
    return {"message": "注册成功"}

@app.post("/token", response_model=Token)
async def login(
    form_data: OAuth2PasswordRequestForm = Depends(),
    db: Session = Depends(get_db)
):
    # 验证用户
    user = db.query(User).filter(User.username == form_data.username).first()
    if not user or not verify_password(form_data.password, user.hashed_password):
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="用户名或密码错误"
        )
    
    # 生成 token
    access_token = create_access_token(data={"sub": user.username})
    return {"access_token": access_token, "token_type": "bearer"}

async def get_current_user(
    token: str = Depends(oauth2_scheme),
    db: Session = Depends(get_db)
):
    payload = verify_token(token)
    if not payload:
        raise HTTPException(status_code=401, detail="无效的 token")
    
    username = payload.get("sub")
    user = db.query(User).filter(User.username == username).first()
    if not user:
        raise HTTPException(status_code=401, detail="用户不存在")
    
    return user

# 受保护的路由
@app.post("/chat")
async def chat(
    request: ChatRequest,
    current_user: User = Depends(get_current_user),
    db: Session = Depends(get_db)
):
    # 只有登录用户才能访问
    answer = rag_engine.query(request.question)
    
    # 保存到该用户的历史
    session = ChatSession(
        user_id=current_user.id,
        question=request.question,
        answer=answer
    )
    db.add(session)
    db.commit()
    
    return {"answer": answer}
```

**今日检查点**：
- [ ] 用户能注册和登录
- [ ] 登录后获得 JWT token
- [ ] 受保护的接口需要 token 才能访问

---

### Day 102（周四，2h）：权限控制

```python
from enum import Enum

class UserRole(str, Enum):
    ADMIN = "admin"
    USER = "user"
    GUEST = "guest"

class User(Base):
    __tablename__ = "users"
    
    id = Column(Integer, primary_key=True)
    username = Column(String(50), unique=True)
    role = Column(String(20), default=UserRole.USER)

def require_role(required_role: UserRole):
    def role_checker(current_user: User = Depends(get_current_user)):
        if current_user.role != required_role and current_user.role != UserRole.ADMIN:
            raise HTTPException(status_code=403, detail="权限不足")
        return current_user
    return role_checker

# 管理员接口
@app.delete("/documents/{doc_id}")
async def delete_document(
    doc_id: int,
    current_user: User = Depends(require_role(UserRole.ADMIN)),
    db: Session = Depends(get_db)
):
    # 只有管理员能删除文档
    doc = db.query(Document).filter(Document.id == doc_id).first()
    if not doc:
        raise HTTPException(status_code=404, detail="文档不存在")
    
    db.delete(doc)
    db.commit()
    return {"message": "删除成功"}
```

**今日检查点**：
- [ ] 能区分不同角色的用户
- [ ] 管理员接口有权限保护

---

### Day 103-104（周五-周六，2h+6h）：Session 管理与安全加固

```python
# Refresh Token 机制
REFRESH_TOKEN_EXPIRE_DAYS = 7

def create_refresh_token(data: dict):
    to_encode = data.copy()
    expire = datetime.utcnow() + timedelta(days=REFRESH_TOKEN_EXPIRE_DAYS)
    to_encode.update({"exp": expire})
    return jwt.encode(to_encode, SECRET_KEY, algorithm=ALGORITHM)

@app.post("/token/refresh")
async def refresh_token(refresh_token: str):
    payload = verify_token(refresh_token)
    if not payload:
        raise HTTPException(status_code=401, detail="无效的 refresh token")
    
    new_access_token = create_access_token(data={"sub": payload["sub"]})
    return {"access_token": new_access_token, "token_type": "bearer"}

# HTTPS 配置（生产环境）
# uvicorn main:app --ssl-keyfile=key.pem --ssl-certfile=cert.pem

# CORS 安全配置
from fastapi.middleware.cors import CORSMiddleware

app.add_middleware(
    CORSMiddleware,
    allow_origins=["https://yourdomain.com"],  # 生产环境指定域名
    allow_credentials=True,
    allow_methods=["GET", "POST"],
    allow_headers=["*"],
)

# SQL 注入防护（使用 ORM 自动防护）
# ✓ 安全：db.query(User).filter(User.username == username)
# ✗ 危险：db.execute(f"SELECT * FROM users WHERE username='{username}'")

# XSS 防护
from html import escape

def sanitize_input(text: str) -> str:
    return escape(text)
```

**今日检查点**：
- [ ] 实现 Refresh Token 机制
- [ ] 理解 HTTPS/CORS/SQL 注入/XSS 防护

---

### Day 105（周日，6h）：Week 14 总结与实践

**综合实践**：
- 完整的用户注册/登录流程
- JWT 认证保护所有 API
- 角色权限控制
- 安全加固（HTTPS/CORS/防注入）

**Week 14 总结检查点**：
- [ ] 用户能注册、登录、获取 token
- [ ] 所有 API 需要认证才能访问
- [ ] 管理员有额外权限
- [ ] 理解常见安全威胁及防护
- [ ] 里程碑 6 达成：并发优化 + 认证授权完成

---

## Phase 6 总结

完成本阶段后，你将具备：

| 能力 | 水平 |
|:---|:---|
| Python 并发 | 理解 asyncio/threading/GIL |
| 性能优化 | 能优化 I/O 密集和 CPU 密集任务 |
| 用户认证 | JWT 认证、注册登录、权限控制 |
| 安全防护 | HTTPS/CORS/SQL 注入/XSS 防护 |

**下一步**：Phase 7 分布式架构，学习 CAP 定理、无状态设计、负载均衡。
