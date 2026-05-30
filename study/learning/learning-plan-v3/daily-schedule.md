# 每日学习计划总览（日历速查表）

> 工作日 2h · 周末 8h · 共 38 周 · 266 天 · 988 小时
> **起止日期**：2026-06-01（周一）至 2027-02-21（周日）

## 两阶段与求职门槛

```
══ Stage A：先具备 AI 应用开发能力 ════════════►│门槛│══ Stage B：边投边学 ═══════════►
P1   P2    P3    P4         P5            │D147│  P6      P7      P8      P9
                  ↑软启动(D105)            │可投│
                  RAG 全栈应用上线           │简历│       ★求职正式启动，P6 起边投边学
```

- **软启动**：P4 末（D105 / 2026-09-13 / 约 3.5 月）——首个 RAG 全栈应用上线，开始零星投递、积累面试反馈
- **正式门槛**：P5 末（D147 / 2026-10-25 / 约 5.5 月）——Agent 就绪，转全力求职，Stage B（P6-P9）边投边学

**日编号权威映射**（各 Phase 起始日均为周一）：
- Phase 1: W1-2 (D1-D14) — D14 Buffer 1
- Phase 2: W3-5 (D15-D35) — D34-35 Buffer 2
- Phase 3: W6-9 (D36-D63) — D62-63 Buffer 3
- Phase 4: W10-15 (D64-D105) — D104-105 Buffer 4　★软启动门槛
- Phase 5: W16-21 (D106-D147) — D146-147 Buffer 5　★正式可投简历门槛
- Phase 6: W22-25 (D148-D175) — D174-175 Buffer 6
- Phase 7: W26-29 (D176-D203) — D202-203 Buffer 7
- Phase 8: W30-32 (D204-D224) — D224 Buffer 8
- Phase 9: W33-38 (D225-D266) — D265-266 Buffer 9

> **附录（后续学习，不计入 988h）**：推理加速（vLLM/TGI/显存量化）、Go 后端（可选第二语言）——见 `appendix-后续学习.md`。
> **周末判定**：每周第 6 天（周六）、第 7 天（周日）为 8h 实战/缓冲日。

---

## Phase 1：双地基 — Python 现代化 + TS/React 启蒙（W1-2，D1-D14）

| 天 | 周 | 时长 | 主题 | 当日产出 |
|:--|:--|:--|:--|:--|
| D1 | 一 | 2h | 类型注解 + Pydantic + f-string | 类型注解示例 + Pydantic 模型 |
| D2 | 二 | 2h | async/await + 装饰器 + 对比 Node.js | 异步函数 + 装饰器示例 |
| D3 | 三 | 2h | 生成器 + 上下文管理器 + httpx | 生成器 + httpx 封装 |
| D4 | 四 | 2h | pytest 深入（fixtures/parametrize/mock） | 完整测试套件示例 |
| D5 | 五 | 2h | 包管理（pyproject/venv/uv）+ 项目结构 | pyproject.toml + 工程结构 |
| D6 | 六 | 8h | 实战：异步 CLI 工具（Click + asyncio） | 完整异步 CLI 项目 |
| D7 | 日 | 8h | 实战：完整测试套件 + 工程化收尾 | 覆盖率 >80% 测试套件 |
| D8 | 一 | 2h | TypeScript 类型系统（类型/接口/泛型/工具类型） | TS 类型示例 |
| D9 | 二 | 2h | TS 进阶（联合/交叉/类型守卫）+ 对比 Vue/JS | TS 进阶示例 + 对比笔记 |
| D10 | 三 | 2h | React 核心（组件/JSX/props/state/事件）对比 Vue | React 基础组件 |
| D11 | 四 | 2h | React Hooks（useState/useEffect/useRef/useMemo） | Hooks 示例集 |
| D12 | 五 | 2h | React 进阶（Context/自定义 Hook/受控组件） | 自定义 Hook + Context 示例 |
| D13 | 六 | 8h | 实战：React + TS 笔记/待办 SPA | 完整 React SPA |
| D14 | 日 | 8h | **Buffer 1**：Zustand 状态管理 + API 请求 + 双栈验收 | 双栈地基验收报告 |

> **本阶段作品**：异步 CLI 工具 + React/TS SPA（地基练手，入 GitHub）

---

## Phase 2：LLM API + Prompt 精通 + Function Calling（W3-5，D15-D35）

| 天 | 周 | 时长 | 主题 | 当日产出 |
|:--|:--|:--|:--|:--|
| D15 | 一 | 2h | Claude API 基础（Messages/system/streaming） | Claude API 调用示例 |
| D16 | 二 | 2h | Claude 结构化输出（tool_use/JSON）+ Function Calling 原理 | 结构化输出示例 |
| D17 | 三 | 2h | Claude Prompt Caching + 成本/Token 优化 | 缓存策略 + 成本分析 |
| D18 | 四 | 2h | OpenAI API（chat/function calling）+ 对比 | OpenAI 示例 + 对比表 |
| D19 | 五 | 2h | 国产模型（智谱 GLM-4/DeepSeek/通义）+ 免费额度 | 国产模型调用示例 |
| D20 | 六 | 8h | 实战：多厂商 LLM 统一客户端抽象层 | 多厂商 LLM 客户端库 |
| D21 | 日 | 8h | 实战：Provider 切换配置 + 流式/重试/降级 | 配置化 LLM 客户端 |
| D22 | 一 | 2h | Prompt 基础（Role/Few-shot/CoT/格式/分隔符） | Prompt 模板库 |
| D23 | 二 | 2h | Prompt 进阶（Self-consistency/ToT/Prompt 链/元提示） | 进阶 Prompt 示例 |
| D24 | 三 | 2h | 上下文窗口管理（长文本/截断/压缩/滑动窗口） | 上下文管理方案 |
| D25 | 四 | 2h | 幻觉治理（基于资料回答/引用/置信度/自检） | 幻觉控制 Prompt 模板 |
| D26 | 五 | 2h | Prompt 测试与评估（A/B/指标/回归集） | Prompt 评估框架 |
| D27 | 六 | 8h | 实战：Prompt 工作台（测试/对比/版本/评估） | Prompt 工作台工具 |
| D28 | 日 | 8h | 实战：用 Prompt 解决一段复杂业务规则 | 业务 Prompt 案例 |
| D29 | 一 | 2h | Function Calling 深入（并行调用/工具选择/参数校验） | Function Calling 示例 |
| D30 | 二 | 2h | 多模态输入（Vision/图像理解/OCR） | Vision 调用示例 |
| D31 | 三 | 2h | Token 经济学（计数/成本/限流/批处理） | 成本计算器 + 限流方案 |
| D32 | 四 | 2h | LLM 安全（提示注入/内容过滤/越狱防御） | 安全检查清单 |
| D33 | 五 | 2h | API 最佳实践（重试/退避/熔断/超时/幂等） | API 最佳实践文档 |
| D34 | 六 | 8h | **Buffer 2**：复盘 P1-2 + 补短板 | 复盘报告 |
| D35 | 日 | 8h | **Buffer 2**：LLM 客户端 + Prompt 库验收 | M2 验收报告 |

> **本阶段作品**：多厂商 LLM 客户端库 + Prompt 工作台（开源，入作品集）

---

## Phase 3：AI 对话前端 — React + Next.js（W6-9，D36-D63）

| 天 | 周 | 时长 | 主题 | 当日产出 |
|:--|:--|:--|:--|:--|
| D36 | 一 | 2h | Next.js App Router（路由/布局/RSC） | Next.js 路由示例 |
| D37 | 二 | 2h | Next.js 数据获取（Server Actions/fetch/缓存） | 数据获取示例 |
| D38 | 三 | 2h | Tailwind CSS + shadcn/ui 组件库 | UI 组件示例 |
| D39 | 四 | 2h | Next.js API Routes + 中间件 + 环境变量 | API Route 示例 |
| D40 | 五 | 2h | 流式 UI 基础（SSE/ReadableStream/Suspense） | 流式 UI 示例 |
| D41 | 六 | 8h | 实战：Next.js 应用骨架（布局/导航/主题） | 应用骨架 |
| D42 | 日 | 8h | 实战：接入 LLM 后端的对话页（非流式） | 基础对话页 |
| D43 | 一 | 2h | Vercel AI SDK（useChat/useCompletion/streamText） | AI SDK 示例 |
| D44 | 二 | 2h | 流式渲染（逐字输出/Markdown/代码高亮） | 流式渲染组件 |
| D45 | 三 | 2h | 对话状态管理（消息列表/多会话/Zustand） | 对话状态管理 |
| D46 | 四 | 2h | 交互细节（停止/重新生成/编辑/复制/滚动跟随） | 交互组件集 |
| D47 | 五 | 2h | 引用与来源展示（citations UI/折叠/高亮） | 引用展示组件 |
| D48 | 六 | 8h | 实战：完整 AI 对话界面（流式+Markdown+多会话） | 完整对话界面 |
| D49 | 日 | 8h | 实战：对话历史持久化 + 体验打磨 | 持久化对话应用 |
| D50 | 一 | 2h | 后台管理 UI（布局/表格/表单/CRUD 模式） | 后台 UI 骨架 |
| D51 | 二 | 2h | 表单工程（react-hook-form + zod 校验） | 表单 + 校验示例 |
| D52 | 三 | 2h | 智能体配置界面（模型/温度/系统提示/工具开关） | 配置表单组件 |
| D53 | 四 | 2h | WebSocket 前端（原生 WS/重连/心跳）vs SSE 选型 | WS 客户端封装 |
| D54 | 五 | 2h | 文件上传 UI（拖拽/进度/多文件/预览） | 上传组件 |
| D55 | 六 | 8h | 实战：智能体配置后台（列表+创建+编辑+测试） | 配置后台 |
| D56 | 日 | 8h | 实战：文档上传界面 + 进度（对接后端） | 上传界面 |
| D57 | 一 | 2h | 数据获取缓存（TanStack Query/SWR） | 数据层封装 |
| D58 | 二 | 2h | 前端性能（代码分割/懒加载/虚拟列表/防抖节流） | 性能优化清单 |
| D59 | 三 | 2h | 前端测试（Vitest/RTL/Playwright） | 前端测试套件 |
| D60 | 四 | 2h | 前端部署（Vercel/静态导出/Docker 化 Next.js） | 部署配置 |
| D61 | 五 | 2h | 响应式与可访问性（移动端适配/a11y） | 响应式样式 |
| D62 | 六 | 8h | **Buffer 3**：复盘 P3 + 前端验收 | P3 复盘报告 |
| D63 | 日 | 8h | **Buffer 3**：Chatbot 前端端到端验收（对接 P2） | M3 验收报告 |

> **本阶段作品**：★ Chatbot Web 应用上线（Next.js 流式对话 + 配置后台 + 上传界面）

---

## Phase 4：RAG + 后端服务化（W10-15，D64-D105）　★软启动门槛

| 天 | 周 | 时长 | 主题 | 当日产出 |
|:--|:--|:--|:--|:--|
| D64 | 一 | 2h | Embedding 原理（向量空间/余弦/维度/bge-m3） | Embedding 笔记 |
| D65 | 二 | 2h | sentence-transformers + 嵌入模型选型（多语言） | 嵌入模型示例 |
| D66 | 三 | 2h | 裸写向量搜索（numpy 余弦相似度） | 手写向量搜索 |
| D67 | 四 | 2h | ChromaDB 基础（集合/元数据/持久化） | ChromaDB 示例 |
| D68 | 五 | 2h | 向量库全景（Chroma/FAISS/Milvus/Pinecone/PGVector） | 向量库对比表 |
| D69 | 六 | 8h | 实战：裸写完整 RAG Pipeline | 完整 RAG Pipeline |
| D70 | 日 | 8h | 实战：多格式文档解析（PDF/Word/MD/TXT/Excel/CSV） | 多格式解析库 |
| D71 | 一 | 2h | 分块策略（固定/递归/语义/按结构） | 分块策略对比 |
| D72 | 二 | 2h | 分块优化（overlap/元数据/父子文档） | 优化分块实现 |
| D73 | 三 | 2h | BM25 + 混合检索原理 | BM25 + 混合检索示例 |
| D74 | 四 | 2h | Rerank 重排序（CrossEncoder/LLM-based） | Rerank 实现 |
| D75 | 五 | 2h | 查询增强（HyDE/多查询/查询改写） | 查询增强示例 |
| D76 | 六 | 8h | 实战：混合检索 + Rerank 集成 | 混合检索系统 |
| D77 | 日 | 8h | 实战：HyDE + 检索质量评测（precision/recall） | HyDE + 评测报告 |
| D78 | 一 | 2h | LangChain 核心（Chain/Prompt/OutputParser/Memory） | LangChain 示例 |
| D79 | 二 | 2h | LangChain 文档处理（Loader/Splitter/Embedding） | 文档处理示例 |
| D80 | 三 | 2h | LangChain 向量库 + 检索器 + LCEL | LCEL 管道示例 |
| D81 | 四 | 2h | LlamaIndex 概览 + 框架选型 | 框架对比文档 |
| D82 | 五 | 2h | Dify 平台（可视化编排/知识库/工作流） | Dify 知识库 demo |
| D83 | 六 | 8h | 实战：LangChain 重写 RAG（对比裸写） | LangChain RAG + 对比 |
| D84 | 日 | 8h | 实战：带记忆的对话式 RAG | 对话式 RAG |
| D85 | 一 | 2h | FastAPI 基础（路由/Pydantic/依赖注入） | FastAPI 基础示例 |
| D86 | 二 | 2h | FastAPI 异步 + SSE 流式响应 | 流式响应示例 |
| D87 | 三 | 2h | Redis 基础（数据结构/CLI） | Redis 操作笔记 |
| D88 | 四 | 2h | Redis 缓存（LLM 响应/Embedding/语义缓存） | Redis 缓存方案 |
| D89 | 五 | 2h | Redis 限流 + 缓存三大问题（穿透/击穿/雪崩） | 限流 + 缓存文档 |
| D90 | 六 | 8h | 实战：RAG API 服务化（FastAPI + Redis 缓存） | RAG API 服务 |
| D91 | 日 | 8h | 实战：前端对接 RAG API（流式问答 + 引用展示） | 前后端联调版本 |
| D92 | 一 | 2h | PGVector（向量扩展/HNSW/IVFFlat 索引） | PGVector 示例 |
| D93 | 二 | 2h | Milvus 架构（Collection/Partition/索引/标量过滤） | Milvus 架构笔记 |
| D94 | 三 | 2h | Milvus 实战（部署/插入/检索/混合过滤） | Milvus 操作示例 |
| D95 | 四 | 2h | 向量库选型与迁移（Chroma→PGVector/Milvus） | 迁移方案 |
| D96 | 五 | 2h | 元数据过滤 + 多租户隔离设计 | 多租户隔离方案 |
| D97 | 六 | 8h | 实战：PGVector 重构 RAG 存储 + 性能对比 | PGVector 迁移 + 对比 |
| D98 | 日 | 8h | 实战：Milvus 大规模向量检索 + 标量过滤 | Milvus 检索系统 |
| D99 | 一 | 2h | 进阶 RAG 模式（CRAG/Self-RAG/Adaptive RAG） | 进阶 RAG 笔记 |
| D100 | 二 | 2h | 多模态 RAG（图片/表格/代码） | 多模态 RAG 示例 |
| D101 | 三 | 2h | RAGAs 评估（faithfulness/relevancy/precision/recall） | RAG 评估方案 |
| D102 | 四 | 2h | 生产 RAG（增量索引/文档版本/可扩展性） | 生产 RAG 架构 |
| D103 | 五 | 2h | RAG 质量调优实战（诊断→优化→再评估） | RAG 调优报告 |
| D104 | 六 | 8h | **Buffer 4**：复盘 P4 + RAG 全栈验收 | P4 复盘报告 |
| D105 | 日 | 8h | **Buffer 4**：RAG 前后端端到端验收 + 上线 | M4 验收 + 首个 AI 应用上线 |

> **本阶段作品**：★★ RAG 知识库问答（全栈上线）——**首个完整 AI 应用，可开始零星投递简历**

---

## Phase 5：Agent 核心链路（W16-21，D106-D147）　★正式可投简历门槛

| 天 | 周 | 时长 | 主题 | 当日产出 |
|:--|:--|:--|:--|:--|
| D106 | 一 | 2h | Agent 范式（ReAct/CoT/Plan-and-Execute/Tool-Use/Autonomous） | Agent 范式笔记 |
| D107 | 二 | 2h | LangGraph 基础（StateGraph/节点/边/条件路由） | LangGraph 示例 |
| D108 | 三 | 2h | LangGraph 状态管理（TypedDict/Reducer/Checkpointer） | 状态管理示例 |
| D109 | 四 | 2h | Tool-Use Agent（工具定义/Schema/执行循环） | Tool-Use Agent |
| D110 | 五 | 2h | Human-in-the-loop（中断/审批/interrupt_before） | HITL Agent |
| D111 | 六 | 8h | 实战：LangGraph ReAct Agent（搜索+计算+文件） | ReAct Agent 项目 |
| D112 | 日 | 8h | 实战：带审批流的 Agent | 审批流 Agent |
| D113 | 一 | 2h | 任务规划 Planning（任务分解/计划生成/重规划） | Planning 示例 |
| D114 | 二 | 2h | 记忆管理（短期/长期/情景 + 向量存储） | 记忆系统设计 |
| D115 | 三 | 2h | 记忆工程（摘要/压缩/遗忘/记忆检索） | 记忆压缩实现 |
| D116 | 四 | 2h | 工具设计模式（幂等/错误处理/超时/安全边界） | 工具设计文档 |
| D117 | 五 | 2h | Function Calling 工程化（工具路由/并行/结果回填） | 工具路由实现 |
| D118 | 六 | 8h | 实战：带规划 + 记忆的 Agent（多步任务） | 规划记忆 Agent |
| D119 | 日 | 8h | 实战：长期记忆 Agent（跨会话 + 个性化） | 长期记忆 Agent |
| D120 | 一 | 2h | MCP 架构深入（传输层/协议/生命周期） | MCP 架构笔记 |
| D121 | 二 | 2h | MCP Server 开发（Python mcp SDK/FastMCP） | MCP Server 示例 |
| D122 | 三 | 2h | MCP 三种能力（Tools/Resources/Prompts） | MCP 能力示例 |
| D123 | 四 | 2h | MCP 客户端集成（LangGraph 连接 MCP） | MCP 集成示例 |
| D124 | 五 | 2h | MCP 实战工具（DB/文件/Web 搜索） | MCP 工具集 |
| D125 | 六 | 8h | 实战：多能力 MCP Server | 完整 MCP Server |
| D126 | 日 | 8h | 实战：MCP 驱动的 Agent 助手 | MCP Agent 助手 |
| D127 | 一 | 2h | 多智能体模式（Supervisor/层级/对等/Swarm） | 多智能体模式笔记 |
| D128 | 二 | 2h | LangGraph 多智能体（子图/Handoff/共享状态） | 多 Agent LangGraph |
| D129 | 三 | 2h | Agent 通信（消息传递/共享状态/黑板） | 通信对比文档 |
| D130 | 四 | 2h | AutoGen 框架（ConversableAgent/GroupChat） | AutoGen 示例 |
| D131 | 五 | 2h | 框架对比（LangGraph/AutoGen/CrewAI/Dify） | 框架选型表 |
| D132 | 六 | 8h | 实战：Supervisor 多智能体协作系统 | 多智能体系统 |
| D133 | 日 | 8h | 实战：AutoGen GroupChat + 对比 LangGraph | AutoGen 系统 + 对比 |
| D134 | 一 | 2h | Agent 评估（完成率/工具效率/多轮一致性） | Agent 评估框架 |
| D135 | 二 | 2h | Agent 可观测性（LangSmith/Token 追踪/决策日志） | 可观测性方案 |
| D136 | 三 | 2h | Agent 生产化（成本/超时/护栏/最大迭代） | 生产化清单 |
| D137 | 四 | 2h | Agent 配置化（可配置模型/工具/提示/记忆策略） | 配置化方案 |
| D138 | 五 | 2h | Dify 二次开发（自定义工具/工作流节点） | Dify 自定义工具 |
| D139 | 六 | 8h | 实战：智能体配置后台对接 Agent 后端（前端融合） | 配置后台全栈版 |
| D140 | 日 | 8h | 实战：Agent 评估 + LangSmith 观测全链路 | 评估 + 观测报告 |
| D141 | 一 | 2h | ReAct vs CoT vs Plan 模式选型实战 | 模式选型文档 |
| D142 | 二 | 2h | Agent + RAG 融合（知识库优先→工具降级/置信度路由） | RAG+Agent 融合方案 |
| D143 | 三 | 2h | 复杂 Agent 工作流（条件分支/循环/并行子任务） | 复杂工作流示例 |
| D144 | 四 | 2h | Agent 安全与对齐（权限/审计/越狱防护） | Agent 安全方案 |
| D145 | 五 | 2h | Agent 成本与延迟优化（缓存/小模型路由/并行） | 优化方案 |
| D146 | 六 | 8h | **Buffer 5**：复盘 P5 + Agent 系统验收 | P5 复盘报告 |
| D147 | 日 | 8h | **Buffer 5**：多智能体 + 配置后台端到端验收 + 上线 | M5 验收 + Agent 系统上线 |

> **本阶段作品**：★★ 多智能体系统 + 配置后台（上线）——**Agent 就绪，转全力求职，Stage B 边投边学**

---

## Phase 6：后端架构 + 多数据库（W22-25，D148-D175）

| 天 | 周 | 时长 | 主题 | 当日产出 |
|:--|:--|:--|:--|:--|
| D148 | 一 | 2h | FastAPI 进阶（中间件/依赖注入/后台任务/生命周期） | FastAPI 进阶示例 |
| D149 | 二 | 2h | WebSocket 后端（FastAPI WS/连接管理/广播） | WS 服务端示例 |
| D150 | 三 | 2h | 会话管理（会话存储/上下文窗口/多轮状态） | 会话管理实现 |
| D151 | 四 | 2h | Agent API 网关设计（路由/鉴权/限流/计费） | 网关设计文档 |
| D152 | 五 | 2h | Celery 异步任务（Worker/Broker/Backend/任务模式） | Celery 示例 |
| D153 | 六 | 8h | 实战：Agent API 网关（鉴权+限流+流式） | API 网关 |
| D154 | 日 | 8h | 实战：WebSocket 实时对话（会话管理+多轮） | WS 实时对话系统 |
| D155 | 一 | 2h | MySQL vs PostgreSQL 选型 + SQL 回顾 | 选型笔记 |
| D156 | 二 | 2h | SQLAlchemy ORM + Alembic 迁移 | ORM + 迁移示例 |
| D157 | 三 | 2h | 数据库设计（用户/会话/消息/智能体/文档表） | DB Schema 文档 |
| D158 | 四 | 2h | 索引与查询优化（EXPLAIN/复合索引/慢查询） | 查询优化方案 |
| D159 | 五 | 2h | 事务与并发（隔离级别/锁/乐观悲观锁） | 事务方案 |
| D160 | 六 | 8h | 实战：完整业务数据库设计 + ORM 落地 | 业务数据库 |
| D161 | 日 | 8h | 实战：会话/消息持久化 + 查询优化 | 持久化 + 优化版本 |
| D162 | 一 | 2h | MongoDB 基础（文档模型/CRUD/聚合管道） | MongoDB 示例 |
| D163 | 二 | 2h | MongoDB 建模（嵌入 vs 引用/索引/分片） | 建模方案 |
| D164 | 三 | 2h | MongoDB 在 Agent 应用（对话日志/非结构化知识） | 对话日志方案 |
| D165 | 四 | 2h | Redis 进阶（发布订阅/Stream/Lua/持久化） | Redis 进阶示例 |
| D166 | 五 | 2h | Redis 在会话与缓存应用（会话存储/分布式锁） | Redis 应用方案 |
| D167 | 六 | 8h | 实战：MongoDB 存对话日志 + 聚合分析 | MongoDB 日志系统 |
| D168 | 日 | 8h | 实战：Redis 会话 + 分布式锁 + 缓存策略 | Redis 会话系统 |
| D169 | 一 | 2h | 高并发理论（C10K/事件循环/IO 模型） | 高并发笔记 |
| D170 | 二 | 2h | 连接池与资源复用（DB/HTTP/Redis 连接池） | 连接池方案 |
| D171 | 三 | 2h | 限流与熔断（令牌桶/滑动窗口/熔断器） | 限流熔断实现 |
| D172 | 四 | 2h | 分布式锁与一致性（Redis 锁/Redlock/幂等） | 分布式锁示例 |
| D173 | 五 | 2h | 系统设计（高并发 Agent 系统架构） | 系统设计文档 |
| D174 | 六 | 8h | **Buffer 6**：复盘 P6 + 后端架构验收 | P6 复盘报告 |
| D175 | 日 | 8h | **Buffer 6**：高并发压测 + 多数据库联调验收 | M6 验收报告 |

> **本阶段作品**：高并发 Agent API 网关 + 多数据库存储层（升级主线项目后端）

---

## Phase 7：部署运维 + 可观测性（W26-29，D176-D203）

| 天 | 周 | 时长 | 主题 | 当日产出 |
|:--|:--|:--|:--|:--|
| D176 | 一 | 2h | Docker 基础（镜像/容器/卷/网络） | Docker 笔记 |
| D177 | 二 | 2h | Dockerfile（多阶段构建/缓存/体积优化） | 优化 Dockerfile |
| D178 | 三 | 2h | Docker Compose（多服务编排） | Compose 配置 |
| D179 | 四 | 2h | 容器化全栈（Next.js + FastAPI + DB） | 全栈容器配置 |
| D180 | 五 | 2h | 镜像优化与安全（非 root/扫描/最小镜像） | 镜像安全清单 |
| D181 | 六 | 8h | 实战：全栈应用容器化（前后端+DB+向量库） | 全栈容器方案 |
| D182 | 日 | 8h | 实战：Docker Compose 一键部署全栈 | 一键部署方案 |
| D183 | 一 | 2h | GitHub Actions（lint/test/build/push） | Actions 配置 |
| D184 | 二 | 2h | CI/CD 流水线（多环境/自动部署/回滚） | CI/CD 流水线 |
| D185 | 三 | 2h | 前端 CI/CD（构建/预览/Vercel） | 前端 CI/CD |
| D186 | 四 | 2h | AI 编程工具（Claude Code/Cursor 提效工作流） | 工具提效笔记 |
| D187 | 五 | 2h | 代码质量（覆盖率/lint/类型检查/pre-commit） | 质量门禁配置 |
| D188 | 六 | 8h | 实战：全栈 CI/CD 流水线（测试门禁） | 全栈 CI/CD |
| D189 | 日 | 8h | 实战：自动化部署 + 回滚演练 | 部署 + 回滚方案 |
| D190 | 一 | 2h | K8s 概念（Pod/Deployment/Service/Ingress/ConfigMap） | K8s 概念笔记 |
| D191 | 二 | 2h | K8s 实战（部署/扩缩容/滚动更新） | K8s 部署示例 |
| D192 | 三 | 2h | K8s 配置与密钥（ConfigMap/Secret） | 配置管理示例 |
| D193 | 四 | 2h | K8s 自动扩缩容（HPA/资源限制） | HPA 配置 |
| D194 | 五 | 2h | Helm Charts（打包/模板/Release） | Helm Chart |
| D195 | 六 | 8h | 实战：K8s 部署全栈 AI 应用 | K8s 部署方案 |
| D196 | 日 | 8h | 实战：HPA 扩缩容 + 滚动更新演练 | 扩缩容演练报告 |
| D197 | 一 | 2h | Prometheus（指标/PromQL/采集） | Prometheus 配置 |
| D198 | 二 | 2h | Grafana（AI 指标：token/延迟 P95/命中率） | AI 仪表盘 |
| D199 | 三 | 2h | OpenTelemetry 链路追踪（Trace/Jaeger） | OTel 配置 |
| D200 | 四 | 2h | 日志聚合（Loki/ELK/结构化日志） | 日志聚合方案 |
| D201 | 五 | 2h | SLA/SLO/告警（SLI 定义/告警/故障排查） | 告警规则配置 |
| D202 | 六 | 8h | **Buffer 7**：复盘 P7 + 云原生验收 | P7 复盘报告 |
| D203 | 日 | 8h | **Buffer 7**：监控 + 告警 + SLA 全栈验收 | M7 验收报告 |

> **本阶段作品**：主线项目云原生上线（Docker/K8s + CI/CD + 监控 + SLA）

---

## Phase 8：多模态（语音 + 图像）（W30-32，D204-D224）

| 天 | 周 | 时长 | 主题 | 当日产出 |
|:--|:--|:--|:--|:--|
| D204 | 一 | 2h | 多模态概览（模态/对齐/在 Agent 的角色） | 多模态笔记 |
| D205 | 二 | 2h | ASR 语音识别（Whisper/实时/流式） | ASR 示例 |
| D206 | 三 | 2h | TTS 语音合成（Edge-TTS/CosyVoice/流式播放） | TTS 示例 |
| D207 | 四 | 2h | 语音 Agent 链路（ASR→LLM→TTS/打断/VAD） | 语音链路设计 |
| D208 | 五 | 2h | 语音前端集成（录音/播放/实时流） | 语音前端组件 |
| D209 | 六 | 8h | 实战：语音对话 Agent（端到端） | 语音 Agent |
| D210 | 日 | 8h | 实战：语音前端 + 流式 ASR/TTS 集成 | 语音前端应用 |
| D211 | 一 | 2h | 图像生成原理（扩散模型/SD 基础） | 图像生成笔记 |
| D212 | 二 | 2h | SD 实战（文生图/图生图/ControlNet/LoRA） | SD 示例 |
| D213 | 三 | 2h | SD API/部署（ComfyUI/A1111/API 化） | SD API 服务 |
| D214 | 四 | 2h | 视觉理解（多模态 LLM/图像问答/OCR） | 视觉理解示例 |
| D215 | 五 | 2h | 多模态 Agent（图文混合/工具调用生成图像） | 多模态 Agent 设计 |
| D216 | 六 | 8h | 实战：多模态 Agent（对话中生成/理解图像） | 多模态 Agent |
| D217 | 日 | 8h | 实战：图像生成工作流集成到产品 | 图像生成集成 |
| D218 | 一 | 2h | 多模态 RAG（图文混排/表格/图表理解检索） | 多模态 RAG 示例 |
| D219 | 二 | 2h | 多模态 Agent 编排（识图/生图/语音工具路由） | 多模态编排示例 |
| D220 | 三 | 2h | 多模态评估与成本（质量/延迟/成本权衡） | 多模态评估方案 |
| D221 | 四 | 2h | 多模态产品集成（语音+图像接入主线 AI 应用） | 集成方案 |
| D222 | 五 | 2h | 多模态体验打磨（前端语音输入/图片上传/生成展示） | 前端多模态组件 |
| D223 | 六 | 8h | 实战：多模态能力接入主线产品（端到端） | 多模态产品 |
| D224 | 日 | 8h | **Buffer 8**：复盘 P8 + 多模态验收 | M8 验收报告 |

> **本阶段作品**：主线项目多模态升级（语音对话 + 图像生成插件）
> **注**：推理加速（vLLM/TGI/显存量化）已移至 `appendix-后续学习.md`，按机会择期补攻。

---

## Phase 9：综合项目 + 作品集 + 面试（W33-38，D225-D266）

| 天 | 周 | 时长 | 主题 | 当日产出 |
|:--|:--|:--|:--|:--|
| D225 | 一 | 2h | 项目 1：需求 + 全栈架构设计 | 架构设计文档 |
| D226 | 二 | 2h | 项目 1：数据库设计 + API 规格 + 项目骨架 | DB Schema + API 规格 |
| D227 | 三 | 2h | 项目 1：RAG 知识库 + 向量库 | 知识库管道 |
| D228 | 四 | 2h | 项目 1：Agent 链路（意图识别/工具/转人工） | Agent 设计 |
| D229 | 五 | 2h | 项目 1：会话管理 + WebSocket 流式 | 会话层代码 |
| D230 | 六 | 8h | 实战：项目 1 后端核心（RAG+Agent+网关） | 后端核心版本 |
| D231 | 日 | 8h | 实战：项目 1 前端（对话 + 客服后台） | 前端版本 |
| D232 | 一 | 2h | 项目 1：多轮上下文 + 记忆 | 记忆模块 |
| D233 | 二 | 2h | 项目 1：缓存 + 限流 + 降级 | 稳定性模块 |
| D234 | 三 | 2h | 项目 1：监控 + 日志 + 告警 | 可观测配置 |
| D235 | 四 | 2h | 项目 1：容器化 + CI/CD | 容器 + CI/CD |
| D236 | 五 | 2h | 项目 1：K8s 部署 + 压测 | K8s 配置 |
| D237 | 六 | 8h | 实战：项目 1 全栈集成联调 | 全栈集成版本 |
| D238 | 日 | 8h | 实战：项目 1 部署上线 + Demo 录制 | 上线版本 + Demo |
| D239 | 一 | 2h | 项目 2：选题 + 架构（AI 自动化工具/多智能体平台） | 项目 2 架构 |
| D240 | 二 | 2h | 项目 2：Agent 编排（规划 + 工具 + 多智能体） | 编排设计 |
| D241 | 三 | 2h | 项目 2：工具生态（MCP/Function Calling） | 工具集 |
| D242 | 四 | 2h | 项目 2：配置后台（可视化 Agent 配置） | 配置后台 |
| D243 | 五 | 2h | 项目 2：任务调度 + 异步执行 | 调度模块 |
| D244 | 六 | 8h | 实战：项目 2 核心 Agent 平台 | 平台核心版本 |
| D245 | 日 | 8h | 实战：项目 2 前端配置后台 + 部署 | 项目 2 上线版本 |
| D246 | 一 | 2h | 作品集整理（GitHub/README/部署/演示） | 作品集仓库 |
| D247 | 二 | 2h | 项目复盘文档（架构决策/难点/量化成果） | 复盘文档 |
| D248 | 三 | 2h | 简历优化（技术栈/项目/量化） | 更新后简历 |
| D249 | 四 | 2h | 系统设计方法论（需求→估算→API→Schema→架构） | 方法论笔记 |
| D250 | 五 | 2h | 设计题：实时 AI 对话系统（百万用户） | 设计文档 |
| D251 | 六 | 8h | 实战：系统设计 企业级 Agent 平台 | 系统设计文档 |
| D252 | 日 | 8h | 实战：系统设计 高并发 RAG 客服系统 | 系统设计文档 |
| D253 | 一 | 2h | AI 面试题（RAG/Embedding/Prompt/上下文窗口） | AI 面试题集 |
| D254 | 二 | 2h | Agent 面试题（ReAct/Planning/Memory/Multi-Agent） | Agent 面试题集 |
| D255 | 三 | 2h | 前端面试题（React/Next.js/TS/性能） | 前端面试题集 |
| D256 | 四 | 2h | 后端面试题（FastAPI/并发/数据库/缓存） | 后端面试题集 |
| D257 | 五 | 2h | 项目深挖面试（架构/难点/取舍/量化） | 项目问答集 |
| D258 | 六 | 8h | 模拟面试（系统设计 + 技术深挖） | 模拟面试记录 |
| D259 | 日 | 8h | 模拟面试（项目讲解 + 行为面试 STAR） | 模拟面试记录 |
| D260 | 一 | 2h | 多模态面试题 | 面试题集 |
| D261 | 二 | 2h | 工程效率/运维面试题（Docker/K8s/CI/CD） | 面试题集 |
| D262 | 三 | 2h | 薄弱点专项复习 | 复习笔记 |
| D263 | 四 | 2h | 行为面试 + 谈薪 + 职业规划 | 行为面试准备 |
| D264 | 五 | 2h | 全计划复盘 + 知识图谱整理 | 知识图谱 |
| D265 | 六 | 8h | **Buffer 9**：最终复盘 + 作品集定稿 | 最终作品集 |
| D266 | 日 | 8h | **Buffer 9**：全真模拟面试 + 未来规划 | M9 验收 + 未来规划 |

> **本阶段作品**：★★★ 2 个上线项目（企业知识库 AI 客服 + AI 自动化工具）+ 完整作品集

---

## 里程碑时间线

```
W2     W5     W9     W15    W21    W25    W29    W32    W38
 |      |      |      |      |      |      |      |      |
 D14    D35    D63    D105   D147   D175   D203   D224   D266
 |      |      |      |      |      |      |      |      |
[M1]   [M2]   [M3]   [M4]   [M5]   [M6]   [M7]   [M8]   [M9]
双栈    Prompt Chatbot RAG    多智能  高并发  云原生  多模态  作品集
地基    大师   前端   全栈★   体系统  网关    上线    (语音/  +就绪
                     软启动  ★正式               图像)
                            可投简历
```

| 里程碑 | 截止日 | 日期 | 验收要点 |
|:--|:--|:--|:--|
| M1 | D14 | 2026-06-14 | Python 异步 + React/TS SPA |
| M2 | D35 | 2026-07-05 | 多厂商 LLM 客户端 + Prompt 库 + Function Calling |
| M3 | D63 | 2026-08-02 | Next.js 流式对话 + 配置后台 + 上传界面 |
| M4 | D105 | 2026-09-13 | RAG 全栈应用上线（**★软启动求职**） |
| M5 | D147 | 2026-10-25 | 多智能体系统（**★正式可投简历，转边投边学**） |
| M6 | D175 | 2026-11-22 | 高并发网关（WebSocket + 多数据库 + 限流熔断 + 压测） |
| M7 | D203 | 2026-12-20 | 云原生（Docker/K8s + CI/CD + 监控 + SLA） |
| M8 | D224 | 2027-01-10 | 多模态（语音 Agent + 图像生成 + 产品集成） |
| M9 | D266 | 2027-02-21 | 2 个上线项目 + 作品集 + 面试就绪 |

---

## 每周复盘问题

每周日晚完成（15-30 分钟）：

1. **完成度**：本周 7 天任务完成几天？未完成原因？
2. **难点回顾**：本周最大困难是什么？如何解决（或下周补强）？
3. **知识掌握**：能否一句话向别人解释本周每个核心概念？
4. **代码产出**：本周写了多少有效代码？有无可复用模块沉淀进作品集？
5. **全栈联动**：本周的 AI 能力是否同时有前端「看得见」、后端「扛得住」？
6. **作品部署**：本阶段作品是否保持线上可访问、README 最新？
7. **求职进展**（Stage B）：本周投递/面试几家？面试反馈暴露了哪些待补短板？
8. **Buffer 使用**（仅 Buffer 周）：是否用于复盘补强，还是浪费了？
