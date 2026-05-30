# 每日学习计划总览（日历速查表）

> 工作日 2h · 周末 6h · 共 20 周 · 440 小时

---

## 第一阶段：Python 速通（Week 1，仅前 3 天）

> **全栈开发者版**：只学 Python 特有语法，Day 4-7 时间并入后续阶段

| 天 | 日期标记 | 时长 | 主题 | 核心任务 | 当日产出 |
|:--|:--|:--|:--|:--|:--|
| Day 1 | 周一 | 2h | Python 特有语法 | 类型注解/Pydantic/f-string/推导式/pathlib | 能写带注解的 Python 脚本 |
| Day 2 | 周二 | 2h | async/await + 装饰器 | 与 Node.js 的差异/@lru_cache/venv 管理 | 异步 HTTP 请求跑通 |
| Day 3 | 周三 | 2h | AI 开发模式 + 环境搭建 | 单例模式/上下文管理器/工具配置/.env | 开发环境就绪，里程碑 1 |

---

## 第二阶段：LLM API + Prompt（Week 2-3）

### Week 2

| 天 | 日期标记 | 时长 | 主题 | 核心任务 | 当日产出 |
|:--|:--|:--|:--|:--|:--|
| Day 8 | 周一 | 2h | 申请API + 首次调用 | 注册智谱AI/创建.env/第一个LLM调用 | API调通，收到AI回复 |
| Day 9 | 周二 | 2h | messages结构 | system/user/assistant/多轮对话 | 有记忆的对话程序 |
| Day 10 | 周三 | 2h | Token + 成本控制 + 流式 | tiktoken/max_tokens/streaming/temperature | 逐字显示+费用估算 |
| Day 11 | 周四 | 2h | 结构化输出 | JSON mode/信息提取 | 自动提取姓名年龄城市 |
| Day 12 | 周五 | 2h | 上下文截断 | ChatSession类/历史限制 | 安全的多轮对话 |
| Day 13 | 周六 | 6h | Prompt Engineering | Role/Few-shot/CoT/格式控制 | 3个高质量Prompt模板 |
| Day 14 | 周日 | 6h | 里程碑2项目 | 完整命令行聊天机器人 | **里程碑 2 达成** |

### Week 3

| 天 | 日期标记 | 时长 | 主题 | 核心任务 | 当日产出 |
|:--|:--|:--|:--|:--|:--|
| Day 15 | 周一 | 2h | LangChain基础 | 安装/ChatModel/PromptTemplate | LangChain调通 |
| Day 16 | 周二 | 2h | LCEL管道语法 | \| 连接/stream/batch | 3种调用方式 |
| Day 17 | 周三 | 2h | LangChain重写聊天机器人 | 用LCEL重写Day14项目 | LangChain版聊天机器人 |
| Day 18 | 周四 | 2h | 文章摘要工具 | 长文本处理/摘要+关键词+评分 | 摘要工具 |
| Day 19 | 周五 | 2h | Function Calling 初体验 | 工具定义/JSON Schema/决策流程 | 理解 Agent 的基础 |
| Day 20 | 周六 | 6h | Gradio界面 | 安装Gradio/聊天界面/推送GitHub | Web版聊天机器人 |
| Day 21 | 周日 | 6h | 复习 + Prompt课程 | 深化LCEL/读官方文档 | 知识巩固 |

---

## 第三阶段：RAG 知识库系统（Week 4-7）

### Week 4

| 天 | 日期标记 | 时长 | 主题 | 核心任务 | 当日产出 |
|:--|:--|:--|:--|:--|:--|
| Day 22 | 周一 | 2h | Embedding概念 | 安装SentenceTransformer/计算相似度 | 理解语义向量 |
| Day 23 | 周二 | 2h | ChromaDB基础 | 安装/add/query/delete | 向量库增删查操作 |
| Day 24 | 周三 | 2h | PDF/TXT/MD解析 | LangChain各种Loader | 多格式文档解析 |
| Day 25 | 周四 | 2h | 文本分块策略 | RecursiveCharacterTextSplitter/参数 | 最优分块配置 |
| Day 26 | 周五 | 2h | 第一个RAG Pipeline | 加载→分块→向量化→检索→生成 | 端到端RAG跑通 |
| Day 27 | 周六 | 6h | RAG综合实践 | 多文档/持久化/交互式问答 | 多文档知识库 |
| Day 28 | 周日 | 6h | LangChain RAG链 | RetrievalQA/带来源引用 | 标准RAG实现 |

### Week 5

| 天 | 日期标记 | 时长 | 主题 | 核心任务 | 当日产出 |
|:--|:--|:--|:--|:--|:--|
| Day 29 | 周一 | 2h | Word/Excel解析 | Docx2txtLoader/Excel解析 | 支持Word/Excel |
| Day 30 | 周二 | 2h | 统一加载器 | 按扩展名分派Loader | 通用文档加载器 |
| Day 31 | 周三 | 2h | 混合检索 | BM25 + 向量 + EnsembleRetriever | 混合检索器 |
| Day 32 | 周四 | 2h | Rerank重排序 | CrossEncoder/bge-reranker | 带Rerank的检索 |
| Day 33 | 周五 | 2h | 查询增强 HyDE + Parent Doc | HyDE实现/ParentDocumentRetriever | 查询增强+上下文保留 |
| Day 34 | 周六 | 6h | 完整RAG CLI | 完整功能的命令行RAG工具 | RAG CLI 完成 |
| Day 35 | 周日 | 6h | RAGAs评估基础 | 安装RAGAs/构建测试集 | RAG质量基准 |

### Week 6

| 天 | 日期标记 | 时长 | 主题 | 核心任务 | 当日产出 |
|:--|:--|:--|:--|:--|:--|
| Day 36 | 周一 | 2h | FastAPI基础 | 安装/路由/Pydantic模型 | Hello FastAPI |
| Day 37 | 周二 | 2h | 文件上传接口 | UploadFile/异步/类型验证 | 文档上传API |
| Day 38 | 周三 | 2h | 查询接口 | POST /chat/同步响应 | 问答API |
| Day 39 | 周四 | 2h | 流式响应SSE | StreamingResponse/async generator | 流式问答API |
| Day 40 | 周五 | 2h | 错误处理与中间件 | 全局异常/CORS/Swagger文档 | 生产级API |
| Day 41 | 周六 | 6h | Redis 基础与缓存 | 安装/5种数据结构/LLM缓存 | Redis 缓存系统 |
| Day 42 | 周日 | 6h | Embedding 缓存与限流 | CachedEmbeddingProvider/API限流 | 缓存+限流完成 |

### Week 7

| 天 | 日期标记 | 时长 | 主题 | 核心任务 | 当日产出 |
|:--|:--|:--|:--|:--|:--|
| Day 43 | 周一 | 2h | 缓存三大问题 | 穿透/击穿/雪崩的解决方案 | 生产级缓存策略 |
| Day 44 | 周二 | 2h | 完整RAG API | 整合所有组件/Postman测试 | RAG API 完成 |
| Day 45 | 周三 | 2h | RAG质量分析 | 找出检索失败的案例 | 问题清单 |
| Day 46 | 周四 | 2h | 元数据过滤优化 | 按来源/时间过滤检索 | 更精准的检索 |
| Day 47 | 周五 | 2h | Prompt调优 | System Prompt改进/减少幻觉 | 更准确的回答 |
| Day 48 | 周六 | 6h | 性能优化与评估 | 并行向量化/RAGAs对比 | 量化改善效果 |
| Day 49 | 周日 | 6h | 文档完善 | README/API文档/架构图 | **里程碑 3 达成** |

---

## 第四阶段：工程化基础（Week 8-9）

### Week 8

| 天 | 日期标记 | 时长 | 主题 | 核心任务 | 当日产出 |
|:--|:--|:--|:--|:--|:--|
| Day 50 | 周一 | 2h | Docker基础 | 安装/hello-world/基本命令 | Docker环境就绪 |
| Day 51 | 周二 | 2h | 编写Dockerfile | 构建镜像/运行容器/映射端口 | 容器化的AI应用 |
| Day 52 | 周三 | 2h | Docker Compose | 多服务编排/数据卷/自动重启 | Compose配置 |
| Day 53 | 周四 | 2h | 配置管理 | pydantic-settings/.env管理 | 生产级配置 |
| Day 54 | 周五 | 2h | API认证+限流 | APIKeyHeader/slowapi | 安全API |
| Day 55 | 周六 | 6h | pytest 单元测试 | conftest/mock重型依赖/测试用例 | 测试套件 |
| Day 56 | 周日 | 6h | GitHub Actions CI | ci.yml/自动跑测试/PR保护 | 自动化CI流程 |

### Week 9

| 天 | 日期标记 | 时长 | 主题 | 核心任务 | 当日产出 |
|:--|:--|:--|:--|:--|:--|
| Day 57 | 周一 | 2h | Ollama 本地模型 | 安装/qwen2.5/LangChain接入 | 零费用本地开发 |
| Day 58 | 周二 | 2h | 日志系统 | logging配置/文件+控制台双输出 | 结构化日志 |
| Day 59 | 周三 | 2h | 性能优化+健康检查 | embedding缓存/异步处理/健康检查端点 | 可监控的服务 |
| Day 60 | 周四 | 2h | Railway部署 | 注册/部署/设置环境变量 | 公网访问的API |
| Day 61 | 周五 | 2h | 服务器部署 | 购买ECS/安装Docker/部署 | 部署完成 |
| Day 62 | 周六 | 6h | 全面测试 | E2E测试/压力测试/修复BUG | 稳定的服务 |
| Day 63 | 周日 | 6h | 文档与演示 | README/部署文档/Demo视频 | **里程碑 4 达成** |

---

## 第五阶段：Agent 系统（Week 10-12）

### Week 10

| 天 | 日期标记 | 时长 | 主题 | 核心任务 | 当日产出 |
|:--|:--|:--|:--|:--|:--|
| Day 64 | 周一 | 2h | Function Calling原理 | JSON Schema/工具定义/调用循环 | 天气查询Agent |
| Day 65 | 周二 | 2h | 搜索工具集成 | Tavily API/申请key/集成 | 能搜索的Agent |
| Day 66 | 周三 | 2h | 代码/计算工具 | 安全执行Python/数学计算 | 多工具Agent |
| Day 67 | 周四 | 2h | 错误处理重试 | 指数退避/最大步数限制 | 稳健的Agent |
| Day 68 | 周五 | 2h | 工具调用日志 | 打印推理过程/调试 | 可观测的Agent |
| Day 69 | 周六 | 6h | 多工具Agent实战 | 搜索+计算+保存文件 | 综合Agent |
| Day 70 | 周日 | 6h | 深化工具开发 | 自定义工具/工具错误处理 | 工具库 |

### Week 11

| 天 | 日期标记 | 时长 | 主题 | 核心任务 | 当日产出 |
|:--|:--|:--|:--|:--|:--|
| Day 71 | 周一 | 2h | LangGraph 基础 | StateGraph/节点/条件路由 | 第一个 LangGraph Agent |
| Day 72 | 周二 | 2h | LangGraph 工具节点 | ToolNode/工具集成/循环图 | 多工具 LangGraph Agent |
| Day 73 | 周三 | 2h | LangGraph Memory | Checkpointer/跨会话记忆/thread_id | 有记忆的 Agent |
| Day 74 | 周四 | 2h | Human-in-the-loop | interrupt_before/审批流程 | 可审批的 Agent |
| Day 75 | 周五 | 2h | CrewAI 了解 | 多 Agent 协作概念/vs LangGraph | 理解不同框架定位 |
| Day 76 | 周六 | 6h | Research Agent实现 | 完整的研究报告Agent（LangGraph版） | **里程碑 6 达成** |
| Day 77 | 周日 | 6h | Agent测试与复习 | 多主题测试/代码整理/GitHub | 里程碑6完善 |

### Week 12

| 天 | 日期标记 | 时长 | 主题 | 核心任务 | 当日产出 |
|:--|:--|:--|:--|:--|:--|
| Day 78 | 周一 | 2h | LangSmith可观测性 | 注册/配置/查看调用链路 | 可视化调用追踪 |
| Day 79 | 周二 | 2h | Agent性能调优 | 减少token消耗/并行工具调用 | 更快的Agent |
| Day 80 | 周三 | 2h | RAG + Agent融合 | IntelligentAssistant类 | 混合知识系统 |
| Day 81 | 周四 | 2h | 流式Agent输出 | 流式显示Agent推理过程 | 更好的用户体验 |
| Day 82 | 周五 | 2h | Agent测试策略 | 测试用例设计/异常场景 | 测试套件 |
| Day 83 | 周六 | 6h | 综合项目1 | RAG知识库 + Agent搜索融合 | 完整AI助手 |
| Day 84 | 周日 | 6h | Phase6复习总结 | 整理代码/写总结文档 | Phase6结案 |

---

## 第六阶段：并发优化（Week 13-14）

### Week 13

| 天 | 日期标记 | 时长 | 主题 | 核心任务 | 当日产出 |
|:--|:--|:--|:--|:--|:--|
| Day 85 | 周一 | 2h | asyncio 深入 | gather/Semaphore/并发限制 | 并发 LLM 调用 |
| Day 86 | 周二 | 2h | GIL 与 threading | 线程池/Queue/适用场景 | 理解 GIL 限制 |
| Day 87 | 周三 | 2h | 连接池 | httpx 连接复用/数据库连接池 | 高效资源管理 |
| Day 88 | 周四 | 2h | 并发问题与锁 | asyncio.Lock/竞态条件 | 线程安全代码 |
| Day 89 | 周五 | 2h | 批量文档处理加速（上） | asyncio 并发解析 | I/O 并发优化 |
| Day 90 | 周六 | 6h | 批量文档处理加速（下） | ThreadPoolExecutor embedding | CPU 并发优化 |
| Day 91 | 周日 | 6h | 性能压测对比 | 压测前后性能数据/优化总结 | 并发优化完成 |

### Week 14

| 天 | 日期标记 | 时长 | 主题 | 核心任务 | 当日产出 |
|:--|:--|:--|:--|:--|:--|
| Day 92 | 周一 | 2h | Celery 基础 | 安装/Redis broker/第一个任务 | Celery 环境就绪 |
| Day 93 | 周二 | 2h | FastAPI 集成 | 上传返回 task_id/轮询进度 | 异步上传接口 |
| Day 94 | 周三 | 2h | 任务优先级与队列 | 多队列路由/优先级设置 | 任务调度系统 |
| Day 95 | 周四 | 2h | Flower 监控 | 安装/配置/任务可视化 | 监控面板 |
| Day 96 | 周五 | 2h | 进度报告 | update_state/前端进度条 | 实时进度反馈 |
| Day 97 | 周六 | 6h | 综合实践 | 文档摄入异步化完整实现 | 异步摄入系统 |
| Day 98 | 周日 | 6h | 压力测试 | locust 并发测试/性能调优 | **里程碑 6 达成** |

---

## 第七阶段：分布式架构（Week 15-16）

### Week 15

| 天 | 日期标记 | 时长 | 主题 | 核心任务 | 当日产出 |
|:--|:--|:--|:--|:--|:--|
| Day 99 | 周一 | 2h | CAP 定理与一致性 | CP vs AP/最终一致性 | 理解分布式权衡 |
| Day 100 | 周二 | 2h | 无状态服务设计 | 会话存 Redis/文件存对象存储 | 可扩展架构 |
| Day 101 | 周三 | 2h | 分布式锁 | Redis 分布式锁实现 | 并发控制 |
| Day 102 | 周四 | 2h | Nginx 负载均衡 | upstream 配置/健康检查 | 流量分发 |
| Day 103 | 周五 | 2h | 后端架构设计题训练（上） | 10万用户 RAG 系统设计 | 架构设计能力 |
| Day 104 | 周六 | 6h | 后端架构设计题训练（下） | 高并发场景设计/画架构图 | 架构设计深化 |
| Day 105 | 周日 | 6h | 后端面试题整理 | 缓存/队列/并发/分布式 | 面试准备 |

### Week 16

| 天 | 日期标记 | 时长 | 主题 | 核心任务 | 当日产出 |
|:--|:--|:--|:--|:--|:--|
| Day 106 | 周一 | 2h | 消息队列深入 | RabbitMQ vs Kafka/使用场景 | 理解消息队列 |
| Day 107 | 周二 | 2h | 微服务通信 | gRPC/REST/服务发现 | 服务间通信 |
| Day 108 | 周三 | 2h | 可观测性 | Prometheus/Grafana/链路追踪 | 监控体系 |
| Day 109 | 周四 | 2h | 容错与降级 | 熔断器/限流/降级策略 | 高可用设计 |
| Day 110 | 周五 | 2h | 数据库扩展 | 主从复制/分库分表/读写分离 | 数据层扩展 |
| Day 111 | 周六 | 6h | 综合架构设计 | 完整的高并发 AI 服务架构 | 架构图与文档 |
| Day 112 | 周日 | 6h | Phase7 复习总结 | 整理笔记/准备项目阶段 | **里程碑 7 达成** |

---

## 第八阶段：综合项目实战（Week 17-20）

### Week 17-18：项目开发

| 天 | 日期标记 | 时长 | 主题 |
|:--|:--|:--|:--|
| Day 113-114 | 周一-周二 | 2h×2 | 项目规划/架构设计/目录结构 |
| Day 115-116 | 周三-周四 | 2h×2 | 核心RAG引擎 |
| Day 117-118 | 周五-周六 | 2h+6h | 会话管理/前端界面 |
| Day 119 | 周日 | 6h | 前端完善/联调 |
| Day 120-121 | 周一-周二 | 2h×2 | 错误处理/边界情况 |
| Day 122-123 | 周三-周四 | 2h×2 | 性能优化/异步任务 |
| Day 124-125 | 周五-周六 | 2h+6h | 安全加固/集成测试 |
| Day 126 | 周日 | 6h | 全面测试/BUG修复 |

### Week 19-20：作品集与总结
| 天 | 日期标记 | 时长 | 主题 |
|:--|:--|:--|:--|
| Day 127-128 | 周一-周二 | 2h×2 | README撰写/项目文档 |
| Day 129-130 | 周三-周四 | 2h×2 | 代码整理/Code Review |
| Day 131 | 周五 | 2h | 部署最终版本 |
| Day 132-133 | 周末 | 6h×2 | 第二个项目（Text2SQL）/深化技术 |
| Day 134-135 | 周一-周二 | 2h×2 | 技术栈总结/能力梳理 |
| Day 136-137 | 周三-周四 | 2h×2 | 面试题准备/技术表达练习 |
| Day 138-139 | 周五-周六 | 2h+6h | 作品集检查/GitHub整理 |
| Day 140 | 周日 | 6h | **结业总结 + 里程碑 8 达成** |

---

## 里程碑时间线

```
Week 1  → 里程碑 1：命令行工具（Python基础验收）
Week 3  → 里程碑 2：聊天机器人（LLM调用验收）
Week 7  → 里程碑 3：RAG API + Redis 缓存（检索+缓存验收）
Week 9  → 里程碑 4：RAG API 生产就绪（工程化验收）
Week 12 → 里程碑 5：Research Agent + Celery（智能体+异步验收）
Week 14 → 里程碑 6：并发优化完成（并发性能验收）
Week 16 → 里程碑 7：分布式架构掌握（架构设计验收）
Week 20 → 里程碑 8：完整作品集（综合能力验收）
```

---

## 每周复盘问题

每周末花 30 分钟回答：
1. 这周学了什么？能用自己的话解释吗？
2. 做了什么项目/练习？
3. 哪个地方还不清楚？（安排下周补充）
4. 里程碑进度如何？
