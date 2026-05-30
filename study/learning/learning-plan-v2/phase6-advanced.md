# Phase 6：进阶调优 + 全栈监控

> **时间**：Week 18-20（D120-D140，78 小时）  
> **前提**：Phase 5 Agent + Celery + Nginx 完成  
> **目标**：并发性能优化、PostgreSQL 高级特性、Prometheus/Grafana 全栈监控、进阶 Agent 模式  
> **融合设计**：AI 系统跑慢了→学并发优化；需要可观测性→学 Prometheus/Grafana；需要更好的存储→学 pgvector

---

## Week 18 (D120-126)：并发优化

### D120：asyncio 深入

**学习内容**

- `asyncio.gather()` vs `asyncio.wait()` 使用场景与异常处理策略
- `asyncio.Semaphore` 并发限制（控制同时运行的协程数量，防止资源耗尽）
- `asyncio.Task` 生命周期管理（create_task、cancel、timeout、done callback）
- 并发限制模式：令牌桶、滑动窗口在 asyncio 中的应用
- 与 Node.js event loop 对比（单线程事件循环、回调地狱 vs async/await、libuv vs selector）
- 常见陷阱：阻塞调用导致事件循环卡死、未 await 的协程泄漏、协程取消时的资源清理

**检查点**

- [ ] 理解 gather 的 return_exceptions 参数作用与异常传播机制
- [ ] 掌握 Semaphore 限制并发数（如同时最多 10 个 HTTP 请求）
- [ ] 能解释 create_task vs await 的区别与调度时机

---

### D121：GIL + threading + multiprocessing

**学习内容**

- GIL（Global Interpreter Lock）本质：CPython 实现细节，保护引用计数的互斥锁
- threading 适用场景：I/O 密集型任务（网络请求、文件读写、数据库查询）
- multiprocessing 适用场景：CPU 密集型任务（数据处理、图像计算、模型推理）
- 判断标准：CPU bound vs I/O bound 的识别方法与性能分析
- `concurrent.futures`：ThreadPoolExecutor 与 ProcessPoolExecutor 统一接口
- asyncio 与线程/进程的混合使用：`loop.run_in_executor()` 将阻塞调用卸载到线程池

**检查点**

- [ ] 能判断给定任务应该用 threading、multiprocessing 还是 asyncio
- [ ] 理解 GIL 为什么不影响 I/O 密集型任务的并行效率
- [ ] 掌握 run_in_executor 在异步环境中调用同步阻塞函数的方法

---

### D122：连接池

**学习内容**

- 连接池核心原理：预建连接复用、避免频繁创建/销毁的开销
- httpx 连接池：`limits` 参数（max_connections、max_keepalive_connections）、连接超时配置
- SQLAlchemy 连接池：`pool_size`、`max_overflow`、`pool_timeout`、`pool_recycle` 参数含义
- Redis 连接池：`ConnectionPool`、`BlockingConnectionPool`、最大连接数配置
- 连接池监控指标：活跃连接数、等待队列长度、连接复用率
- 连接泄漏排查：未归还连接的检测与预防（上下文管理器模式）

**检查点**

- [ ] 理解 pool_size 与 max_overflow 的协作关系
- [ ] 掌握 httpx.AsyncClient 作为连接池持有者的生命周期管理
- [ ] 能根据 QPS 估算合理的连接池大小

---

### D123：并发问题

**学习内容**

- 竞态条件（Race Condition）：多协程/线程同时读写共享状态导致的数据不一致
- 死锁（Deadlock）：循环等待的形成条件与预防策略（锁排序、超时机制）
- 资源泄漏（Resource Leak）：未正确关闭的连接、文件句柄、临时文件
- `asyncio.Lock`、`asyncio.Event`、`asyncio.Queue` 同步原语
- 幂等性设计：在并发重试场景下保证操作结果一致
- 分布式锁基础：Redis SETNX 实现分布式互斥

**检查点**

- [ ] 能识别典型竞态条件场景（如计数器并发自增）
- [ ] 理解 asyncio.Lock 与 threading.Lock 的区别（协程锁 vs 线程锁）
- [ ] 掌握资源清理的最佳实践（async with、try/finally）

---

### D124：批量处理加速

**学习内容**

- 并发文档解析：多文件同时解析（Semaphore 控制并发度，避免内存暴涨）
- 批量 Embedding：将多段文本打包为一个 batch 发送给嵌入模型（减少 API 调用次数）
- 批量向量写入：ChromaDB/pgvector 的 batch insert 策略（批次大小与内存的权衡）
- Pipeline 模式：解析→分块→嵌入→存储各阶段流水线并行（生产者-消费者模型）
- 背压（Backpressure）控制：当下游处理慢于上游生产时的缓冲与限流策略
- 性能瓶颈定位：`time.perf_counter`、`cProfile`、`asyncio` debug 模式

**检查点**

- [ ] 理解 batch embedding 相比逐条 embedding 的性能优势
- [ ] 掌握 asyncio.Queue 实现生产者-消费者 pipeline 的方法
- [ ] 能分析文档摄入流程中各阶段的瓶颈所在

---

### D125 Sat (8h)：实战 — RAG 文档摄入并发优化

**学习内容**

- 对现有 RAG 文档摄入管道进行性能基准测试（记录当前耗时）
- 识别瓶颈阶段：文件解析、文本分块、嵌入计算、向量写入各阶段耗时占比
- 应用并发优化策略：多文件并发解析、batch embedding、batch vector write
- Pipeline 重构：将串行流程改为多阶段并行流水线
- 优化前后性能对比：目标实现 3x 加速
- 稳定性验证：大批量文档（100+ 文件）摄入的错误处理与重试机制

**检查点**

- [ ] 完成优化前的性能基准数据记录
- [ ] 实现文档摄入并发优化，达成 3x 加速目标
- [ ] 大批量文档摄入无报错，失败文件有重试或跳过机制

---

### D126 Sun (8h)：实战 — 压力测试 + 性能基准报告

**学习内容**

- 压力测试工具选型：Locust（Python 原生、可编程场景）vs k6（Go 引擎、高并发）
- 测试场景设计：文档摄入并发、问答 API 并发、混合读写负载
- 关键指标采集：RPS、P50/P95/P99 延迟、错误率、资源利用率（CPU/内存/网络）
- 性能瓶颈分析：识别系统在不同并发级别下的表现拐点
- 性能基准报告撰写：包含测试环境、场景、数据、结论与优化建议
- 容量规划基础：根据压测数据推算系统最大承载能力

**检查点**

- [ ] 使用 Locust 或 k6 完成至少 3 个场景的压力测试
- [ ] 产出性能基准报告（含图表、P95 延迟、最大 RPS）
- [ ] 识别出当前系统的性能瓶颈与优化方向

---

## Week 19 (D127-133)：PostgreSQL 高级 + 监控

### D127：PostgreSQL 高级 SQL

**学习内容**

- 窗口函数（Window Functions）：ROW_NUMBER、RANK、DENSE_RANK、LAG、LEAD、NTILE
- 窗口帧定义：PARTITION BY + ORDER BY + ROWS/RANGE BETWEEN
- CTE（Common Table Expressions）：WITH 语句、递归 CTE（树形结构查询）
- JSONB 操作：`->`、`->>`、`@>`、`?`、`jsonb_path_query`，JSONB 索引（GIN）
- 全文搜索：`tsvector`、`tsquery`、`to_tsvector()`、`plainto_tsquery()`、GIN 索引加速
- 中文全文搜索方案：pg_jieba / zhparser 分词插件

**检查点**

- [ ] 能用窗口函数实现排名、同比环比计算
- [ ] 理解 CTE 与子查询的区别（可读性、物化策略）
- [ ] 掌握 JSONB 的查询语法与 GIN 索引创建

---

### D128：PostgreSQL 性能优化

**学习内容**

- `EXPLAIN ANALYZE` 解读：Seq Scan vs Index Scan vs Bitmap Scan、实际行数 vs 估算行数
- 索引策略：B-tree（等值/范围）、Hash（等值）、GiST（空间/全文）、GIN（数组/JSONB/全文）
- 覆盖索引（Covering Index）：`INCLUDE` 子句避免回表查询
- 部分索引（Partial Index）：`WHERE` 条件过滤，减小索引体积
- 统计信息与查询计划：`pg_stats`、`pg_stat_statements`、自动 vacuum 与 analyze
- 慢查询排查流程：定位→EXPLAIN→索引优化→验证

**检查点**

- [ ] 能解读 EXPLAIN ANALYZE 输出，识别全表扫描与低效 join
- [ ] 理解覆盖索引和部分索引的适用场景
- [ ] 掌握 pg_stat_statements 找出 Top N 慢查询的方法

---

### D129：pgvector

**学习内容**

- pgvector 扩展：PostgreSQL 原生向量存储与检索能力
- 向量数据类型：`vector(dim)` 列定义、embedding 存储
- 距离函数：L2 距离（`<->`）、余弦距离（`<=>`）、内积（`<#>`）
- 索引算法对比：IVFFlat（倒排索引，构建快、精度稍低）vs HNSW（图算法，精度高、内存大）
- 混合查询：SQL 条件过滤 + 向量相似度搜索（metadata 过滤 + top-k 检索）
- 与专用向量库对比：pgvector vs ChromaDB vs Milvus（功能、性能、运维复杂度）

**检查点**

- [ ] 理解 IVFFlat 与 HNSW 索引的构建参数与适用场景
- [ ] 掌握混合查询（WHERE 条件 + ORDER BY 向量距离 LIMIT k）
- [ ] 能分析 pgvector 替代 ChromaDB 的利弊

---

### D130：PostgreSQL 复制

**学习内容**

- 流式复制（Streaming Replication）：WAL 日志传输、同步/异步复制模式
- 逻辑复制（Logical Replication）：发布/订阅模型、选择性表复制
- 只读副本（Read Replicas）：读写分离架构、查询路由策略
- PgBouncer 连接池代理：session/transaction/statement 三种池模式
- 高可用方案概览：Patroni + etcd 自动故障切换
- 备份策略：pg_dump 逻辑备份、pg_basebackup 物理备份、PITR 时间点恢复

**检查点**

- [ ] 理解流式复制与逻辑复制的区别与适用场景
- [ ] 掌握 PgBouncer transaction 模式的配置与优势
- [ ] 能设计一个读写分离的数据库架构方案

---

### D131：Prometheus 基础

**学习内容**

- Prometheus 架构：Pull 模式采集、时序数据库、服务发现
- 指标类型：Counter（只增计数器）、Gauge（可增减仪表）、Histogram（分布直方图）、Summary
- PromQL 基础：instant vector、range vector、聚合操作（sum、avg、rate、increase）
- Scrape 配置：`prometheus.yml` 的 job 定义、scrape_interval、targets
- Python 客户端：`prometheus_client` 库，自定义指标暴露（/metrics 端点）
- 常见 PromQL 模式：QPS 计算（`rate(counter[5m])`）、延迟分位数（`histogram_quantile`）

**检查点**

- [ ] 理解 Counter vs Gauge 的使用场景（请求数 vs 当前连接数）
- [ ] 掌握 rate() 函数计算 QPS 的原理
- [ ] 能编写 PromQL 查询 P95 延迟

---

### D132 Sat (8h)：实战 — Prometheus + Grafana 部署 + AI 专属仪表盘

**学习内容**

- Docker Compose 部署 Prometheus + Grafana 全套监控栈
- FastAPI 应用集成 prometheus_client，暴露自定义指标
- AI 系统专属指标设计：
  - Token 消耗量与成本（按模型、按接口统计）
  - LLM 调用延迟 P50/P95/P99
  - 缓存命中率（向量检索缓存、LLM 响应缓存）
  - Embedding 批处理吞吐量
- Grafana Dashboard 构建：变量、面板、告警阈值
- Dashboard as Code：JSON 模板导出与版本化管理

**检查点**

- [ ] Prometheus 成功采集应用指标
- [ ] Grafana 仪表盘展示 Token 成本、延迟 P95、缓存命中率
- [ ] Dashboard JSON 模板纳入版本控制

---

### D133 Sun (8h)：实战 — pgvector 迁移

**学习内容**

- 迁移规划：ChromaDB → pgvector 的数据迁移方案设计
- Schema 设计：向量表结构（id、content、metadata JSONB、embedding vector(dim)）
- 数据迁移执行：从 ChromaDB 导出 → 转换格式 → 批量写入 pgvector
- HNSW 索引构建与参数调优（m、ef_construction）
- 性能对比测试：相同查询集在 ChromaDB 与 pgvector 上的延迟与召回率
- 混合查询验证：SQL 条件过滤 + 向量检索的端到端测试

**检查点**

- [ ] 完成 ChromaDB → pgvector 数据迁移
- [ ] 性能对比报告（延迟、召回率、资源占用）
- [ ] 混合查询（metadata 过滤 + 向量检索）功能验证通过

---

## Week 20 (D134-140)：进阶 Agent + 链路追踪 + Buffer 5

### D134：进阶 Agent 模式

**学习内容**

- 任务规划（Task Planning）：LLM 将复杂问题拆解为子任务的策略
- 自主智能体（Autonomous Agents）：ReAct 模式（Reasoning + Acting 交替循环）
- 迭代改进（Iterative Improvement）：多轮推理逐步逼近最优答案
- 自我反思（Self-Reflection）：Agent 评估自身输出质量并修正错误
- 工具调用编排：多工具串联、条件分支、并行调用
- Agent 记忆机制：短期记忆（上下文窗口）、长期记忆（向量存储）、工作记忆（scratchpad）

**检查点**

- [ ] 理解 ReAct 循环的 Thought→Action→Observation 流程
- [ ] 掌握 Agent 自我反思的实现思路（输出质量评估 + 重新生成）
- [ ] 能设计一个多步推理 Agent 的任务规划方案

---

### D135：RAG + Agent 融合

**学习内容**

- 知识库优先策略：先检索本地知识库，相关度不足时 fallback 到外部搜索
- 置信度路由（Confidence Routing）：根据检索结果的相似度分数决定回答策略
  - 高置信度：直接基于检索结果生成回答
  - 中置信度：结合检索结果 + LLM 通用知识
  - 低置信度：触发外部搜索或请求用户澄清
- 多源融合：向量检索 + 关键词检索 + 知识图谱的混合检索策略
- 答案溯源（Citation）：回答中引用原始文档段落与来源
- 自适应 RAG：根据问题类型动态选择检索策略（事实型/分析型/开放型）

**检查点**

- [ ] 理解置信度路由的三级策略及阈值设定方法
- [ ] 掌握 RAG + Agent 融合架构的数据流
- [ ] 能设计一个自适应 RAG 的问题分类与策略映射方案

---

### D136：链路追踪 OpenTelemetry

**学习内容**

- 分布式追踪核心概念：Trace（调用链）、Span（操作单元）、SpanContext（上下文传播）
- OpenTelemetry SDK：TracerProvider、Tracer、Span 创建与属性设置
- 上下文传播（Context Propagation）：W3C TraceContext 标准、跨服务传递 trace ID
- 自动埋点 vs 手动埋点：FastAPI、httpx、SQLAlchemy 的自动 instrumentation
- Jaeger 后端：Span 数据收集、存储与可视化
- AI 系统埋点设计：LLM 调用 span、检索 span、嵌入计算 span 的层级关系

**检查点**

- [ ] 理解 Trace → Span 的父子关系与上下文传播机制
- [ ] 掌握 OpenTelemetry Python SDK 的基本使用模式
- [ ] 能设计 RAG 系统的 Span 层级结构（请求→检索→LLM→响应）

---

### D137：告警

**学习内容**

- SLO（Service Level Objective）定义：可用性 99.9%、P95 延迟 < 500ms
- SLI（Service Level Indicator）选择：与 SLO 对应的可量化指标
- Error Budget：SLO 余量管理，错误预算耗尽时暂停变更
- Grafana Alerting：告警规则、通知渠道、告警分级（P0-P3）
- Slack/钉钉集成：Webhook 配置、告警消息模板定制
- 告警最佳实践：避免告警风暴、设置合理阈值、告警可操作性

**检查点**

- [ ] 能为 RAG 系统定义 SLO 与对应的 SLI
- [ ] 掌握 Grafana 告警规则配置方法
- [ ] 理解 Error Budget 的概念与实际应用

---

### D138：日志聚合

**学习内容**

- 日志聚合方案对比：ELK（Elasticsearch + Logstash + Kibana）vs Loki + Grafana
- Loki 架构：日志标签索引、LogQL 查询语法、与 Prometheus 标签体系对齐
- 结构化日志：JSON 格式日志、统一字段规范（timestamp、level、service、trace_id）
- 日志与链路关联：通过 trace_id 将日志条目与 OpenTelemetry Span 关联
- Python 日志最佳实践：structlog 库、日志级别策略、敏感信息脱敏
- 可观测性三支柱整合：Metrics + Traces + Logs 的统一查询与关联分析

**检查点**

- [ ] 理解 ELK 与 Loki 的架构差异与选型依据
- [ ] 掌握通过 trace_id 关联日志与链路的方法
- [ ] 能设计结构化日志的字段规范

---

### D139 Sat (8h)：Buffer 5 — 复盘 Phase 6 + 性能优化验收

**学习内容**

- Phase 6 知识点回顾：并发优化、连接池、PostgreSQL 高级特性、pgvector
- 性能优化验收：
  - 文档摄入并发优化是否达成 3x 加速目标
  - 压力测试报告完整性检查
  - pgvector 迁移功能与性能验证
- 查漏补缺：回顾未掌握的检查点，针对性补强
- 知识沉淀：整理并发优化与数据库调优的最佳实践清单

**检查点**

- [ ] Phase 6 并发与数据库相关检查点全部完成
- [ ] 性能优化目标达成（文档摄入 3x 加速、pgvector 正常运行）
- [ ] 输出性能优化最佳实践总结

---

### D140 Sun (8h)：Buffer 5 — 监控全栈验收

**学习内容**

- 监控全栈验收：
  - Prometheus 指标采集正常，PromQL 查询准确
  - Grafana 仪表盘展示完整（Token 成本、延迟分位数、缓存命中率）
  - OpenTelemetry 链路追踪端到端可用（Jaeger 可视化调用链）
- 可观测性整合验证：
  - 从 Grafana 告警→定位异常指标→查看关联 Trace→查看关联日志 的完整排查流程
- 告警规则有效性测试：模拟异常场景验证告警触发
- Phase 6 总结与 Phase 7 准备

**检查点**

- [ ] Prometheus + Grafana + OpenTelemetry 全栈运行正常
- [ ] 完成一次端到端的异常排查演练（指标→链路→日志）
- [ ] 告警规则至少覆盖 SLO 中定义的关键指标

---

## 里程碑 6

> **并发优化完成**（文档摄入 3x 加速）。**pgvector 运行**（从 ChromaDB 完成迁移，混合查询可用）。**Prometheus + Grafana 监控**（AI 专属仪表盘，Token 成本/延迟 P95/缓存命中率）。**OpenTelemetry 链路追踪**（Jaeger 可视化）。**RAG + Agent 融合模式**（置信度路由，知识库优先策略）。

### 里程碑验收标准

| 验收项 | 达标标准 |
|:------|:--------|
| 并发优化 | 文档摄入耗时降至优化前的 1/3 以下 |
| pgvector | 数据迁移完成，混合查询延迟 < 100ms（1000 条文档规模） |
| 监控仪表盘 | Grafana 展示 Token 成本、P95 延迟、缓存命中率三项核心指标 |
| 链路追踪 | Jaeger 可查看完整的 请求→检索→LLM→响应 调用链 |
| Agent 融合 | 置信度路由逻辑可运行，低置信度场景触发 fallback |
| 压力测试 | 产出包含 RPS、P95 延迟、错误率的性能基准报告 |
