# 每日学习计划总览（日历速查表）

> 工作日 2h · 周末 8h · 共 28 周 · 728 小时

**起止日期**：2026-04-06（周一）至 2026-10-18（周日）

**日编号权威映射**：
- Phase 1: W01 (D1-D7)
- Phase 2: W02-W04 (D8-D28) — D27-28 为 Buffer 1
- Phase 3: W05-W09 (D29-D63) — D62-63 为 Buffer 2
- Phase 4: W10-W12 (D64-D84) — D83-84 为 Buffer 3
- Phase 5: W13-W17 (D85-D119) — D118-119 为 Buffer 4
- Phase 6: W18-W20 (D120-D140) — D139-140 为 Buffer 5
- Phase 7: W21-W22 (D141-D154) — D153-154 为 Buffer 6
- Phase 8: W23-W28 (D155-D196) — D195-196 为 Buffer 7

---

## Phase 1：Python 现代化（W01，D1-D7）

| 天 | 日期标记 | 时长 | Phase | 主题 | 核心任务 | 当日产出 |
|:---|:--------|:-----|:------|:-----|:--------|:--------|
| D1 | 周一 | 2h | Phase 1 | 类型注解 + Pydantic + f-string | 学习类型提示、Pydantic 模型验证、格式化字符串 | 类型注解示例代码 + Pydantic 模型 |
| D2 | 周二 | 2h | Phase 1 | async/await + 装饰器 + 与 Node.js 对比 | 异步编程基础、装饰器模式、对比 JS 异步 | 异步函数示例 + 装饰器实现 |
| D3 | 周三 | 2h | Phase 1 | 生成器 + 上下文管理器 + httpx | 生成器原理、with 语句、HTTP 客户端 | 生成器示例 + httpx 请求封装 |
| D4 | 周四 | 2h | Phase 1 | pytest 深入（fixtures/parametrize/mock） | 测试夹具、参数化测试、Mock 对象 | 完整测试套件示例 |
| D5 | 周五 | 2h | Phase 1 | Python 包管理（pyproject.toml/venv/uv） | 现代包管理、虚拟环境、uv 工具 | pyproject.toml 配置 + 依赖管理文档 |
| D6 | 周六 | 8h | Phase 1 | 实战：构建异步 CLI 工具 | 使用 Click + asyncio 构建命令行工具 | 完整异步 CLI 项目 |
| D7 | 周日 | 8h | Phase 1 | 实战：编写完整测试套件 | 为 CLI 工具编写单元测试和集成测试 | 测试覆盖率 >80% 的测试套件 |

---

## Phase 2：LLM API 与 Prompt 工程（W02-W04，D8-D28）

| 天 | 日期标记 | 时长 | Phase | 主题 | 核心任务 | 当日产出 |
|:---|:--------|:-----|:------|:-----|:--------|:--------|
| D8 | 周一 | 2h | Phase 2 | Claude API 基础（Messages API/system prompt/streaming） | 学习 Claude API 调用、系统提示、流式响应 | Claude API 调用示例 |
| D9 | 周二 | 2h | Phase 2 | Claude Structured Output（tool_use 强制 JSON） | 使用 tool_use 获取结构化输出 | 结构化输出示例代码 |
| D10 | 周三 | 2h | Phase 2 | Claude Prompt Caching + 成本优化 | 提示缓存机制、成本计算与优化 | 缓存策略文档 + 成本分析 |
| D11 | 周四 | 2h | Phase 2 | OpenAI API（chat completions/function calling/对比 Claude） | OpenAI API 使用、函数调用、与 Claude 对比 | OpenAI API 示例 + 对比表格 |
| D12 | 周五 | 2h | Phase 2 | 智谱 AI API（GLM-4/免费额度/SDK 差异） | 智谱 AI 接入、免费额度使用、SDK 差异 | 智谱 AI 调用示例 |
| D13 | 周六 | 8h | Phase 2 | 实战：多厂商 LLM 客户端抽象层 | 设计统一接口支持三家 LLM 提供商 | 多厂商 LLM 客户端库 |
| D14 | 周日 | 8h | Phase 2 | 实战：Provider 切换配置 + 三厂商测试 | 配置驱动的提供商切换、完整测试 | 配置化 LLM 客户端 + 测试报告 |
| D15 | 周一 | 2h | Phase 2 | Prompt 基础（Role/Few-shot/CoT/格式控制） | 角色设定、少样本学习、思维链、格式控制 | Prompt 模板库 |
| D16 | 周二 | 2h | Phase 2 | Prompt 进阶（Self-consistency/ToT/Prompt 链） | 自洽性、思维树、提示链 | 进阶 Prompt 示例 |
| D17 | 周三 | 2h | Phase 2 | RAG 专用 Prompt（上下文注入/引用/仅基于资料回答） | RAG 场景提示工程、引用格式、幻觉控制 | RAG Prompt 模板 |
| D18 | 周四 | 2h | Phase 2 | Prompt 测试与评估（A/B 对比/指标设计） | Prompt 效果评估、A/B 测试、指标体系 | Prompt 评估框架 |
| D19 | 周五 | 2h | Phase 2 | MCP 协议入门（架构/Server-Client 模型） | MCP 协议概念、架构设计、通信模型 | MCP 协议笔记 |
| D20 | 周六 | 8h | Phase 2 | 实战：Prompt 工程工作台 CLI | 构建 Prompt 测试、对比、评估工具 | Prompt 工作台 CLI 工具 |
| D21 | 周日 | 8h | Phase 2 | 实战：MCP Server 基础实现（文件系统工具） | 实现基础 MCP Server 提供文件操作能力 | MCP Server 文件系统工具 |
| D22 | 周一 | 2h | Phase 2 | Claude Vision API（图片分析/OCR） | 图片理解、OCR 能力、多模态应用 | Vision API 示例 |
| D23 | 周二 | 2h | Phase 2 | Token 计算 + 成本估算 + 限流策略 | Token 计数、成本预估、限流设计 | 成本计算器 + 限流方案 |
| D24 | 周三 | 2h | Phase 2 | 安全（内容过滤/拒绝处理/System Prompt 安全） | 内容安全、提示注入防护、安全最佳实践 | 安全检查清单 |
| D25 | 周四 | 2h | Phase 2 | API 最佳实践（重试/退避/降级/熔断） | 重试策略、指数退避、服务降级、熔断器 | API 调用最佳实践文档 |
| D26 | 周五 | 2h | Phase 2 | 复习：回顾 Phase 1-2 薄弱点 | 复习前两阶段知识点、查缺补漏 | 知识点复习笔记 |
| D27 | 周六 | 8h | Phase 2 | **Buffer 1**：复盘 + 补短板 | 深度复盘 Phase 1-2、补强薄弱环节 | 复盘报告 + 补充练习 |
| D28 | 周日 | 8h | Phase 2 | **Buffer 1**：LLM 客户端验收测试 | 完整测试多厂商 LLM 客户端、性能验证 | LLM 客户端验收报告 |

---

## Phase 3：RAG 核心技术（W05-W09，D29-D63）

| 天 | 日期标记 | 时长 | Phase | 主题 | 核心任务 | 当日产出 |
|:---|:--------|:-----|:------|:-----|:--------|:--------|
| D29 | 周一 | 2h | Phase 3 | Embedding 原理（向量空间/余弦相似度/维度） | 向量表示、相似度计算、维度理解 | Embedding 原理笔记 |
| D30 | 周二 | 2h | Phase 3 | sentence-transformers（模型选择/多语言/bge-m3） | 模型选型、多语言支持、bge-m3 使用 | sentence-transformers 示例 |
| D31 | 周三 | 2h | Phase 3 | 裸写向量搜索（numpy 手动余弦相似度） | 使用 numpy 实现向量检索 | 手写向量搜索代码 |
| D32 | 周四 | 2h | Phase 3 | ChromaDB 基础（集合/元数据/持久化/距离度量） | ChromaDB 使用、元数据管理、持久化 | ChromaDB 操作示例 |
| D33 | 周五 | 2h | Phase 3 | 向量库对比（ChromaDB vs FAISS vs Pinecone vs Milvus） | 向量库选型、性能对比、适用场景 | 向量库对比表格 |
| D34 | 周六 | 8h | Phase 3 | 实战：裸写完整 RAG Pipeline（加载→分块→嵌入→检索→生成） | 从零实现 RAG 全流程 | 完整 RAG Pipeline 代码 |
| D35 | 周日 | 8h | Phase 3 | 实战：多格式文档解析（PDF/Word/MD/TXT/Excel） | 实现多格式文档解析器 | 多格式文档解析库 |
| D36 | 周一 | 2h | Phase 3 | 分块策略（固定/递归/语义/按结构） | 文本分块方法、策略选择 | 分块策略对比文档 |
| D37 | 周二 | 2h | Phase 3 | 分块优化（overlap/元数据/父子文档） | 重叠分块、元数据保留、层级文档 | 优化分块实现 |
| D38 | 周三 | 2h | Phase 3 | BM25 关键词检索 + 混合检索原理 | BM25 算法、向量+关键词混合检索 | BM25 + 混合检索示例 |
| D39 | 周四 | 2h | Phase 3 | Rerank 重排序（CrossEncoder/LLM-based） | 重排序原理、CrossEncoder、LLM 重排 | Rerank 实现代码 |
| D40 | 周五 | 2h | Phase 3 | 查询增强（HyDE/多查询/查询扩展） | HyDE 方法、查询改写、查询扩展 | 查询增强示例 |
| D41 | 周六 | 8h | Phase 3 | 实战：混合检索 + Rerank 集成 | 集成 BM25 + 向量检索 + 重排序 | 混合检索系统 |
| D42 | 周日 | 8h | Phase 3 | 实战：HyDE + 检索质量评测（precision/recall） | 实现 HyDE、评测检索质量 | HyDE 实现 + 评测报告 |
| D43 | 周一 | 2h | Phase 3 | LangChain 核心（Chain/Prompt/OutputParser/Memory） | LangChain 基础组件、链式调用 | LangChain 基础示例 |
| D44 | 周二 | 2h | Phase 3 | LangChain 文档处理（Loader/Splitter/Embedding） | 文档加载、分块、嵌入 | LangChain 文档处理示例 |
| D45 | 周三 | 2h | Phase 3 | LangChain 向量库 + 检索器 | 向量库集成、检索器使用 | LangChain 检索示例 |
| D46 | 周四 | 2h | Phase 3 | LCEL 管道语法（\| 连接/stream/batch） | LCEL 语法、流式处理、批处理 | LCEL 管道示例 |
| D47 | 周五 | 2h | Phase 3 | LlamaIndex 概览（与 LangChain 对比/选型） | LlamaIndex 特性、框架对比、选型建议 | 框架对比文档 |
| D48 | 周六 | 8h | Phase 3 | 实战：LangChain 重写 RAG Pipeline（对比裸写） | 使用 LangChain 重构 RAG、性能对比 | LangChain RAG 实现 + 对比报告 |
| D49 | 周日 | 8h | Phase 3 | 实战：带记忆的对话式 RAG（LangChain） | 实现多轮对话 RAG、会话记忆 | 对话式 RAG 系统 |
| D50 | 周一 | 2h | Phase 3 | FastAPI 基础（路由/Pydantic 模型/依赖注入） | FastAPI 路由、请求验证、依赖注入 | FastAPI 基础示例 |
| D51 | 周二 | 2h | Phase 3 | FastAPI 异步 + SSE 流式响应 | 异步路由、Server-Sent Events 流式 | 流式响应示例 |
| D52 | 周三 | 2h | Phase 3 | Redis 基础（5 种数据结构/安装/CLI） | Redis 数据结构、基础操作 | Redis 操作笔记 |
| D53 | 周四 | 2h | Phase 3 | Redis 缓存实践（LLM 响应缓存/Embedding 缓存/语义缓存） | LLM 缓存策略、语义缓存实现 | Redis 缓存方案 |
| D54 | 周五 | 2h | Phase 3 | Redis 限流 + 缓存三大问题（穿透/击穿/雪崩） | 限流算法、缓存问题与解决方案 | 限流 + 缓存方案文档 |
| D55 | 周六 | 8h | Phase 3 | 实战：RAG API 服务化（FastAPI + Redis 缓存） | 构建 RAG REST API、集成 Redis 缓存 | RAG API 服务 |
| D56 | 周日 | 8h | Phase 3 | 实战：完整 RAG API + Swagger 文档 + Postman 测试 | API 文档生成、接口测试 | 完整 RAG API + 测试集合 |
| D57 | 周一 | 2h | Phase 3 | 进阶 RAG 模式（CRAG/Self-RAG/Adaptive RAG） | 校正式 RAG、自适应 RAG | 进阶 RAG 模式笔记 |
| D58 | 周二 | 2h | Phase 3 | 多模态 RAG（图片/表格/代码） | 多模态文档处理、特殊格式解析 | 多模态 RAG 示例 |
| D59 | 周三 | 2h | Phase 3 | RAGAs 评估框架（faithfulness/relevancy/precision/recall） | RAG 评估指标、RAGAs 使用 | RAG 评估方案 |
| D60 | 周四 | 2h | Phase 3 | 生产 RAG 关注点（增量索引/文档版本/可扩展性） | 增量更新、版本管理、扩展性设计 | 生产 RAG 架构文档 |
| D61 | 周五 | 2h | Phase 3 | RAG 质量调优实战（诊断→优化→再评估） | 质量问题诊断、优化迭代 | RAG 调优报告 |
| D62 | 周六 | 8h | Phase 3 | **Buffer 2**：复盘 Phase 3 + RAG 项目收尾 | 深度复盘 RAG 技术、项目完善 | Phase 3 复盘报告 |
| D63 | 周日 | 8h | Phase 3 | **Buffer 2**：RAG API + Redis 缓存验收 | 完整验收 RAG API、性能测试 | RAG 系统验收报告 |

---

## Phase 4：工程化与部署（W10-W12，D64-D84）

| 天 | 日期标记 | 时长 | Phase | 主题 | 核心任务 | 当日产出 |
|:---|:--------|:-----|:------|:-----|:--------|:--------|
| D64 | 周一 | 2h | Phase 4 | Docker 基础（镜像/容器/卷/网络） | Docker 基础概念、容器操作 | Docker 基础笔记 |
| D65 | 周二 | 2h | Phase 4 | Dockerfile 编写（多阶段构建/缓存优化） | Dockerfile 最佳实践、构建优化 | 优化的 Dockerfile |
| D66 | 周三 | 2h | Phase 4 | Docker Compose（多服务编排：app+redis+chroma） | 多容器编排、服务依赖管理 | Docker Compose 配置 |
| D67 | 周四 | 2h | Phase 4 | .dockerignore + 镜像优化 | 镜像体积优化、构建加速 | 镜像优化方案 |
| D68 | 周五 | 2h | Phase 4 | 实战：容器化 RAG API（Dockerfile + Compose） | RAG API 容器化 | 容器化 RAG 项目 |
| D69 | 周六 | 8h | Phase 4 | 实战：完整多服务 Docker Compose 部署 | 部署 RAG + Redis + ChromaDB 全栈 | 完整容器化部署方案 |
| D70 | 周日 | 8h | Phase 4 | 实战：本地模型集成 Ollama + 零费用开发 | 集成 Ollama 本地模型、离线开发 | Ollama 集成方案 |
| D71 | 周一 | 2h | Phase 4 | PostgreSQL 基础（安装/SQL/索引/EXPLAIN） | PostgreSQL 基础操作、查询优化 | PostgreSQL 笔记 |
| D72 | 周二 | 2h | Phase 4 | SQLAlchemy ORM（模型定义/CRUD/关系） | ORM 模型、关系映射、CRUD 操作 | SQLAlchemy 示例 |
| D73 | 周三 | 2h | Phase 4 | Alembic 数据库迁移 | 数据库版本管理、迁移脚本 | Alembic 迁移示例 |
| D74 | 周四 | 2h | Phase 4 | 数据库设计（用户/会话/文档元数据表） | RAG 系统数据库设计、Schema 设计 | 数据库 Schema 文档 |
| D75 | 周五 | 2h | Phase 4 | GitHub Actions CI/CD（lint + test + build） | CI/CD 流水线、自动化测试 | GitHub Actions 配置 |
| D76 | 周六 | 8h | Phase 4 | 实战：FastAPI + PostgreSQL 集成（会话持久化） | 集成数据库、实现会话管理 | 带数据库的 RAG API |
| D77 | 周日 | 8h | Phase 4 | 实战：CI/CD 流水线 + PR 保护规则 | 完整 CI/CD、代码质量门禁 | CI/CD 流水线 + 规则配置 |
| D78 | 周一 | 2h | Phase 4 | 结构化日志（logging/structlog/JSON 格式） | 结构化日志、日志最佳实践 | 日志方案 |
| D79 | 周二 | 2h | Phase 4 | JWT 认证（注册/登录/Token 生成与验证） | JWT 认证流程、Token 管理 | JWT 认证实现 |
| D80 | 周三 | 2h | Phase 4 | 权限控制（RBAC/角色保护路由） | 基于角色的访问控制 | RBAC 实现 |
| D81 | 周四 | 2h | Phase 4 | 安全加固（CORS/SQL 注入防护/Refresh Token/HTTPS） | 安全最佳实践、漏洞防护 | 安全加固清单 |
| D82 | 周五 | 2h | Phase 4 | 性能分析（cProfile/py-spy/瓶颈定位） | 性能分析工具、瓶颈优化 | 性能分析报告 |
| D83 | 周六 | 8h | Phase 4 | **Buffer 3**：复盘 Phase 4 + Docker 全栈验收 | 复盘工程化技术、全栈部署验收 | Phase 4 复盘报告 |
| D84 | 周日 | 8h | Phase 4 | **Buffer 3**：CI/CD + 安全验收 | 验收 CI/CD 流水线、安全加固 | 工程化验收报告 |

---

## Phase 5：Agent 与异步架构（W13-W17，D85-D119）

| 天 | 日期标记 | 时长 | Phase | 主题 | 核心任务 | 当日产出 |
|:---|:--------|:-----|:------|:-----|:--------|:--------|
| D85 | 周一 | 2h | Phase 5 | Agent 分类（ReAct/Plan-and-Execute/Tool-Use/Autonomous） | Agent 类型、架构模式 | Agent 分类笔记 |
| D86 | 周二 | 2h | Phase 5 | LangGraph 基础（StateGraph/节点/边/条件路由） | LangGraph 核心概念、图构建 | LangGraph 基础示例 |
| D87 | 周三 | 2h | Phase 5 | LangGraph 状态管理（TypedDict/Reducer/Checkpointer） | 状态定义、状态更新、持久化 | 状态管理示例 |
| D88 | 周四 | 2h | Phase 5 | Tool-Use Agent（工具定义/Schema/执行循环） | 工具调用、Schema 设计、执行流程 | Tool-Use Agent 示例 |
| D89 | 周五 | 2h | Phase 5 | Human-in-the-loop（中断/审批/interrupt_before） | 人工介入、审批流程 | HITL Agent 示例 |
| D90 | 周六 | 8h | Phase 5 | 实战：LangGraph ReAct Agent（搜索+计算+文件） | 构建 ReAct Agent 集成多种工具 | ReAct Agent 项目 |
| D91 | 周日 | 8h | Phase 5 | 实战：带审批流的 Agent（危险操作需确认） | 实现危险操作人工审批流程 | 审批流 Agent 系统 |
| D92 | 周一 | 2h | Phase 5 | MCP 架构深入（传输层/协议消息/Server 生命周期） | MCP 协议细节、传输机制 | MCP 架构笔记 |
| D93 | 周二 | 2h | Phase 5 | MCP Server 开发（Python mcp SDK） | 使用 Python SDK 开发 MCP Server | MCP Server 示例 |
| D94 | 周三 | 2h | Phase 5 | MCP 三种能力（Tools vs Resources vs Prompts） | 工具、资源、提示三种能力对比 | MCP 能力示例 |
| D95 | 周四 | 2h | Phase 5 | MCP 客户端集成（LangGraph Agent 连接 MCP Server） | Agent 与 MCP Server 集成 | MCP 客户端集成示例 |
| D96 | 周五 | 2h | Phase 5 | 工具设计模式（幂等/错误处理/超时管理） | 工具设计最佳实践 | 工具设计模式文档 |
| D97 | 周六 | 8h | Phase 5 | 实战：MCP Server 开发（DB 访问 + 文件系统 + Web 搜索） | 实现多能力 MCP Server | 完整 MCP Server |
| D98 | 周日 | 8h | Phase 5 | 实战：MCP 驱动的开发助手（读写文件/跑测试/查 DB） | 构建开发者辅助 Agent | MCP 开发助手 |
| D99 | 周一 | 2h | Phase 5 | 多智能体模式（Supervisor/层级/对等/Swarm） | 多 Agent 协作架构模式 | 多智能体模式笔记 |
| D100 | 周二 | 2h | Phase 5 | LangGraph 多智能体（子图/Agent 交接/共享状态） | LangGraph 多 Agent 实现 | 多 Agent LangGraph 示例 |
| D101 | 周三 | 2h | Phase 5 | Agent 通信协议（消息传递 vs 共享状态 vs 黑板） | Agent 间通信模式对比 | 通信协议对比文档 |
| D102 | 周四 | 2h | Phase 5 | Agent 记忆（短期/长期/情景记忆） | Agent 记忆系统设计 | Agent 记忆实现 |
| D103 | 周五 | 2h | Phase 5 | Agent 评估（任务完成率/工具效率/多轮一致性） | Agent 评估指标与方法 | Agent 评估框架 |
| D104 | 周六 | 8h | Phase 5 | 实战：多智能体协作系统（Supervisor 编排） | 实现 Supervisor 编排多 Agent | 多智能体协作系统 |
| D105 | 周日 | 8h | Phase 5 | 实战：CrewAI 快速体验 + 与 LangGraph 对比 | CrewAI 框架体验、对比分析 | CrewAI 示例 + 对比报告 |
| D106 | 周一 | 2h | Phase 5 | Celery 基础（Worker/Broker/Backend/任务定义） | Celery 核心概念、任务定义 | Celery 基础示例 |
| D107 | 周二 | 2h | Phase 5 | Celery 任务模式（重试/链/组/和弦/定时任务） | 高级任务模式 | Celery 任务模式示例 |
| D108 | 周三 | 2h | Phase 5 | Celery + FastAPI 集成（async 提交 + 进度轮询） | 异步任务提交、进度查询 | Celery + FastAPI 集成 |
| D109 | 周四 | 2h | Phase 5 | 消息队列理论（at-least-once/at-most-once/exactly-once） | 消息投递语义、可靠性保证 | 消息队列理论笔记 |
| D110 | 周五 | 2h | Phase 5 | RabbitMQ 基础（Exchange/Queue/Binding/DLQ） | RabbitMQ 核心概念 | RabbitMQ 操作笔记 |
| D111 | 周六 | 8h | Phase 5 | 实战：Agent 长任务 Celery 异步化（提交→进度→结果） | 长任务异步化、进度追踪 | Agent 异步任务系统 |
| D112 | 周日 | 8h | Phase 5 | 实战：事件驱动文档摄入（RabbitMQ/Kafka 二选一） | 事件驱动摄入管道 | 事件驱动摄入系统 |
| D113 | 周一 | 2h | Phase 5 | Nginx 基础（反向代理/静态文件/SSL） | Nginx 配置、反向代理 | Nginx 配置示例 |
| D114 | 周二 | 2h | Phase 5 | Nginx 负载均衡（Round-robin/Least-conn/健康检查） | 负载均衡策略、健康检查 | 负载均衡配置 |
| D115 | 周三 | 2h | Phase 5 | 多实例部署（Docker Compose + Nginx LB） | 多实例容器部署 | 多实例部署方案 |
| D116 | 周四 | 2h | Phase 5 | Agent 可观测性（LangSmith Tracing/Token 追踪/决策日志） | Agent 执行追踪、成本监控 | 可观测性方案 |
| D117 | 周五 | 2h | Phase 5 | Agent 生产化（成本控制/超时/安全栏杆） | Agent 生产化最佳实践 | Agent 生产化清单 |
| D118 | 周六 | 8h | Phase 5 | **Buffer 4**：复盘 Phase 5 + Agent 系统验收 | 复盘 Agent 技术、系统验收 | Phase 5 复盘报告 |
| D119 | 周日 | 8h | Phase 5 | **Buffer 4**：Celery + Nginx 全链路验收 | 验收异步任务、负载均衡 | 全链路验收报告 |

---

## Phase 6：性能与可观测性（W18-W20，D120-D140）

| 天 | 日期标记 | 时长 | Phase | 主题 | 核心任务 | 当日产出 |
|:---|:--------|:-----|:------|:-----|:--------|:--------|
| D120 | 周一 | 2h | Phase 6 | asyncio 深入（gather/Semaphore/并发限制） | 并发模式、信号量限流 | asyncio 进阶示例 |
| D121 | 周二 | 2h | Phase 6 | GIL + threading + multiprocessing（适用场景） | GIL 原理、线程/进程选型 | 并发模型笔记 |
| D122 | 周三 | 2h | Phase 6 | 连接池（httpx/SQLAlchemy/Redis 连接复用） | 连接池配置与优化 | 连接池配置方案 |
| D123 | 周四 | 2h | Phase 6 | 并发问题（竞态条件/死锁/资源泄漏） | 并发问题诊断与解决 | 并发问题案例集 |
| D124 | 周五 | 2h | Phase 6 | 批量处理加速（并发解析/批量 Embedding/批量写入） | 批量化处理优化 | 批量处理方案 |
| D125 | 周六 | 8h | Phase 6 | 实战：RAG 文档摄入并发优化（3 倍加速目标） | 并发优化摄入管道 | 优化后摄入管道 + 性能数据 |
| D126 | 周日 | 8h | Phase 6 | 实战：压力测试（locust/k6）+ 性能基准报告 | 压力测试、性能基线建立 | 压力测试报告 |
| D127 | 周一 | 2h | Phase 6 | PostgreSQL 高级（窗口函数/CTE/JSONB/全文搜索） | PG 高级特性 | PG 高级查询示例 |
| D128 | 周二 | 2h | Phase 6 | PG 性能优化（查询优化/索引策略/EXPLAIN 深入） | 查询优化、索引调优 | PG 优化方案 |
| D129 | 周三 | 2h | Phase 6 | pgvector（PG 作为向量库/嵌入存储/混合 SQL+向量查询） | pgvector 安装与使用 | pgvector 示例 |
| D130 | 周四 | 2h | Phase 6 | PG 复制（流复制/逻辑复制/读副本） | 数据库复制策略 | PG 复制配置 |
| D131 | 周五 | 2h | Phase 6 | Prometheus 基础（指标类型/PromQL/采集配置） | Prometheus 监控基础 | Prometheus 配置 |
| D132 | 周六 | 8h | Phase 6 | 实战：Prometheus + Grafana 部署 + AI 专属仪表盘 | 部署监控栈、构建 AI 仪表盘（token 成本/延迟 P95/缓存命中率） | 监控仪表盘 |
| D133 | 周日 | 8h | Phase 6 | 实战：pgvector 迁移（从 ChromaDB 迁移/性能对比） | 向量库迁移、性能对比 | pgvector 迁移方案 + 对比报告 |
| D134 | 周一 | 2h | Phase 6 | 进阶 Agent 模式（任务规划/自主 Agent/迭代改进） | 高级 Agent 模式 | 进阶 Agent 模式笔记 |
| D135 | 周二 | 2h | Phase 6 | RAG + Agent 融合（知识库优先→搜索降级/置信度路由） | RAG 与 Agent 协同策略 | RAG+Agent 融合方案 |
| D136 | 周三 | 2h | Phase 6 | 链路追踪（OpenTelemetry/Jaeger/Trace 上下文传播） | 分布式链路追踪 | OTel 配置示例 |
| D137 | 周四 | 2h | Phase 6 | 告警（SLO/SLI 定义/Slack 集成/告警规则） | 告警体系设计 | 告警规则配置 |
| D138 | 周五 | 2h | Phase 6 | 日志聚合（ELK/Loki 概览/结构化日志关联） | 日志聚合方案 | 日志聚合方案文档 |
| D139 | 周六 | 8h | Phase 6 | **Buffer 5**：复盘 Phase 6 + 性能优化验收 | 复盘性能优化、验收成果 | Phase 6 复盘报告 |
| D140 | 周日 | 8h | Phase 6 | **Buffer 5**：监控全栈验收（Prometheus+Grafana+OTel） | 验收监控全栈 | 监控验收报告 |

---

## Phase 7：分布式与系统设计（W21-W22，D141-D154）

| 天 | 日期标记 | 时长 | Phase | 主题 | 核心任务 | 当日产出 |
|:---|:--------|:-----|:------|:-----|:--------|:--------|
| D141 | 周一 | 2h | Phase 7 | CAP 定理 + BASE vs ACID + 一致性模型 | 分布式理论基础 | 分布式理论笔记 |
| D142 | 周二 | 2h | Phase 7 | 无状态服务改造（会话存 Redis/文件存对象存储） | 无状态化改造方案 | 无状态改造方案 |
| D143 | 周三 | 2h | Phase 7 | 分布式锁（Redis SETNX/Lua 原子性/Redlock 概念） | 分布式锁实现 | 分布式锁示例 |
| D144 | 周四 | 2h | Phase 7 | Redis 集群搭建（3 主 3 从/分片/故障转移） | Redis 集群部署 | Redis 集群配置 |
| D145 | 周五 | 2h | Phase 7 | 分布式限流（令牌桶/滑动窗口/Redis 实现） | 分布式限流算法与实现 | 分布式限流方案 |
| D146 | 周六 | 8h | Phase 7 | 实战：Redis 集群 + 分布式锁 + 语义缓存升级 | 集群部署、锁实现、缓存升级 | Redis 集群系统 |
| D147 | 周日 | 8h | Phase 7 | 实战：无状态服务改造 + 分布式限流 | 服务无状态化、限流集成 | 无状态服务 + 限流系统 |
| D148 | 周一 | 2h | Phase 7 | K8s 概念（Pod/Deployment/Service/Ingress/ConfigMap） | Kubernetes 核心概念 | K8s 概念笔记 |
| D149 | 周二 | 2h | Phase 7 | K8s AI 工作负载（GPU 调度/资源限制/HPA） | AI 场景 K8s 配置 | K8s AI 配置示例 |
| D150 | 周三 | 2h | Phase 7 | Helm Charts（打包/模板/Release 管理） | Helm 包管理 | Helm Chart 示例 |
| D151 | 周四 | 2h | Phase 7 | 系统设计框架（需求→估算→API→Schema→架构） | 系统设计方法论 | 系统设计框架文档 |
| D152 | 周五 | 2h | Phase 7 | 系统设计实战：10 万用户 RAG 系统 | 设计高并发 RAG 系统 | RAG 系统设计文档 |
| D153 | 周六 | 8h | Phase 7 | **Buffer 6**：复盘 Phase 7 + K8s 部署验收 | 复盘分布式技术、K8s 验收 | Phase 7 复盘报告 |
| D154 | 周日 | 8h | Phase 7 | **Buffer 6**：系统设计练习 + 架构图整理 | 系统设计练习、架构图 | 系统设计练习 + 架构图集 |

---

## Phase 8：综合项目与求职冲刺（W23-W28，D155-D196）

| 天 | 日期标记 | 时长 | Phase | 主题 | 核心任务 | 当日产出 |
|:---|:--------|:-----|:------|:-----|:--------|:--------|
| D155 | 周一 | 2h | Phase 8 | 综合项目：架构设计 + API 规格 + DB Schema | 项目架构设计、接口规格定义 | 架构设计文档 + API 规格 |
| D156 | 周二 | 2h | Phase 8 | 综合项目：项目初始化 + CI/CD + Docker Compose | 项目骨架搭建、自动化配置 | 项目骨架 + CI/CD 配置 |
| D157 | 周三 | 2h | Phase 8 | 综合项目：RAG Pipeline（代码嵌入/仓库摄入） | 代码仓库级 RAG 管道 | 代码 RAG Pipeline |
| D158 | 周四 | 2h | Phase 8 | 综合项目：Agent 设计（角色定义/状态图/工具规格） | Agent 角色与工具设计 | Agent 设计文档 |
| D159 | 周五 | 2h | Phase 8 | 综合项目：PostgreSQL Schema + pgvector | 数据库 Schema 实现 | DB Schema + pgvector 配置 |
| D160 | 周六 | 8h | Phase 8 | 实战：综合项目核心 RAG + Agent 实现 | 核心功能编码 | RAG + Agent 核心代码 |
| D161 | 周日 | 8h | Phase 8 | 实战：综合项目 Agent 系统集成测试 | 集成测试 Agent 系统 | Agent 集成测试套件 |
| D162 | 周一 | 2h | Phase 8 | 综合项目：FastAPI REST + WebSocket 流式 | REST API + WebSocket 实现 | API 层代码 |
| D163 | 周二 | 2h | Phase 8 | 综合项目：Celery 异步处理 + 进度通知 | 异步任务集成 | Celery 任务配置 |
| D164 | 周三 | 2h | Phase 8 | 综合项目：Redis 缓存 + 会话管理 | 缓存层集成 | Redis 集成代码 |
| D165 | 周四 | 2h | Phase 8 | 综合项目：MCP Server（Git 操作/文件访问） | MCP Server 开发 | MCP Server 实现 |
| D166 | 周五 | 2h | Phase 8 | 综合项目：集成测试 E2E | 端到端测试 | E2E 测试套件 |
| D167 | 周六 | 8h | Phase 8 | 实战：综合项目后端全栈集成 | 全栈集成联调 | 后端全栈集成版本 |
| D168 | 周日 | 8h | Phase 8 | 实战：综合项目性能优化 + 负载测试 | 性能优化、压测 | 性能优化报告 |
| D169 | 周一 | 2h | Phase 8 | 综合项目：Prometheus + Grafana 监控 | 监控配置 | 监控仪表盘配置 |
| D170 | 周二 | 2h | Phase 8 | 综合项目：Nginx 负载均衡配置 | 负载均衡部署 | Nginx 配置 |
| D171 | 周三 | 2h | Phase 8 | 综合项目：Docker Compose 全服务部署 | 全服务容器化部署 | Docker Compose 全栈配置 |
| D172 | 周四 | 2h | Phase 8 | 综合项目：README + API 文档 + 架构决策记录 | 文档撰写 | 项目文档集 |
| D173 | 周五 | 2h | Phase 8 | 综合项目：K8s 部署（Helm + HPA） | K8s 部署配置 | Helm Chart + HPA 配置 |
| D174 | 周六 | 8h | Phase 8 | 实战：综合项目部署验证 + 故障转移测试 | 部署验证、容灾测试 | 部署验证报告 |
| D175 | 周日 | 8h | Phase 8 | 实战：综合项目 Demo 准备 + 边界处理 | Demo 准备、边界用例处理 | Demo 版本 + 边界用例文档 |
| D176 | 周一 | 2h | Phase 8 | 系统设计面试框架（需求/估算/API/Schema/架构） | 面试框架方法论 | 系统设计面试笔记 |
| D177 | 周二 | 2h | Phase 8 | 设计题：实时 AI 聊天系统 | 设计实时聊天系统 | 聊天系统设计文档 |
| D178 | 周三 | 2h | Phase 8 | 设计题：百万文档搜索引擎 | 设计大规模搜索引擎 | 搜索引擎设计文档 |
| D179 | 周四 | 2h | Phase 8 | 设计题：多租户 AI SaaS 平台 | 设计多租户 SaaS | SaaS 平台设计文档 |
| D180 | 周五 | 2h | Phase 8 | 设计题：GitHub Code Review Bot | 设计代码审查 Bot | Code Review Bot 设计 |
| D181 | 周六 | 8h | Phase 8 | 模拟面试：系统设计 | 全天系统设计模拟 | 模拟面试记录 |
| D182 | 周日 | 8h | Phase 8 | 模拟面试：架构方案讲解 | 全天架构讲解练习 | 架构讲解记录 |
| D183 | 周一 | 2h | Phase 8 | AI 面试题：RAG 架构/Embedding/Prompt 工程 | AI 相关面试题练习 | AI 面试题答案集 |
| D184 | 周二 | 2h | Phase 8 | AI 面试题：Agent 架构/LangGraph/MCP/评估 | Agent 相关面试题练习 | Agent 面试题答案集 |
| D185 | 周三 | 2h | Phase 8 | 后端面试题：Redis/消息队列/数据库优化 | 后端技术面试题 | 后端面试题答案集 |
| D186 | 周四 | 2h | Phase 8 | 后端面试题：分布式/CAP/一致性 | 分布式面试题 | 分布式面试题答案集 |
| D187 | 周五 | 2h | Phase 8 | 行为面试：STAR 故事（项目经验） | 行为面试准备 | STAR 故事集 |
| D188 | 周六 | 8h | Phase 8 | 全天模拟面试（2 系统设计 + 1 编程 + 1 行为） | 全天模拟面试 | 模拟面试记录 + 评分 |
| D189 | 周日 | 8h | Phase 8 | 复盘模拟面试 + 补短板 | 模拟面试复盘 | 复盘报告 + 补强计划 |
| D190 | 周一 | 2h | Phase 8 | 作品集定稿（GitHub 仓库/README 美化/部署链接） | 作品集整理 | GitHub 作品集 |
| D191 | 周二 | 2h | Phase 8 | 简历更新（技术栈/项目描述/量化成果） | 简历更新 | 更新后简历 |
| D192 | 周三 | 2h | Phase 8 | 知识图谱（个人参考手册） | 知识体系整理 | 个人知识图谱 |
| D193 | 周四 | 2h | Phase 8 | 薄弱点复习 | 查缺补漏 | 薄弱点复习笔记 |
| D194 | 周五 | 2h | Phase 8 | 学习计划复盘（成功/失败/未来方向） | 全计划复盘 | 学习计划复盘报告 |
| D195 | 周六 | 8h | Phase 8 | **Buffer 7**：最终复盘 + 查缺补漏 | 最终查缺补漏 | 最终复盘报告 |
| D196 | 周日 | 8h | Phase 8 | **Buffer 7**：作品集定稿 + 未来规划 | 作品集定稿、未来路线规划 | 最终作品集 + 未来规划文档 |

---

## 里程碑时间线

```
W01        W04        W09        W12        W17        W20        W22        W28
 |          |          |          |          |          |          |          |
 D1----D7   D8---D28   D29--D63   D64--D84   D85-D119   D120-D140  D141-D154  D155----D196
 |          |          |          |          |          |          |          |
 Phase 1    Phase 2    Phase 3    Phase 4    Phase 5    Phase 6    Phase 7    Phase 8
 Python     LLM API    RAG 核心    工程化      Agent      性能        分布式      综合项目
 现代化      Prompt     技术        部署        异步架构    可观测性    系统设计    求职冲刺
 |          |          |          |          |          |          |          |
 26h        78h        130h       78h        130h       78h        52h        156h
 |          |          |          |          |          |          |          |
[M1]       [M2]       [M3]       [M4]       [M5]       [M6]       [M7]       [M8]
异步CLI     多厂商LLM   RAG API    容器化      Agent      监控全栈    K8s部署     作品集
+测试       客户端      +Redis     CI/CD      系统       Prometheus  系统设计    求职就绪
```

| 里程碑 | 截止日 | 验收标准 |
|:------|:------|:--------|
| M1 | D7（04-12 周日） | 异步 CLI 工具 + 测试覆盖率 >80% |
| M2 | D28（05-03 周日） | 多厂商 LLM 客户端 + MCP Server 基础 |
| M3 | D63（06-07 周日） | 完整 RAG API + Redis 缓存 + 混合检索 |
| M4 | D84（06-28 周日） | 容器化部署 + CI/CD + JWT 认证 |
| M5 | D119（08-02 周日） | Agent 系统 + Celery 异步 + Nginx 负载均衡 |
| M6 | D140（08-23 周日） | 性能优化 + Prometheus/Grafana + pgvector |
| M7 | D154（09-06 周日） | K8s 部署 + 系统设计练习 |
| M8 | D196（10-18 周日） | 综合项目完成 + 作品集定稿 + 求职就绪 |

---

## 每周复盘问题

每周日晚完成以下复盘（建议用 15-30 分钟）：

1. **完成度**：本周计划的 7 天任务，完成了几天？未完成的原因是什么？
2. **难点回顾**：本周遇到的最大困难是什么？如何解决的（或需要下周补强）？
3. **知识掌握**：能否用一句话向别人解释本周学到的每个核心概念？
4. **代码产出**：本周写了多少行有效代码？有没有可复用的模块？
5. **时间管理**：工作日 2h 是否被有效利用？周末 8h 是否出现明显疲劳或分心？
6. **下周预告**：下周的主题是什么？需要提前准备什么环境/工具/资料？
7. **Buffer 使用**（仅 Buffer 周）：Buffer 时间是否被用于复盘和补强？还是浪费了？
