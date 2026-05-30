# Phase 3：RAG 深度 + 后端服务化

> **时间**：Week 5-9（D29-D63，130 小时）  
> **前提**：Phase 2 LLM API 完成  
> **目标**：从裸写到框架掌握 RAG 全链路，并用 FastAPI + Redis 实现服务化  
>  
> **融合设计**：学完 RAG 检索后立即服务化（FastAPI）+ 缓存（Redis），体会后端组件的即时价值

---

## Week 5 (D29-D35): 裸写 RAG — Embedding + 向量存储

### D29: Embedding 原理

**学习内容**

- 向量空间模型：文本如何映射到高维空间（768/1024/1536 维）
- 余弦相似度计算原理：为何适合语义相似度度量
- 维度的意义：更高维度 vs 计算成本权衡
- Embedding 为何有效：语义信息的几何表示

**检查点**

- [ ] 理解向量空间模型的几何意义
- [ ] 能手算 2 个向量的余弦相似度
- [ ] 解释为何余弦相似度适合语义度量
- [ ] 对比不同维度模型的性能与成本

---

### D30: sentence-transformers

**学习内容**

- sentence-transformers 库架构：模型加载、编码、批处理
- 模型选择策略：bge-m3（多语言）、all-MiniLM（英文）、bge-large（高精度）
- 模型大小权衡：参数量 vs 推理速度 vs 精度
- 本地部署 vs API 调用：成本与延迟对比

**检查点**

- [ ] 安装 sentence-transformers 并加载模型
- [ ] 对比 3 种模型的编码速度和向量维度
- [ ] 理解模型选择的业务场景差异
- [ ] 测试批量编码的性能优化

---

### D31: 裸写向量搜索

**学习内容**

- NumPy 实现余弦相似度矩阵计算
- 暴力搜索（Brute-Force）：O(n) 复杂度分析
- Top-K 检索：堆排序 vs 全排序
- 为何需要向量数据库：百万级数据的性能瓶颈

**检查点**

- [ ] 用 NumPy 实现余弦相似度搜索函数
- [ ] 测试 1000/10000/100000 条数据的检索耗时
- [ ] 理解暴力搜索的性能极限
- [ ] 总结向量数据库的必要性

---

### D32: ChromaDB

**学习内容**

- ChromaDB 核心概念：Collection、Document、Metadata、Embedding
- 持久化存储：内存模式 vs 磁盘持久化
- 距离度量：cosine、l2、ip（内积）的适用场景
- HNSW 索引原理：分层图结构加速检索

**检查点**

- [ ] 创建 ChromaDB Collection 并插入文档
- [ ] 测试 Metadata 过滤查询
- [ ] 对比 cosine/l2/ip 三种距离度量的结果差异
- [ ] 理解 HNSW 索引的性能优势

---

### D33: 向量库对比

**学习内容**

- ChromaDB：轻量级、嵌入式、适合原型和中小规模
- FAISS：Meta 开源、高性能、适合离线批量检索
- Pinecone：托管服务、自动扩展、适合生产环境
- Milvus：分布式、支持 GPU、适合大规模部署
- pgvector：PostgreSQL 插件、适合已有 PG 技术栈
- 选择标准：数据规模、延迟要求、运维成本、生态集成

**检查点**

- [ ] 对比 5 种向量库的核心特性
- [ ] 绘制选择决策树（数据量 -> 延迟 -> 成本）
- [ ] 理解嵌入式 vs 托管 vs 自建的权衡
- [ ] 确定当前项目的向量库选型

---

### D34 Sat 8h: 实战 — 裸写完整 RAG Pipeline

**实战目标**

从零实现完整 RAG 流程，不使用任何框架（LangChain/LlamaIndex）：

1. 文档加载：读取 TXT/MD 文件
2. 文本分块：固定长度分块（chunk_size=500, overlap=50）
3. 向量化：sentence-transformers 编码
4. 存储：ChromaDB 持久化
5. 检索：用户查询 -> Top-K 相似文档
6. 生成：拼接 Prompt -> 调用 LLM API -> 返回答案

**检查点**

- [ ] 实现 5 个独立函数：load/chunk/embed/store/retrieve
- [ ] 端到端测试：上传文档 -> 提问 -> 获得答案
- [ ] 测量各环节耗时（加载/分块/嵌入/检索/生成）
- [ ] 对比有无 RAG 的答案质量差异

---

### D35 Sun 8h: 实战 — 多格式文档解析

**实战目标**

扩展文档加载器，支持多种格式：

- PDF：PyPDF2 或 pdfplumber
- Word：python-docx
- Markdown：保留结构（标题层级）
- Excel/CSV：表格数据转文本
- 统一接口：所有格式返回 List[Document]

**检查点**

- [ ] 实现 5 种格式的解析器
- [ ] 设计统一的 Document 数据结构
- [ ] 处理解析异常（损坏文件、编码问题）
- [ ] 测试混合格式文档目录的批量导入

---

## Week 6 (D36-D42): 裸写 RAG — 检索增强

### D36: 分块策略

**学习内容**

- 固定长度分块：简单但可能割裂语义
- 递归分块：按段落/句子递归切分，保留结构
- 语义分块：基于 Embedding 相似度动态切分
- 结构化分块：保留 Markdown 标题、代码块结构
- 中英文分隔符差异：中文句号、英文换行符

**检查点**

- [ ] 实现 4 种分块策略的函数
- [ ] 对比同一文档的不同分块结果
- [ ] 测试中英文混合文档的分块效果
- [ ] 分析分块策略对检索质量的影响

---

### D37: 分块优化

**学习内容**

- Overlap 调优：重叠区域如何影响上下文连贯性
- Metadata 富化：为每个 Chunk 添加来源、标题、时间戳
- Parent-Child Document：小块检索 + 大块返回
- 分块边界处理：避免在句子中间切分

**检查点**

- [ ] 测试不同 overlap 值（0/50/100/200）的检索效果
- [ ] 实现 Metadata 自动提取（文件名、章节、页码）
- [ ] 实现 Parent-Child 分块策略
- [ ] 对比优化前后的检索准确率

---

### D38: BM25 + 混合检索

**学习内容**

- BM25 原理：基于词频的稀疏检索算法
- 稀疏检索 vs 密集检索：互补性分析
- EnsembleRetriever 概念：加权融合多路检索结果
- Alpha 权重调优：BM25 vs Dense 的比例平衡

**检查点**

- [ ] 用 rank-bm25 库实现 BM25 检索
- [ ] 对比 BM25 和 Dense 检索的召回差异
- [ ] 实现加权融合算法（alpha=0.5）
- [ ] 测试混合检索的准确率提升

---

### D39: Rerank 重排序

**学习内容**

- CrossEncoder 原理：双塔模型 vs 交叉编码器
- bge-reranker 模型：中英文重排序
- LLM-based Reranking：用 LLM 判断相关性
- 何时使用 Rerank：Top-K 较大时的精排需求

**检查点**

- [ ] 用 CrossEncoder 实现重排序
- [ ] 对比重排序前后的 Top-5 结果
- [ ] 测试 LLM Rerank 的效果和成本
- [ ] 分析 Rerank 的性能开销

---

### D40: 查询增强 HyDE

**学习内容**

- HyDE 原理：假设性文档嵌入（Hypothetical Document Embedding）
- Multi-Query：生成多个改写查询扩大召回
- Query Expansion：同义词扩展、上下位词
- 何时使用查询增强：短查询、歧义查询

**检查点**

- [ ] 实现 HyDE：用 LLM 生成假设答案 -> 嵌入检索
- [ ] 实现 Multi-Query：生成 3 个改写查询
- [ ] 对比查询增强前后的召回率
- [ ] 分析查询增强的适用场景

---

### D41 Sat 8h: 实战 — 混合检索 + Rerank

**实战目标**

集成混合检索与重排序：

1. BM25 检索 Top-20
2. Dense 检索 Top-20
3. 加权融合 -> Top-10
4. CrossEncoder 重排序 -> Top-5
5. 返回最终结果

**检查点**

- [ ] 实现完整混合检索 + Rerank 管道
- [ ] 对比单路检索 vs 混合检索的准确率
- [ ] 测量各环节耗时（BM25/Dense/Rerank）
- [ ] 调优 alpha 权重和 Rerank 阈值

---

### D42 Sun 8h: 实战 — HyDE + 检索质量评测

**实战目标**

实现 HyDE 并建立评测体系：

1. 构建测试集：10 个问题 + 标准答案
2. 实现 HyDE 检索
3. 计算 Precision@K 和 Recall@K
4. 对比不同检索策略的评测结果

**检查点**

- [ ] 实现 HyDE 检索管道
- [ ] 构建标注测试集（问题-文档对）
- [ ] 实现 Precision/Recall 计算函数
- [ ] 生成检索质量对比报告

---

## Week 7 (D43-D49): LangChain RAG 框架

### D43: LangChain 核心

**学习内容**

- Chain 概念：输入 -> 处理 -> 输出的链式结构
- Prompt 模板：变量替换、Few-Shot、Chat Prompt
- OutputParser：结构化输出解析（JSON/List/Pydantic）
- Memory：对话历史管理（Buffer/Summary/Window）

**检查点**

- [ ] 创建简单 Chain：Prompt -> LLM -> OutputParser
- [ ] 实现 Few-Shot Prompt 模板
- [ ] 测试 3 种 Memory 类型的差异
- [ ] 理解 Chain 的组合与嵌套

---

### D44: LangChain 文档处理

**学习内容**

- Loader：UnstructuredFileLoader、DirectoryLoader、PyPDFLoader
- Splitter：CharacterTextSplitter、RecursiveCharacterTextSplitter
- Embeddings：HuggingFaceEmbeddings、OpenAIEmbeddings
- 对比裸写实现：代码量、灵活性、性能

**检查点**

- [ ] 用 LangChain Loader 加载多格式文档
- [ ] 用 RecursiveCharacterTextSplitter 分块
- [ ] 对比 LangChain 与裸写的分块结果
- [ ] 分析 LangChain 的抽象层优劣

---

### D45: LangChain 向量库 + 检索器

**学习内容**

- VectorStore 抽象：Chroma、FAISS、Pinecone 统一接口
- VectorStoreRetriever：from_documents、similarity_search
- EnsembleRetriever：BM25Retriever + VectorStoreRetriever
- MultiQueryRetriever：自动生成多查询

**检查点**

- [ ] 用 LangChain 创建 ChromaDB VectorStore
- [ ] 实现 EnsembleRetriever 混合检索
- [ ] 测试 MultiQueryRetriever 效果
- [ ] 对比 LangChain 与裸写的检索性能

---

### D46: LCEL 管道语法

**学习内容**

- Pipe 操作符（|）：链式组合 Runnable
- Stream：流式输出 LLM 响应
- Batch：批量处理多个输入
- Runnable 接口：invoke、stream、batch 统一抽象

**检查点**

- [ ] 用 LCEL 重写 RAG 管道（Retriever | Prompt | LLM）
- [ ] 实现流式 RAG 响应
- [ ] 测试批量问答（10 个问题并行）
- [ ] 理解 LCEL 的声明式编程范式

---

### D47: LlamaIndex 概览

**学习内容**

- LlamaIndex vs LangChain：节点式 vs 链式架构
- Node 概念：文档的结构化表示
- Index 类型：VectorStoreIndex、ListIndex、TreeIndex
- 何时选择 LlamaIndex：复杂文档结构、多跳推理

**检查点**

- [ ] 用 LlamaIndex 构建简单 RAG
- [ ] 对比 LlamaIndex 与 LangChain 的代码风格
- [ ] 理解 Node 的元数据管理
- [ ] 总结两个框架的选择标准

---

### D48 Sat 8h: 实战 — LangChain 重写 RAG

**实战目标**

用 LangChain 重写 Week 5-6 的裸写 RAG：

1. DirectoryLoader 加载文档
2. RecursiveCharacterTextSplitter 分块
3. HuggingFaceEmbeddings 嵌入
4. Chroma VectorStore 存储
5. EnsembleRetriever 检索
6. LCEL 管道生成答案

**检查点**

- [ ] 完整 LangChain RAG 实现
- [ ] 对比裸写与 LangChain 的代码量（行数）
- [ ] 分析 LangChain 的灵活性损失
- [ ] 总结框架的适用场景

---

### D49 Sun 8h: 实战 — 对话式 RAG

**实战目标**

实现带记忆的多轮对话 RAG：

1. ConversationBufferMemory 管理历史
2. 历史压缩：超过 N 轮后自动总结
3. 上下文引用：回答时引用历史问题
4. 会话持久化：保存/加载对话历史

**检查点**

- [ ] 实现多轮对话 RAG（至少 5 轮）
- [ ] 测试历史压缩功能
- [ ] 实现会话保存/恢复
- [ ] 对比有无记忆的对话连贯性

---

## Week 8 (D50-D56): FastAPI 服务化 + Redis 缓存

### D50: FastAPI 基础

**学习内容**

- 路由定义：@app.get/post/put/delete
- Pydantic 模型：请求体验证、响应序列化
- 依赖注入：Depends() 管理共享资源
- Swagger 自动文档：/docs 和 /redoc

**检查点**

- [ ] 创建 FastAPI 应用并定义 4 个路由
- [ ] 用 Pydantic 定义请求/响应模型
- [ ] 实现依赖注入（数据库连接）
- [ ] 访问 Swagger 文档并测试 API

---

### D51: FastAPI 异步 + SSE 流式

**学习内容**

- async/await：异步路由与异步依赖
- StreamingResponse：流式返回大文件或 LLM 输出
- Server-Sent Events (SSE)：实时推送 LLM 生成过程
- async generator：yield 逐块返回数据

**检查点**

- [ ] 实现异步路由（async def）
- [ ] 用 StreamingResponse 返回 LLM 流式输出
- [ ] 实现 SSE 端点（/chat/stream）
- [ ] 前端测试 EventSource 接收流式响应

---

### D52: Redis 基础

**学习内容**

- 5 种数据结构：String、Hash、List、Set、Sorted Set
- Docker 安装 Redis：docker run -p 6379:6379 redis
- redis-cli 操作：SET/GET/EXPIRE/TTL
- Python 客户端：redis-py 的同步与异步接口

**检查点**

- [ ] Docker 启动 Redis 并连接
- [ ] 用 redis-cli 测试 5 种数据结构
- [ ] 用 redis-py 实现 Python 客户端
- [ ] 测试 TTL 过期机制

---

### D53: Redis 缓存实践

**学习内容**

- LLM 响应缓存：SHA256(prompt) 作为 key
- Embedding 缓存：避免重复编码相同文本
- 语义缓存：基于 Embedding 相似度的缓存命中
- 缓存失效策略：TTL、LRU、手动清除

**检查点**

- [ ] 实现 LLM 响应缓存（SHA256 key）
- [ ] 实现 Embedding 缓存
- [ ] 实现语义缓存（相似度阈值 0.95）
- [ ] 测试缓存命中率和性能提升

---

### D54: Redis 限流 + 缓存三大问题

**学习内容**

- 滑动窗口限流：Sorted Set 实现
- 缓存穿透：查询不存在的数据 -> 布隆过滤器
- 缓存击穿：热点数据过期 -> 互斥锁
- 缓存雪崩：大量数据同时过期 -> 随机 TTL
- 限流算法对比：固定窗口 vs 滑动窗口 vs 令牌桶

**检查点**

- [ ] 实现滑动窗口限流（100 req/min）
- [ ] 实现布隆过滤器防穿透
- [ ] 实现互斥锁防击穿
- [ ] 测试随机 TTL 防雪崩

---

### D55 Sat 8h: 实战 — RAG API 服务化

**实战目标**

将 RAG 封装为 FastAPI 服务：

1. POST /documents/upload：上传文档并入库
2. POST /chat：问答接口（同步）
3. POST /chat/stream：流式问答（SSE）
4. Redis 多层缓存：Embedding 缓存 + LLM 响应缓存 + 语义缓存

**检查点**

- [ ] 实现 3 个 API 端点
- [ ] 集成 Redis 三层缓存
- [ ] 测试流式响应的实时性
- [ ] 测量缓存命中率和延迟降低

---

### D56 Sun 8h: 实战 — 完整 RAG API

**实战目标**

完善 RAG API 服务：

1. GET /documents：列出所有文档
2. DELETE /documents/{id}：删除文档
3. GET /health：健康检查
4. Swagger 文档完善
5. Postman 测试集

**检查点**

- [ ] 实现 5 个完整端点
- [ ] 完善 Swagger 文档（描述、示例）
- [ ] 创建 Postman Collection 并测试
- [ ] 部署到本地并验证端到端流程

---

## Week 9 (D57-D63): 进阶 RAG + Buffer 2

### D57: 进阶 RAG 模式

**学习内容**

- CRAG (Corrective RAG)：检索后用 LLM 判断相关性，不相关则重新检索
- Self-RAG：LLM 自我反思检索质量并决定是否需要更多上下文
- Adaptive RAG：根据查询复杂度动态选择检索策略
- 何时使用进阶模式：高精度要求、复杂推理任务

**检查点**

- [ ] 理解 CRAG/Self-RAG/Adaptive RAG 的原理
- [ ] 对比三种模式的适用场景
- [ ] 分析进阶模式的成本与收益
- [ ] 设计简单的 CRAG 流程图

---

### D58: 多模态 RAG

**学习内容**

- 图片处理：OCR 提取文字、CLIP 嵌入图片
- 表格处理：保留结构、转 Markdown/HTML
- 代码处理：保留语法高亮、函数签名提取
- 多模态检索：文本 + 图片 + 表格的统一检索

**检查点**

- [ ] 用 OCR 提取 PDF 图片中的文字
- [ ] 实现表格转 Markdown 的解析器
- [ ] 测试代码文档的检索效果
- [ ] 设计多模态文档的统一表示

---

### D59: RAGAs 评估

**学习内容**

- Faithfulness：答案是否忠实于检索内容
- Answer Relevancy：答案是否回答了问题
- Context Precision：检索内容的精确度
- Context Recall：检索内容的召回率
- RAGAs 库：自动化评估流程

**检查点**

- [ ] 安装 RAGAs 并运行示例
- [ ] 对 10 个问答对进行 4 项指标评估
- [ ] 分析评估结果并定位问题
- [ ] 设计改进方案（分块/检索/生成）

---

### D60: 生产 RAG

**学习内容**

- 增量索引：新文档增量入库，避免全量重建
- 文档版本管理：更新文档时保留历史版本
- 扩展性考虑：分布式向量库、异步任务队列
- 监控与日志：检索耗时、缓存命中率、错误率

**检查点**

- [ ] 实现增量索引（仅处理新增/修改文档）
- [ ] 设计文档版本管理方案
- [ ] 分析扩展性瓶颈（嵌入/检索/生成）
- [ ] 添加监控指标（Prometheus/Grafana）

---

### D61: RAG 质量调优

**学习内容**

- 诊断流程：定位问题环节（分块/检索/生成）
- 优化策略：调整分块大小、Top-K、Prompt
- 重新评估：RAGAs 验证改进效果
- 迭代循环：诊断 -> 优化 -> 评估 -> 再诊断

**检查点**

- [ ] 对现有 RAG 系统进行全面诊断
- [ ] 实施 3 项优化措施
- [ ] 用 RAGAs 对比优化前后的指标
- [ ] 总结调优经验和最佳实践

---

### D62 Sat 8h: Buffer 2 — Phase 3 复盘

**复盘目标**

1. 回顾 Week 5-9 的学习内容
2. 整理裸写 RAG vs LangChain 的对比笔记
3. 完善 RAG 项目文档
4. 修复遗留 Bug 和技术债

**检查点**

- [ ] 完成 Phase 3 学习笔记整理
- [ ] 对比裸写与框架的优劣总结
- [ ] 完善项目 README 和 API 文档
- [ ] 修复所有已知 Bug

---

### D63 Sun 8h: Buffer 2 — 全链路验收

**验收目标**

端到端测试完整 RAG API 系统：

1. 上传多格式文档（PDF/Word/MD/TXT）
2. 混合检索 + Rerank + HyDE
3. 流式问答（SSE）
4. Redis 三层缓存验证
5. RAGAs 评估报告

**检查点**

- [ ] 端到端测试通过（上传 -> 检索 -> 问答）
- [ ] 缓存命中率 > 50%
- [ ] RAGAs 4 项指标均 > 0.7
- [ ] 生成完整验收报告

---

## 里程碑 3：RAG API 服务

**交付物**

1. 裸写 RAG 实现（Week 5-6）
2. LangChain RAG 实现（Week 7）
3. FastAPI + Redis 服务化（Week 8）
4. RAGAs 评估流水线（Week 9）
5. 混合检索 + Rerank + HyDE 全部可用

**技术栈**

- 向量库：ChromaDB
- 嵌入模型：sentence-transformers (bge-m3)
- 检索：BM25 + Dense + Rerank
- 框架：LangChain + FastAPI
- 缓存：Redis（三层缓存）
- 评估：RAGAs

---

## 下阶段预告：Phase 4 — Agent 架构 + 工具调用 (Week 10-14)

Phase 4 将进入 Agent 领域，学习：

- ReAct 推理框架：Thought -> Action -> Observation 循环
- 工具调用：Function Calling、Tool Use API
- LangGraph：状态机编排多步 Agent
- 多 Agent 协作：AutoGen、CrewAI
- Agent 评估：任务成功率、工具调用准确率

**融合设计**：Agent 学习与实际工具集成（搜索/计算器/数据库）同步进行，体会 Agent 的实用价值。
