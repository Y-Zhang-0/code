# Phase 1：Python 速通（全栈开发者版）

> **时间**：Week 1（第 1-3 天，约 6 小时）
> **前提**：已有编程经验（Java/Node.js/Vue）
> **目标**：掌握 Python 与 AI 开发强相关的特有语法，跳过通用概念

---

## 跳过内容（你已掌握）

- 变量、数据类型、循环、条件、函数 → 和 Java/JS 概念一致
- HTTP 请求、JSON 处理 → 和 axios/fetch/RestTemplate 一致
- 异步编程概念 → 和 Node.js async/await 一致
- 包管理（pip = npm）、虚拟环境（venv = node_modules 隔离）

---

## Day 1（2h）：Python 特有语法速通

### 必须掌握的 Python 特有写法

**类型注解（Type Hints）— FastAPI/Pydantic 强依赖**

```python
# Java: String name, int age
# Python 类型注解
def greet(name: str, age: int) -> str:
    return f"Hello {name}, you are {age}"

# 复杂类型
from typing import Optional, Union
from list import List  # Python 3.9+ 可直接用 list[str]

def process(items: list[str], limit: Optional[int] = None) -> dict[str, int]:
    pass

# Pydantic 模型（FastAPI 的核心）— 类似 Java Bean + 校验
from pydantic import BaseModel, Field

class ChatRequest(BaseModel):
    question: str
    top_k: int = Field(default=3, ge=1, le=10)
    session_id: Optional[str] = None
```

**f-string 和多行字符串（Prompt 模板必用）**

```python
name = "张三"
# f-string（类似 JS 模板字符串）
greeting = f"你好，{name}！"

# 多行字符串 — 写 Prompt 模板时极常用
system_prompt = """
你是一个专业的技术文档助手。

规则：
1. 只基于提供的参考资料回答
2. 不知道时直接说不知道
3. 回答使用 Markdown 格式

参考资料：
{context}

用户问题：{question}
""".strip()

# 使用
prompt = system_prompt.format(context="...", question="...")
```

**列表/字典推导式（处理 LLM 返回数据常用）**

```python
# 类似 JS 的 .map() .filter()
docs = ["doc1", "doc2", "doc3"]

# map
upper = [d.upper() for d in docs]

# filter
filtered = [d for d in docs if len(d) > 4]

# 字典推导
scores = {doc: len(doc) for doc in docs}

# 真实场景：处理检索结果
chunks = [
    {"content": r.page_content, "source": r.metadata.get("source", "")}
    for r in retrieval_results
    if r.metadata.get("score", 0) > 0.7
]
```

**解包和 * / ** 操作符**

```python
# 函数接受任意参数（LangChain 内部大量使用）
def build_prompt(*args, **kwargs):
    print(args)    # tuple
    print(kwargs)  # dict

build_prompt("role", "user", role="系统", task="总结")

# 字典合并（Python 3.9+）
base = {"model": "gpt-4", "temperature": 0.7}
override = {"temperature": 0, "max_tokens": 500}
merged = {**base, **override}  # {'model': 'gpt-4', 'temperature': 0, 'max_tokens': 500}
```

**pathlib（替代 os.path，现代写法）**

```python
from pathlib import Path

# 替代 os.path.join
uploads = Path("./uploads")
file_path = uploads / "document.pdf"  # 路径拼接用 /

# 常用操作
print(file_path.suffix)    # .pdf
print(file_path.stem)      # document
print(file_path.exists())  # True/False

# 创建目录
uploads.mkdir(parents=True, exist_ok=True)

# 遍历目录
for f in uploads.glob("*.pdf"):
    print(f)
```

### 今日检查点

- [ ] 能写带类型注解的函数
- [ ] 能用 Pydantic 定义数据模型
- [ ] 能写 Prompt 模板（多行字符串 + format）
- [ ] 理解 pathlib 基本操作

---

## Day 2（2h）：Python 异步 + 虚拟环境实践

### async/await 与 Node.js 的差异

```python
# Node.js 风格（你熟悉的）
# async function fetchData() { return await axios.get(url) }

# Python 风格（几乎一样，但需要 asyncio.run 启动）
import asyncio
import aiohttp

async def fetch_data(url: str) -> dict:
    async with aiohttp.ClientSession() as session:
        async with session.get(url) as response:
            return await response.json()

async def main():
    # 并发执行（类似 Promise.all）
    results = await asyncio.gather(
        fetch_data("https://api1.example.com"),
        fetch_data("https://api2.example.com"),
    )
    return results

# 启动（脚本入口，类似 Node 直接运行）
asyncio.run(main())

# FastAPI 中不需要 asyncio.run，框架自动处理
# @app.get("/data")
# async def get_data():   ← 直接写 async def 即可
#     return await fetch_data(url)
```

**Python 装饰器（LangChain 大量使用）**

```python
# 类似 Java 注解 / NestJS 装饰器，但更灵活
from functools import wraps, lru_cache

# 缓存装饰器（AI 应用中缓存 embedding 计算结果）
@lru_cache(maxsize=1000)
def get_embedding(text: str) -> tuple:
    # 只计算一次，后续从缓存返回
    return embedding_model.encode(text)

# 自定义装饰器
def retry(max_times: int = 3):
    def decorator(func):
        @wraps(func)
        async def wrapper(*args, **kwargs):
            for i in range(max_times):
                try:
                    return await func(*args, **kwargs)
                except Exception as e:
                    if i == max_times - 1:
                        raise
                    await asyncio.sleep(2 ** i)
        return wrapper
    return decorator

@retry(max_times=3)
async def call_llm(prompt: str) -> str:
    ...
```

**虚拟环境（对应 Node.js 的 node_modules）**

```bash
# 创建（每个项目单独创建，等同于 npm init）
python -m venv venv

# 激活
# Windows: venv\Scripts\activate
# Mac/Linux: source venv/bin/activate

# 安装依赖（等同于 npm install）
pip install langchain fastapi chromadb

# 导出依赖（等同于 package.json）
pip freeze > requirements.txt

# 从依赖文件安装（等同于 npm install）
pip install -r requirements.txt

# 2025 推荐：uv（速度是 pip 的 10-100x，类似 pnpm）
# pip install uv
# uv venv && uv pip install -r requirements.txt
```

### 今日检查点

- [ ] 理解 Python async/await 与 Node.js 的区别
- [ ] 能使用装饰器（特别是 @lru_cache）
- [ ] 虚拟环境创建和依赖管理流程熟悉

---

## Day 3（2h）：AI 开发常用模式 + 环境搭建

### 单例模式（AI 应用中极常用）

```python
# 问题：嵌入模型、向量库初始化耗时，不能每次请求都新建
# 解决：模块级单例 + lru_cache

from functools import lru_cache
from sentence_transformers import SentenceTransformer

# 方式1：模块级变量（最简单）
_model = None

def get_model():
    global _model
    if _model is None:
        _model = SentenceTransformer("BAAI/bge-m3")
    return _model

# 方式2：lru_cache（更 Pythonic，FastAPI 推荐）
@lru_cache()
def get_settings():
    return Settings()  # 只初始化一次

# FastAPI 依赖注入
from fastapi import Depends

def get_rag_engine(settings=Depends(get_settings)):
    return RAGEngine(settings)
```

**上下文管理器（with 语句）**

```python
# Python 的 try-finally 语法糖
# 你在 Java 里用 try-with-resources，Python 用 with

# 文件操作
with open("file.txt", "r", encoding="utf-8") as f:
    content = f.read()
# f 自动关闭，等同于 finally { f.close() }

# 自定义上下文管理器
from contextlib import contextmanager

@contextmanager
def timer(name: str):
    import time
    start = time.time()
    yield
    elapsed = time.time() - start
    print(f"{name} 耗时: {elapsed:.2f}s")

with timer("向量化"):
    embeddings = model.encode(texts)
```

### 开发工具配置

```bash
# 安装必要工具
pip install python-dotenv   # .env 文件读取
pip install httpx           # 现代 HTTP 客户端（替代 requests，支持 async）
pip install rich            # 终端美化输出（调试 AI 应用时很有用）
pip install pytest pytest-asyncio  # 测试框架

# VS Code 推荐插件（你可能已有）
# Python（Microsoft）
# Pylance（类型检查）
# Ruff（格式化，替代 Black+flake8）
```

**.env 配置**

```bash
# .env 文件
ZHIPU_API_KEY=your_key_here
OPENAI_API_KEY=your_key_here
LLM_PROVIDER=ollama
OLLAMA_BASE_URL=http://localhost:11434
```

```python
# 在代码中读取
from dotenv import load_dotenv
import os

load_dotenv()  # 读取 .env 文件
api_key = os.getenv("ZHIPU_API_KEY")
```

### 本周里程碑

```python
# 用 5 行 Python 写一个调用公开 API 的小脚本（用你学到的类型注解和 async）
import asyncio
import httpx

async def get_ip_info() -> dict[str, str]:
    async with httpx.AsyncClient() as client:
        response = await client.get("https://httpbin.org/ip")
        return response.json()

asyncio.run(get_ip_info())
```

验收标准：
- [ ] 脚本带类型注解
- [ ] 使用 async/await
- [ ] 使用虚拟环境运行
- [ ] .env 文件管理密钥（即使这里不需要）

---

## 时间调整说明

> 全栈开发者 Phase 1 从 7 天缩短为 3 天（6小时）
> 节省的 16 小时可以：
> - 在 Phase 3 RAG 调优多花时间（检索质量是核心竞争力）
> - 在 Phase 4 LangGraph 多花时间（2025 年面试热点）

**下周预告**：直接进入 LLM API 调用，第一天就让大模型回复你。
