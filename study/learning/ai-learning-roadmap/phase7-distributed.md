# Phase 7：分布式架构

> **时间**：Week 15-16（第 106-112 天）
> **总学时**：28 小时
> **目标**：掌握分布式系统基础理论,能设计可扩展的 AI 服务架构,在面试中讲述高并发系统设计方案

---

## 本阶段里程碑

- 理解 CAP 定理与一致性模型
- 掌握无状态服务设计原则
- 能实现分布式锁与负载均衡
- 能设计支持 10 万用户的 RAG 系统架构
- 整理完整的后端架构面试题库
- 绘制完整的系统架构图

---

## Week 15（第 106-112 天）：分布式基础与架构设计

### Day 106（周一,2h）：CAP 定理与一致性

#### CAP 定理核心

```
CAP 定理：分布式系统无法同时满足以下三点,只能取其二

C — Consistency（一致性）：所有节点同时看到相同数据
A — Availability（可用性）：每次请求都得到响应（不保证最新数据）
P — Partition Tolerance（分区容错）：网络故障时系统仍能运行

实际上 P 必须保留（网络故障是常态）,所以选择：
- CP（牺牲可用性）：如 ZooKeeper,选举期间不可用
- AP（牺牲强一致）：如 DynamoDB,可能读到旧数据（最终一致）
```

#### AI 应用的选择

**大多数场景选 AP（最终一致性）**：
- 读到稍旧的知识库可以接受
- 但服务不能停（可用性优先）

**一致性模型对比**

| 模型 | 保证 | 适用场景 |
|:---|:---|:---|
| 强一致性 | 读必定返回最新写入 | 金融交易、库存扣减 |
| 最终一致性 | 一段时间后所有节点一致 | 社交媒体点赞、知识库更新 |
| 因果一致性 | 有因果关系的操作保持顺序 | 聊天消息、评论回复 |

**RAG 系统的一致性需求**

```python
# 场景 1：文档上传后立即查询（可能查不到）
POST /documents/upload  # 写入节点 A
GET /chat?q="刚上传的文档内容"  # 读取节点 B（可能还未同步）

# 解决方案：
# 1. 同步等待索引完成（牺牲性能）
# 2. 返回"文档处理中"提示（用户体验更好）
# 3. 客户端轮询直到可查询

# 场景 2：多节点同时写入同一文档（冲突）
# 解决方案：分布式锁（Day 108 学习）
```

#### 今日检查点

- [ ] 理解 CAP 定理的权衡
- [ ] 能判断 AI 应用应选择 CP 还是 AP
- [ ] 理解最终一致性的含义

---

### Day 107（周二,2h）：无状态服务设计

#### 有状态 vs 无状态

```
有状态服务（不可水平扩展）：
用户 → 服务器A（存有该用户的会话）
                ↑ 用户必须打到同一台服务器

无状态服务（可水平扩展）：
用户 → 负载均衡 → 服务器A
                → 服务器B  ← 会话存在 Redis,任意服务器均可处理
                → 服务器C
```

#### 改造 AI 服务为无状态

**问题诊断**

```python
# 有状态的错误设计
class ChatService:
    def __init__(self):
        self.user_sessions = {}  # 存在内存中！

    def chat(self, user_id: str, message: str):
        if user_id not in self.user_sessions:
            self.user_sessions[user_id] = []
        self.user_sessions[user_id].append(message)
        # 如果用户下次请求打到另一台服务器,会话丢失！
```

**无状态改造方案**

```python
# 方案 1：会话存 Redis
import redis
import json

redis_client = redis.Redis(host='localhost', port=6379, decode_responses=True)

class StatelessChatService:
    def chat(self, user_id: str, message: str):
        # 从 Redis 读取历史
        key = f"session:{user_id}"
        history = json.loads(redis_client.get(key) or "[]")
        
        history.append({"role": "user", "content": message})
        
        # 调用 LLM
        response = llm.invoke(history)
        history.append({"role": "assistant", "content": response})
        
        # 写回 Redis（设置过期时间）
        redis_client.setex(key, 3600, json.dumps(history))
        
        return response

# 方案 2：上传文件存对象存储
from minio import Minio

minio_client = Minio(
    "minio.example.com",
    access_key="ACCESS_KEY",
    secret_key="SECRET_KEY"
)

@app.post("/documents/upload")
async def upload(file: UploadFile):
    # 错误：存本地磁盘（有状态）
    # with open(f"./uploads/{file.filename}", "wb") as f:
    #     f.write(await file.read())
    
    # 正确：存对象存储（无状态）
    file_id = str(uuid.uuid4())
    minio_client.put_object(
        "documents",
        f"{file_id}/{file.filename}",
        file.file,
        length=-1,
        part_size=10*1024*1024
    )
    
    return {"file_id": file_id, "url": f"s3://documents/{file_id}/{file.filename}"}
```

**无状态设计检查清单**

- [ ] 会话数据存外部存储（Redis/数据库）
- [ ] 文件存对象存储（MinIO/S3）
- [ ] 配置从环境变量读取
- [ ] 不依赖本地文件系统
- [ ] 任意实例可处理任意请求

#### 今日检查点

- [ ] 理解有状态服务的扩展性问题
- [ ] 能将会话存储改造为 Redis
- [ ] 理解对象存储的作用

---

### Day 108（周三,2h）：分布式锁

#### 为什么需要分布式锁？

```python
# 场景：多个 Worker 同时处理文档上传队列
# Worker A 和 Worker B 同时取到同一个任务
Worker A: 开始处理 document_123.pdf
Worker B: 开始处理 document_123.pdf  # 重复处理！
```

#### Redis 分布式锁实现

```python
import redis
import uuid
import time

class RedisLock:
    def __init__(self, redis_client, key: str, ttl: int = 60):
        self.redis = redis_client
        self.key = f"lock:{key}"
        self.ttl = ttl
        self.token = str(uuid.uuid4())  # 唯一标识,防止误删别人的锁

    def acquire(self) -> bool:
        """尝试获取锁"""
        return self.redis.set(self.key, self.token, nx=True, ex=self.ttl)

    def release(self):
        """释放锁（Lua 脚本保证原子性）"""
        lua_script = """
        if redis.call("get", KEYS[1]) == ARGV[1] then
            return redis.call("del", KEYS[1])
        else
            return 0
        end
        """
        self.redis.eval(lua_script, 1, self.key, self.token)

# 使用示例
redis_client = redis.Redis(host='localhost', port=6379)

def process_document(doc_id: str):
    lock = RedisLock(redis_client, f"doc:{doc_id}", ttl=300)
    
    if not lock.acquire():
        print(f"文档 {doc_id} 正在被其他 Worker 处理")
        return
    
    try:
        # 处理文档（可能耗时 5 分钟）
        print(f"开始处理 {doc_id}")
        time.sleep(5)
        print(f"处理完成 {doc_id}")
    finally:
        lock.release()
```

#### 分布式锁的坑

**坑 1：锁超时导致重复执行**

```python
# 问题：任务执行时间超过 TTL
lock = RedisLock(redis_client, "task", ttl=10)
lock.acquire()
time.sleep(15)  # 锁已过期,其他进程可能获取到锁
lock.release()  # 可能删除了别人的锁！

# 解决：使用 token 防止误删（上面代码已实现）
```

**坑 2：Redis 主从切换导致锁失效**

```
场景：
1. Client A 在 Master 获取锁
2. Master 宕机,Slave 提升为新 Master（但锁数据未同步）
3. Client B 在新 Master 获取到同一把锁
4. A 和 B 同时持有锁！

解决方案：
- 使用 Redlock 算法（多个 Redis 实例）
- 或接受极低概率的冲突（大多数场景可接受）
```

#### 今日检查点

- [ ] 理解分布式锁的应用场景
- [ ] 能用 Redis 实现基本的分布式锁
- [ ] 理解锁超时和主从切换的问题

---

### Day 109（周四,2h）：Nginx 负载均衡

#### 负载均衡策略

```nginx
# /etc/nginx/conf.d/ai-service.conf

upstream ai_services {
    # 策略 1：轮询（默认）
    # server localhost:8001;
    # server localhost:8002;
    # server localhost:8003;
    
    # 策略 2：最少连接（推荐 AI 服务）
    least_conn;
    server localhost:8001;
    server localhost:8002;
    server localhost:8003;
    
    # 策略 3：IP 哈希（保持会话亲和性）
    # ip_hash;
    # server localhost:8001;
    # server localhost:8002;
}

server {
    listen 80;
    server_name ai.example.com;

    location /api/ {
        proxy_pass http://ai_services;
        
        # 超时设置（AI 响应可能较慢）
        proxy_read_timeout 120s;
        proxy_connect_timeout 10s;
        
        # 传递真实 IP
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        
        # 健康检查（需要 nginx-plus 或第三方模块）
        # health_check interval=10s fails=3 passes=2;
    }
}
```

#### 本地测试负载均衡

```bash
# 启动 3 个实例
uvicorn app.main:app --host 0.0.0.0 --port 8001 &
uvicorn app.main:app --host 0.0.0.0 --port 8002 &
uvicorn app.main:app --host 0.0.0.0 --port 8003 &

# 重载 Nginx 配置
sudo nginx -s reload

# 测试（观察请求分发到不同端口）
for i in {1..10}; do
    curl http://localhost/api/health
done
```

#### Docker Compose 多实例部署

```yaml
# docker-compose.yml
version: "3.8"

services:
  ai-service-1:
    build: .
    environment:
      - INSTANCE_ID=1
    ports:
      - "8001:8000"

  ai-service-2:
    build: .
    environment:
      - INSTANCE_ID=2
    ports:
      - "8002:8000"

  ai-service-3:
    build: .
    environment:
      - INSTANCE_ID=3
    ports:
      - "8003:8000"

  nginx:
    image: nginx:alpine
    ports:
      - "80:80"
    volumes:
      - ./nginx.conf:/etc/nginx/conf.d/default.conf
    depends_on:
      - ai-service-1
      - ai-service-2
      - ai-service-3
```

#### 今日检查点

- [ ] 理解负载均衡的三种策略
- [ ] 能配置 Nginx 反向代理
- [ ] 能用 Docker Compose 启动多实例

---

### Day 110（周五,2h）：后端架构设计题训练

#### 设计题：支持 10 万用户的 RAG 系统

**需求**
- 10 万注册用户,日活 1 万
- 每用户平均 10 次查询/天
- 峰值 QPS：100（假设集中在工作时间）
- 文档总量：100 万篇
- 响应时间：P95 < 3s

**架构设计思路**

```
                    ┌─────────────┐
                    │   用户请求   │
                    └──────┬──────┘
                           │
                    ┌──────▼──────┐
                    │  Nginx LB   │
                    └──────┬──────┘
                           │
        ┌──────────────────┼──────────────────┐
        │                  │                  │
   ┌────▼────┐       ┌────▼────┐       ┌────▼────┐
   │ API 实例1│       │ API 实例2│       │ API 实例3│
   └────┬────┘       └────┬────┘       └────┬────┘
        │                  │                  │
        └──────────────────┼──────────────────┘
                           │
        ┌──────────────────┼──────────────────┐
        │                  │                  │
   ┌────▼────┐       ┌────▼────┐       ┌────▼────┐
   │  Redis  │       │ Vector  │       │  Celery │
   │ (缓存)  │       │   DB    │       │ (异步)  │
   └─────────┘       └─────────┘       └─────────┘
```

**1. 无状态化（可水平扩展）**

```python
# 会话存 Redis
class ChatService:
    def __init__(self, redis_client):
        self.redis = redis_client
    
    async def chat(self, user_id: str, question: str):
        # 读取历史
        history_key = f"chat:{user_id}"
        history = json.loads(await self.redis.get(history_key) or "[]")
        
        # 调用 RAG
        result = await rag_engine.query(question, history)
        
        # 更新历史
        history.append({"q": question, "a": result["answer"]})
        await self.redis.setex(history_key, 3600, json.dumps(history[-10:]))
        
        return result
```

**2. 文档摄入异步化（Celery）**

```python
# tasks.py
from celery import Celery

celery_app = Celery('tasks', broker='redis://localhost:6379/0')

@celery_app.task
def ingest_document(file_path: str, doc_id: str):
    """异步处理文档"""
    loader = DocumentLoader()
    docs = loader.load(file_path)
    vector_store.add_documents(docs, ids=[doc_id])
    return {"status": "completed", "doc_id": doc_id}

# API 路由
@app.post("/documents/upload")
async def upload(file: UploadFile):
    doc_id = str(uuid.uuid4())
    file_path = save_to_storage(file)
    
    # 提交异步任务
    task = ingest_document.delay(file_path, doc_id)
    
    return {"doc_id": doc_id, "task_id": task.id, "status": "processing"}
```

**3. LLM 响应缓存（降低成本）**

```python
import hashlib

async def query_with_cache(question: str):
    # 生成缓存 key
    cache_key = f"llm:{hashlib.md5(question.encode()).hexdigest()}"
    
    # 尝试从缓存读取
    cached = await redis_client.get(cache_key)
    if cached:
        return json.loads(cached)
    
    # 调用 LLM
    result = await rag_engine.query(question)
    
    # 缓存结果（1 小时）
    await redis_client.setex(cache_key, 3600, json.dumps(result))
    
    return result
```

**4. 数据库连接池**

```python
from sqlalchemy import create_engine
from sqlalchemy.pool import QueuePool

engine = create_engine(
    "postgresql://user:pass@localhost/db",
    poolclass=QueuePool,
    pool_size=20,          # 常驻连接数
    max_overflow=10,       # 峰值额外连接数
    pool_timeout=30,       # 获取连接超时
    pool_recycle=3600      # 连接回收时间
)
```

**5. 向量库优化**

```python
# ChromaDB 分片（按用户或文档类型）
def get_collection(user_id: str):
    shard_id = hash(user_id) % 10  # 10 个分片
    return chroma_client.get_or_create_collection(f"docs_shard_{shard_id}")

# 或使用专业向量库（生产环境推荐）
# - Milvus（开源,支持分布式）
# - Pinecone（云服务,按量付费）
# - Weaviate（开源,支持多租户）
```

**容量估算**

| 资源 | 计算 | 结果 |
|:---|:---|:---|
| API 实例 | 100 QPS ÷ 10 QPS/实例 | 10 台（2 核 4G） |
| Redis | 1 万用户 × 10 条历史 × 1KB | 100 MB（单机足够） |
| 向量库 | 100 万文档 × 1024 维 × 4 字节 | 4 GB（需索引优化） |
| 带宽 | 100 QPS × 10 KB/响应 | 1 MB/s（8 Mbps） |

#### 今日检查点

- [ ] 能画出完整的系统架构图
- [ ] 理解各组件的作用和容量估算
- [ ] 能讲述扩展性优化思路

---

### Day 111-112（周末,6h×2）：后端面试题整理 + 架构图与文档

#### Day 111（周六,6h）：后端面试题整理

**缓存相关**

1. Redis 的数据结构有哪些？各自适用场景？
   - String：缓存、计数器、分布式锁
   - Hash：用户信息、配置
   - List：消息队列、时间线
   - Set：标签、去重
   - ZSet：排行榜、延时队列

2. 缓存穿透、击穿、雪崩的区别和解决方案？
   - 穿透：查询不存在的数据 → 布隆过滤器
   - 击穿：热点 key 过期 → 互斥锁或永不过期
   - 雪崩：大量 key 同时过期 → 随机 TTL

3. 如何保证缓存与数据库一致性？
   - 先更新数据库,再删除缓存（推荐）
   - 延时双删
   - 订阅 binlog 异步更新

**队列与异步**

4. Celery 的工作原理？
   - Broker（消息队列）：存储任务
   - Worker（工作进程）：执行任务
   - Backend（结果存储）：保存执行结果

5. 如何保证消息不丢失？
   - 持久化队列和消息
   - 手动 ACK
   - 死信队列处理失败任务

**并发与分布式**

6. Python GIL 是什么？如何绕过？
   - 全局解释器锁,同一时刻只有一个线程执行字节码
   - I/O 密集：asyncio 或 threading
   - CPU 密集：multiprocessing

7. 分布式锁的实现方式？
   - Redis SETNX + 过期时间
   - Redlock 算法（多实例）
   - ZooKeeper（强一致性）

8. CAP 定理在实际项目中如何选择？
   - 金融系统：CP（强一致性）
   - 社交应用：AP（高可用）
   - AI 服务：AP（最终一致性可接受）

**架构设计**

9. 如何设计一个高并发的短链接系统？
   - 号码生成：雪花算法或自增 ID + Base62
   - 缓存：Redis 存热点链接
   - 数据库：分库分表
   - 重定向：302（可统计）vs 301（浏览器缓存）

10. 如何设计一个秒杀系统？
    - 前端：按钮置灰、验证码
    - 后端：Redis 预减库存、消息队列削峰
    - 数据库：乐观锁（version 字段）

#### Day 112（周日,6h）：架构图与文档

**任务清单**

1. 绘制 RAG 系统架构图（使用 draw.io 或 Excalidraw）
   - 用户层
   - 接入层（Nginx）
   - 应用层（API 实例）
   - 数据层（Redis/向量库/对象存储）
   - 异步层（Celery）

2. 在作品集 README 中补充"高并发设计"章节
   ```markdown
   ## 高并发设计

   本项目支持水平扩展,可承载 10 万用户规模：

   - 无状态服务：会话存 Redis,任意实例可处理请求
   - 异步处理：文档摄入通过 Celery 异步执行
   - 缓存优化：LLM 响应缓存,降低 API 成本
   - 负载均衡：Nginx 最少连接策略分发流量
   - 分布式锁：避免重复处理同一文档

   架构图：[查看详细架构](docs/architecture.png)
   ```

3. 整理学习笔记
   - 将 Day 106-112 的代码示例整理到 GitHub
   - 写一篇博客：《从单机到分布式：AI 服务的扩展性改造》

4. 模拟面试练习
   - 找同学或用 ChatGPT 模拟面试官
   - 练习讲述系统设计思路（15 分钟内）
   - 录音并回听,改进表达

---

## Phase 7 总结

完成本阶段后,你将具备：

| 能力 | 水平 |
|:---|:---|
| 分布式理论 | 理解 CAP 定理、一致性模型 |
| 无状态设计 | 能将有状态服务改造为可扩展架构 |
| 分布式锁 | 能用 Redis 实现基本的分布式锁 |
| 负载均衡 | 能配置 Nginx 反向代理和多实例部署 |
| 架构设计 | 能在面试中讲述高并发 AI 服务架构 |
| 容量规划 | 能进行基本的资源估算和性能优化 |

**面试准备检查清单**

- [ ] 能在白板上画出完整的系统架构图
- [ ] 能讲述 CAP 定理并举例说明
- [ ] 能解释缓存穿透/击穿/雪崩的区别
- [ ] 能设计一个支持 10 万用户的 RAG 系统
- [ ] 能回答 Python 并发相关问题（GIL/asyncio）
- [ ] 能解释分布式锁的实现原理和坑

**下一步**：Phase 8 综合项目实战,整合所有技术栈。

---

## 学习资源

**推荐阅读**
- 《数据密集型应用系统设计》（DDIA）— 分布式系统圣经
- 《凤凰架构》— 国内架构师必读
- Redis 官方文档 — 分布式锁章节

**在线课程**
- MIT 6.824：分布式系统（经典课程）
- 极客时间《从 0 开始学架构》

**实战项目**
- 改造 RAG 知识库为分布式架构
- 实现一个简单的分布式任务调度系统
- 用 Docker Compose 部署多实例 + Nginx 负载均衡

---

## Week 16（第 113-119 天）：监控与可观测性

### Day 113（周一，2h）：监控体系概述

**为什么需要监控？**
- 生产环境问题：服务挂了？慢了？错误率高？
- 没有监控 = 盲飞，出问题只能靠用户反馈

**监控三大支柱**：
1. **Metrics（指标）**：CPU、内存、QPS、响应时间
2. **Logs（日志）**：错误日志、访问日志、业务日志
3. **Traces（链路追踪）**：请求在各服务间的调用路径

**今日检查点**：
- [ ] 理解监控的重要性
- [ ] 了解 Metrics/Logs/Traces 的区别

---

### Day 114-115（周二-周三，各 2h）：Prometheus + Grafana

```bash
# docker-compose.yml
version: '3.8'
services:
  prometheus:
    image: prom/prometheus
    ports:
      - "9090:9090"
    volumes:
      - ./prometheus.yml:/etc/prometheus/prometheus.yml
  
  grafana:
    image: grafana/grafana
    ports:
      - "3000:3000"
    environment:
      - GF_SECURITY_ADMIN_PASSWORD=admin
```

```yaml
# prometheus.yml
global:
  scrape_interval: 15s

scrape_configs:
  - job_name: 'fastapi'
    static_configs:
      - targets: ['host.docker.internal:8000']
```

```python
# FastAPI 集成 Prometheus
from prometheus_client import Counter, Histogram, generate_latest
from fastapi import Response

# 定义指标
request_count = Counter('http_requests_total', 'Total HTTP requests', ['method', 'endpoint'])
request_duration = Histogram('http_request_duration_seconds', 'HTTP request duration')

@app.middleware("http")
async def metrics_middleware(request: Request, call_next):
    with request_duration.time():
        response = await call_next(request)
    
    request_count.labels(method=request.method, endpoint=request.url.path).inc()
    return response

@app.get("/metrics")
def metrics():
    return Response(content=generate_latest(), media_type="text/plain")
```

**Grafana 配置**：
1. 访问 http://localhost:3000（admin/admin）
2. 添加 Prometheus 数据源
3. 导入 Dashboard 模板（FastAPI Dashboard）

**今日检查点**：
- [ ] Prometheus 能抓取 FastAPI 指标
- [ ] Grafana 能展示 QPS、响应时间、错误率

---

### Day 116（周四，2h）：日志聚合

```python
# 结构化日志
import logging
import json

class JSONFormatter(logging.Formatter):
    def format(self, record):
        log_data = {
            "timestamp": self.formatTime(record),
            "level": record.levelname,
            "message": record.getMessage(),
            "module": record.module,
        }
        if record.exc_info:
            log_data["exception"] = self.formatException(record.exc_info)
        return json.dumps(log_data)

handler = logging.StreamHandler()
handler.setFormatter(JSONFormatter())
logger = logging.getLogger()
logger.addHandler(handler)
logger.setLevel(logging.INFO)

# 使用
logger.info("User login", extra={"user_id": 123, "ip": "1.2.3.4"})
```

**日志聚合方案**（了解即可）：
- ELK Stack（Elasticsearch + Logstash + Kibana）
- Loki + Grafana（轻量级）

**今日检查点**：
- [ ] 能输出结构化 JSON 日志
- [ ] 理解日志聚合的作用

---

### Day 117（周五，2h）：链路追踪基础

```bash
pip install opentelemetry-api opentelemetry-sdk opentelemetry-instrumentation-fastapi
```

```python
from opentelemetry import trace
from opentelemetry.sdk.trace import TracerProvider
from opentelemetry.sdk.trace.export import ConsoleSpanExporter, SimpleSpanProcessor

# 初始化
trace.set_tracer_provider(TracerProvider())
tracer = trace.get_tracer(__name__)
trace.get_tracer_provider().add_span_processor(
    SimpleSpanProcessor(ConsoleSpanExporter())
)

# 自动追踪 FastAPI
from opentelemetry.instrumentation.fastapi import FastAPIInstrumentor
FastAPIInstrumentor.instrument_app(app)

# 手动追踪
@app.post("/chat")
async def chat(request: ChatRequest):
    with tracer.start_as_current_span("rag_query"):
        with tracer.start_as_current_span("retrieve"):
            docs = vectordb.search(request.question)
        
        with tracer.start_as_current_span("llm_generate"):
            answer = llm.generate(docs, request.question)
    
    return {"answer": answer}
```

**今日检查点**：
- [ ] 理解链路追踪的作用
- [ ] 能看到请求的调用链路

---

### Day 118-119（周末，6h×2）：监控实战

**Day 118（6h）**：
- 为 RAG API 添加完整监控
- 配置告警规则（响应时间 > 5s、错误率 > 1%）
- 压测并观察监控面板

**Day 119（6h）**：
- 模拟故障场景（数据库连接失败、LLM 超时）
- 通过监控定位问题
- 优化慢查询

**Week 16 总结检查点**：
- [ ] Prometheus + Grafana 监控就绪
- [ ] 能通过监控发现性能问题
- [ ] 理解 Metrics/Logs/Traces 的作用

---
