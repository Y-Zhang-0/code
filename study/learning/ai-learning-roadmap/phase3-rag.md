# Phase 4：RAG 知识库系统

> **时间**：Week 5-8（第 29-56 天）
> **总学时**：88 小时
> **为什么在这里**：有了 LLM API + Redis 缓存基础，现在构建完整的 RAG 系统，从 Embedding 到检索到服务化到性能优化，一气呵成。

**本阶段目标**：
- 掌握 Embedding + 向量数据库核心原理
- 实现多格式文档解析与混合检索
- 构建生产级 RAG API 服务（FastAPI + Redis 缓存）
- 理解 RAG 质量评估与调优方法

---

## Week 5：Embedding 与向量数据库

### Day 29（周一，2h）：Embedding 原理与实践

**核心概念**：将文本转换为高维向量，语义相似的文本在向量空间中距离更近。

```python
from sentence_transformers import SentenceTransformer

# 使用多语言模型（支持中英日）
model = SentenceTransformer('BAAI/bge-m3')

texts = [
    "如何使用 Python 操作 Redis？",
    "Redis Python 客户端教程",
    "今天天气真好"
]

embeddings = model.encode(texts)
print(embeddings.shape)  # (3, 1024) - 每个文本变成 1024 维向量

# 计算相似度
from sklearn.metrics.pairwise import cosine_similarity
sim_matrix = cosine_similarity(embeddings)
print(sim_matrix)
# [[1.   0.85 0.12]
#  [0.85 1.   0.10]
#  [0.12 0.10 1.  ]]
```

**为什么选 bge-m3**：
- 支持 100+ 语言（中英日无缝切换）
- 8192 token 上下文（长文档友好）
- 开源免费，本地部署无 API 成本

**今日检查点**：
- [ ] 安装 `sentence-transformers`
- [ ] 对比中英文相似问题的 cosine 相似度 > 0.8

---

### Day 30（周二，2h）：ChromaDB 快速上手

ChromaDB 是最简单的向量数据库，零配置启动，适合快速原型。

```python
import chromadb
from chromadb.config import Settings

# 持久化到本地
client = chromadb.PersistentClient(path="./chroma_db")

# 创建集合（自动使用默认 embedding 函数）
collection = client.get_or_create_collection(
    name="knowledge_base",
    metadata={"hnsw:space": "cosine"}  # 使用余弦相似度
)

# 添加文档
collection.add(
    documents=[
        "Redis 是内存数据库，常用于缓存",
        "Python 的 redis-py 是官方推荐客户端",
        "FastAPI 是现代 Python Web 框架"
    ],
    ids=["doc1", "doc2", "doc3"]
)

# 查询
results = collection.query(
    query_texts=["如何用 Python 连接 Redis？"],
    n_results=2
)

print(results['documents'])      # 返回最相关的 2 个文档
print(results['distances'])      # 距离越小越相似
```

**今日检查点**：
- [ ] ChromaDB 能持久化并重启后恢复数据
- [ ] 查询结果按相似度排序

---

### Day 31（周三，2h）：文档分块策略

长文档不能直接 embed，需要切成小块（chunk）。

```python
from langchain.text_splitter import RecursiveCharacterTextSplitter

splitter = RecursiveCharacterTextSplitter(
    chunk_size=500,        # 每块最多 500 字符
    chunk_overlap=50,      # 块之间重叠 50 字符（保留上下文）
    separators=["\n\n", "\n", "。", ".", " ", ""]
)

text = """
Redis 是一个开源的内存数据结构存储系统。

它支持多种数据结构，包括字符串、哈希、列表、集合等。

Redis 常用于缓存、会话管理、实时排行榜等场景。
"""

chunks = splitter.split_text(text)
for i, chunk in enumerate(chunks):
    print(f"Chunk {i}: {chunk[:50]}...")
```

**分块参数调优**：
| 参数 | 推荐值 | 影响 |
|:---|:---|:---|
| chunk_size | 300-800 | 太小丢上下文，太大检索不精准 |
| chunk_overlap | 10-20% | 避免关键信息被切断 |
| separators | 按语言调整 | 中文优先 `。\n`，英文优先 `.\n` |

**今日检查点**：
- [ ] 对一篇长文档分块，检查块之间有重叠
- [ ] 调整 chunk_size，观察检索效果变化

---

### Day 32（周四，2h）：集成 Embedding 模型到 ChromaDB

ChromaDB 默认用 `all-MiniLM-L6-v2`（英文模型），需要替换成多语言模型。

```python
from chromadb.utils import embedding_functions

# 使用自定义 embedding 函数
embedding_fn = embedding_functions.SentenceTransformerEmbeddingFunction(
    model_name="BAAI/bge-m3"
)

collection = client.get_or_create_collection(
    name="multilang_kb",
    embedding_function=embedding_fn
)

# 添加中英日混合文档
collection.add(
    documents=[
        "Redis 是内存数据库",
        "Redis is an in-memory database",
        "Redis はインメモリデータベースです"
    ],
    ids=["zh", "en", "ja"]
)

# 用中文查询，能匹配到所有语言
results = collection.query(
    query_texts=["什么是 Redis？"],
    n_results=3
)
print(results['documents'])  # 应该返回三种语言的文档
```

**今日检查点**：
- [ ] 用中文查询能检索到英文/日文文档
- [ ] 相似度分数合理（同语言 > 0.7，跨语言 > 0.5）

---

### Day 33（周五，2h）：完整 RAG Pipeline v1

将 Embedding + 检索 + LLM 串起来。

```python
class SimpleRAG:
    def __init__(self, collection, llm_client):
        self.collection = collection
        self.llm = llm_client

    def query(self, question: str, top_k: int = 3) -> str:
        # 1. 检索相关文档
        results = self.collection.query(
            query_texts=[question],
            n_results=top_k
        )
        context = "\n\n".join(results['documents'][0])

        # 2. 构造 Prompt
        prompt = f"""根据以下参考资料回答问题：

参考资料：
{context}

问题：{question}

回答："""

        # 3. 调用 LLM
        return self.llm.complete(prompt)

# 使用
rag = SimpleRAG(collection, llm_client)
answer = rag.query("Redis 有哪些数据结构？")
print(answer)
```

**今日检查点**：
- [ ] 能回答知识库内的问题
- [ ] 知识库外的问题会回答"参考资料中未提及"

---

### Day 34-35（周末，6h×2）：多格式文档导入

**Day 34（6h）**：支持 PDF/Word/Markdown

```python
from langchain.document_loaders import (
    PyPDFLoader,
    Docx2txtLoader,
    UnstructuredMarkdownLoader
)

def load_document(file_path: str):
    ext = file_path.split('.')[-1].lower()
    
    loaders = {
        'pdf': PyPDFLoader,
        'docx': Docx2txtLoader,
        'md': UnstructuredMarkdownLoader
    }
    
    if ext not in loaders:
        raise ValueError(f"不支持的文件格式：{ext}")
    
    loader = loaders[ext](file_path)
    documents = loader.load()
    
    # 分块
    splitter = RecursiveCharacterTextSplitter(
        chunk_size=500,
        chunk_overlap=50
    )
    chunks = splitter.split_documents(documents)
    
    # 添加到向量库
    collection.add(
        documents=[chunk.page_content for chunk in chunks],
        metadatas=[chunk.metadata for chunk in chunks],
        ids=[f"{file_path}_{i}" for i in range(len(chunks))]
    )

# 批量导入
import glob
for file in glob.glob("docs/**/*.pdf", recursive=True):
    load_document(file)
```

**Day 35（6h）**：支持 Excel/CSV 表格

```python
import pandas as pd

def load_excel(file_path: str):
    df = pd.read_excel(file_path)
    
    # 每行转成一段文本
    documents = []
    for idx, row in df.iterrows():
        text = " | ".join([f"{col}: {val}" for col, val in row.items()])
        documents.append(text)
    
    collection.add(
        documents=documents,
        metadatas=[{"source": file_path, "row": idx} for idx in range(len(df))],
        ids=[f"{file_path}_row{idx}" for idx in range(len(df))]
    )

# 示例：员工信息表
# | 姓名 | 部门 | 职位 |
# | 张三 | 技术部 | 工程师 |
# 转成："姓名: 张三 | 部门: 技术部 | 职位: 工程师"
```

**Week 5 总结检查点**：
- [ ] 理解 Embedding 原理，能计算文本相似度
- [ ] ChromaDB 能持久化并查询
- [ ] 实现完整 RAG Pipeline（检索 + Prompt + LLM）
- [ ] 支持 5 种文档格式导入（PDF/Word/MD/Excel/CSV）

---

## Week 6：RAG 进阶检索

### Day 36（周一，2h）：混合检索（Hybrid Search）

单纯向量检索会漏掉关键词匹配，混合检索 = 向量检索 + BM25 关键词检索。

```python
from rank_bm25 import BM25Okapi
import numpy as np

class HybridRetriever:
    def __init__(self, collection, documents):
        self.collection = collection
        self.documents = documents
        
        # 构建 BM25 索引
        tokenized_docs = [doc.split() for doc in documents]
        self.bm25 = BM25Okapi(tokenized_docs)
    
    def search(self, query: str, top_k: int = 5, alpha: float = 0.5):
        # 1. 向量检索
        vector_results = self.collection.query(
            query_texts=[query],
            n_results=top_k * 2
        )
        
        # 2. BM25 关键词检索
        tokenized_query = query.split()
        bm25_scores = self.bm25.get_scores(tokenized_query)
        
        # 3. 归一化分数并融合
        vector_scores = 1 - np.array(vector_results['distances'][0])
        vector_scores = vector_scores / vector_scores.max()
        bm25_scores = bm25_scores / bm25_scores.max()
        
        # 加权融合
        final_scores = alpha * vector_scores + (1 - alpha) * bm25_scores
        top_indices = np.argsort(final_scores)[-top_k:][::-1]
        
        return [self.documents[i] for i in top_indices]
```

**alpha 参数调优**：
- `alpha=1.0`：纯向量检索（语义理解强）
- `alpha=0.5`：平衡模式
- `alpha=0.0`：纯关键词检索（精确匹配强）

**今日检查点**：
- [ ] 对比纯向量检索和混合检索的召回率
- [ ] 调整 alpha 参数，找到最佳平衡点


---

## Week 7（第 43-49 天）：FastAPI 服务化 + Redis 缓存优化

### Day 43-44（周一-周二，各 2h）：FastAPI 基础

```bash
pip install fastapi uvicorn python-multipart
```

```python
# app/main.py
from fastapi import FastAPI, UploadFile, File, HTTPException
from pydantic import BaseModel

app = FastAPI(title="RAG 知识库 API")

class ChatRequest(BaseModel):
    question: str
    top_k: int = 3

class ChatResponse(BaseModel):
    answer: str
    sources: list[str]

@app.get("/health")
def health():
    return {"status": "ok"}

@app.post("/documents/upload")
async def upload_document(file: UploadFile = File(...)):
    allowed = ["pdf", "docx", "txt", "md"]
    ext = file.filename.split(".")[-1].lower()
    if ext not in allowed:
        raise HTTPException(status_code=400, detail=f"不支持的格式：{ext}")
    
    # 保存并处理文档
    content = await file.read()
    # ... 导入向量库逻辑
    
    return {"message": f"已成功导入：{file.filename}"}

@app.post("/chat", response_model=ChatResponse)
async def chat(request: ChatRequest):
    # RAG 逻辑
    return ChatResponse(answer="回答", sources=["来源1"])

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000, reload=True)
```

**今日检查点**：
- [ ] FastAPI 服务启动，访问 http://localhost:8000/docs 看到 Swagger 文档
- [ ] 能上传文档并调用问答接口

---

### Day 45-46（周三-周四，各 2h）：流式响应

```python
from fastapi.responses import StreamingResponse

@app.post("/chat/stream")
async def chat_stream(request: ChatRequest):
    async def generate():
        # 检索
        context = retrieve(request.question)
        
        # 流式生成
        async for chunk in llm.astream([...]):
            yield f"data: {chunk.content}\n\n"
        
        yield "data: [DONE]\n\n"
    
    return StreamingResponse(generate(), media_type="text/event-stream")
```

**今日检查点**：
- [ ] 流式接口能逐字返回，前端可以实时显示

---

### Day 47（周五，2h）：错误处理与中间件

```python
from fastapi import Request
from fastapi.responses import JSONResponse
from fastapi.middleware.cors import CORSMiddleware

# 全局异常处理
@app.exception_handler(Exception)
async def global_exception_handler(request: Request, exc: Exception):
    return JSONResponse(status_code=500, content={"detail": str(exc)})

# CORS
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_methods=["*"],
    allow_headers=["*"],
)
```

---

### Day 48（周六，6h）：完整 RAG API 上线

整合所有组件，用 Postman 测试所有接口。

**今日检查点**：
- [ ] 所有接口正常工作
- [ ] 错误情况有友好提示

---

### Day 49（周日，6h）：性能分析 + Redis 缓存

**问题发现**：相同问题重复调用 LLM，浪费 token 和时间。

**解决方案**：引入 Redis 缓存。

```bash
# 安装 Redis
docker run -d -p 6379:6379 --name redis redis
pip install redis
```

```python
# cache/llm_cache.py
import hashlib
import json
import redis

r = redis.Redis(host='localhost', port=6379, decode_responses=True)

class CachedLLMClient:
    def __init__(self, llm_client, ttl: int = 3600):
        self.llm = llm_client
        self.r = r
        self.ttl = ttl
    
    def _cache_key(self, prompt: str) -> str:
        return "llm:" + hashlib.sha256(prompt.encode()).hexdigest()[:16]
    
    def complete(self, prompt: str) -> str:
        key = self._cache_key(prompt)
        
        cached = self.r.get(key)
        if cached:
            print("[缓存命中] 节省一次 API 调用")
            return cached
        
        response = self.llm.complete(prompt)
        self.r.set(key, response, ex=self.ttl)
        return response
```

```python
# cache/embedding_cache.py
class CachedEmbeddingProvider:
    def __init__(self, model, ttl: int = 86400):
        self.model = model
        self.r = r
        self.ttl = ttl
    
    def encode(self, text: str) -> list[float]:
        key = "emb:" + hashlib.sha256(text.encode()).hexdigest()[:16]
        
        cached = self.r.get(key)
        if cached:
            return json.loads(cached)
        
        vector = self.model.encode(text).tolist()
        self.r.set(key, json.dumps(vector), ex=self.ttl)
        return vector
```

**API 限流**：

```python
# middleware/rate_limit.py
import time

class RateLimiter:
    def __init__(self, max_requests: int = 20, window: int = 60):
        self.max_requests = max_requests
        self.window = window
    
    def is_allowed(self, user_id: str) -> bool:
        key = f"rate:{user_id}"
        now = time.time()
        
        pipe = r.pipeline()
        pipe.zremrangebyscore(key, 0, now - self.window)
        pipe.zcard(key)
        pipe.zadd(key, {str(now): now})
        pipe.expire(key, self.window)
        results = pipe.execute()
        
        return results[1] < self.max_requests
```

**缓存三大问题**：

| 问题 | 场景 | 解决方案 |
|:---|:---|:---|
| 穿透 | 查询不存在的文档 | 缓存空值 + 短 TTL |
| 雪崩 | 大批文档同时过期 | TTL 加随机抖动 |
| 击穿 | 热门问题缓存失效 | 分布式锁 / 逻辑过期 |

**今日检查点**：
- [ ] Redis 缓存命中率 > 30%
- [ ] 相同问题第二次查询速度提升 10 倍
- [ ] API 限流生效

---

## Week 8（第 50-56 天）：RAG 质量评估与调优

### Day 50-51（周一-周二，各 2h）：RAGAs 评估框架

```bash
pip install ragas datasets
```

```python
from ragas import evaluate
from ragas.metrics import (
    answer_relevancy,
    faithfulness,
    context_recall,
    context_precision,
)
from datasets import Dataset

# 构建评估数据集
eval_data = {
    "question": ["Python 是什么？", "LangChain 有什么用？"],
    "answer": ["Python 是...", "LangChain 是..."],
    "contexts": [["相关段落1", "段落2"], ["段落3"]],
    "ground_truth": ["Python 是高级语言...", "LangChain 用于..."]
}
dataset = Dataset.from_dict(eval_data)

result = evaluate(dataset, metrics=[
    answer_relevancy, faithfulness, context_recall, context_precision
])
print(result)
```

**今日检查点**：
- [ ] 能运行 RAGAs 评估
- [ ] 理解四个指标的含义

---

### Day 52-54（周三-周五，各 2h）：系统调优实践

**常见问题诊断**：

| 问题 | 诊断方法 | 解决方案 |
|:---|:---|:---|
| 明明有答案但检索不到 | 检查 context_recall | 增大 chunk_overlap，用混合检索 |
| 检索到内容但回答错 | 检查 faithfulness | 优化 System Prompt |
| 回答和问题不相关 | 检查 answer_relevancy | 改进 Prompt，用 CoT |
| 专有名词检索差 | 对比关键词 vs 向量 | 加入 BM25 混合检索 |

**向量库文档同步**：

```python
from langchain.indexes import SQLRecordManager, index

record_manager = SQLRecordManager(
    namespace="chroma/my_docs",
    db_url="sqlite:///record_manager.db"
)
record_manager.create_schema()

# 增量同步
result = index(
    docs_source=new_documents,
    record_manager=record_manager,
    vector_store=vectordb,
    cleanup="incremental",
    source_id_key="source",
)
```

**今日检查点**：
- [ ] 找出检索失败的案例并优化
- [ ] RAGAs 分数提升 10%+

---

### Day 55-56（周末，6h×2）：Phase 4 收尾

**Day 55（6h）**：
- 优化 RAG 系统，对比调优前后的 RAGAs 分数
- 元数据过滤优化
- Prompt 调优

**Day 56（6h）**：
- 代码整理、文档补全
- 推送 GitHub
- 录制演示视频（可选）

**Week 8 总结检查点**：
- [ ] RAG API 完整可用
- [ ] Redis 缓存生效，性能提升明显
- [ ] 能用 RAGAs 评估并改善检索质量
- [ ] 里程碑 3 达成：RAG API + Redis 缓存就绪

---

## Phase 4 总结

完成本阶段后，你将具备：

| 能力 | 水平 |
|:---|:---|
| Embedding 原理 | 理解向量化和语义相似度 |
| 向量数据库 | 能用 ChromaDB 构建知识库 |
| 文档解析 | 支持 5 种格式（PDF/Word/MD/Excel/CSV）|
| 混合检索 | 向量 + BM25 + Rerank |
| FastAPI 服务 | 能构建生产级 API |
| Redis 缓存 | LLM/Embedding 缓存，API 限流 |
| RAG 评估 | 能用 RAGAs 量化检索质量 |

**下一步**：Phase 5 工程化基础，将 RAG 服务容器化部署上线。
