# 学习资料推荐

> 按阶段精选，优先官方文档 + 权威实践，避免资料过载。每阶段挑 1-2 个主线资料深读，其余备查。

---

## 通用 / 贯穿全程

- **官方文档优先**：遇到 API/框架问题，第一手查官方文档，而非二手博客
- **AI 编程工具**：Claude Code（claude.ai/code）、Cursor —— 贯穿全程提效，是本岗位核心竞争力之一
- **代码托管**：GitHub（作品集 + README + Actions）
- **英文文档**：借助翻译工具直读一手资料，避免二手信息失真

---

## Phase 1：双地基（Python + TS/React）

| 资料 | 类型 | 说明 |
|:--|:--|:--|
| Python 官方教程 / Real Python | 文档 | async/类型注解/生成器 |
| pytest 官方文档 | 文档 | fixtures/parametrize/mock |
| uv 文档（astral-sh/uv） | 文档 | 现代包管理 |
| TypeScript Handbook | 文档 | 类型系统权威 |
| React 官方文档（react.dev） | 文档 | Hooks/思维模型，对比 Vue |
| Zustand 文档 | 文档 | 轻量状态管理（类比 Pinia） |

## Phase 2：LLM API + Prompt 精通

| 资料 | 类型 | 说明 |
|:--|:--|:--|
| Anthropic Claude 文档 | 文档 | Messages API / tool_use / Prompt Caching |
| OpenAI API 文档 | 文档 | chat / function calling |
| 智谱 GLM / DeepSeek 文档 | 文档 | 国产模型 + 免费额度 |
| Anthropic Prompt Engineering 指南 | 文档 | Prompt 工程权威 |
| 《Prompt Engineering Guide》(promptingguide.ai) | 站点 | CoT/ToT/Self-consistency |

## Phase 3：AI 对话前端

| 资料 | 类型 | 说明 |
|:--|:--|:--|
| Next.js 官方文档（App Router） | 文档 | 路由/RSC/Server Actions |
| Vercel AI SDK 文档 | 文档 | useChat/streamText 流式对话 |
| shadcn/ui 文档 | 文档 | 组件库 |
| Tailwind CSS 文档 | 文档 | 原子化样式 |
| react-hook-form + zod 文档 | 文档 | 表单工程 |
| TanStack Query 文档 | 文档 | 数据获取缓存 |

## Phase 4：RAG + 后端服务化

| 资料 | 类型 | 说明 |
|:--|:--|:--|
| FastAPI 官方文档 | 文档 | 路由/异步/SSE |
| LangChain / LlamaIndex 文档 | 文档 | RAG 框架 |
| sentence-transformers / BAAI bge | 文档 | 嵌入模型 |
| Milvus 文档 / PGVector README | 文档 | 向量库实战 |
| RAGAs 文档 | 文档 | RAG 评估指标 |
| Dify 文档 | 文档 | 可视化 RAG/工作流 |

## Phase 5：Agent 核心链路

| 资料 | 类型 | 说明 |
|:--|:--|:--|
| LangGraph 官方文档 | 文档 | StateGraph/多智能体 |
| MCP 规范 + Python SDK | 文档 | 工具协议 |
| AutoGen 文档（microsoft） | 文档 | GroupChat 多智能体 |
| LangSmith 文档 | 文档 | Agent 观测/追踪 |
| 《ReAct》《Reflexion》论文 | 论文 | Agent 范式原理 |

## Phase 6：后端架构 + 多数据库

| 资料 | 类型 | 说明 |
|:--|:--|:--|
| SQLAlchemy / Alembic 文档 | 文档 | ORM + 迁移 |
| PostgreSQL / MySQL 文档 | 文档 | 索引/事务/优化 |
| MongoDB 文档 | 文档 | 文档模型/聚合 |
| Redis 文档 | 文档 | Stream/Pub-Sub/分布式锁 |

## Phase 7：部署运维 + 可观测性

| 资料 | 类型 | 说明 |
|:--|:--|:--|
| Docker / Docker Compose 文档 | 文档 | 容器化 |
| Kubernetes 文档 + kubectl 速查 | 文档 | 部署/HPA |
| Helm 文档 | 文档 | 包管理 |
| GitHub Actions 文档 | 文档 | CI/CD |
| Prometheus / Grafana / OpenTelemetry 文档 | 文档 | 可观测性 |

## Phase 8：多模态

| 资料 | 类型 | 说明 |
|:--|:--|:--|
| Whisper / faster-whisper | 文档 | ASR |
| Edge-TTS / CosyVoice | 文档 | TTS |
| Stable Diffusion / ComfyUI | 文档 | 图像生成 |
| 多模态 LLM（GPT-4o / Claude / Qwen-VL）文档 | 文档 | 图像理解 |

> 推理加速（vLLM/TGI/显存）、Go 后端的学习资料见 [`appendix-后续学习.md`](./appendix-后续学习.md)。

## Phase 9：综合项目 + 面试

| 资料 | 类型 | 说明 |
|:--|:--|:--|
| 《System Design Interview》(Alex Xu) | 书 | 系统设计方法论 |
| GitHub 优秀 AI 项目 README | 参考 | 作品集排版借鉴 |
| 各厂 AI 应用岗 JD | 参考 | 对标技能与面试方向 |

---

## 辅助教程（体系化课程，跟着做）

> 上面的表偏「官方文档」（查阅用）；这里是**带实操、能跟着做**的课程/书，作为血肉补充。
> ⚠️ AI 生态迭代快，下列以**名称/出处**为准，链接与版本临用时核一下时效。

### 🥇 顶级优先（最高 ROI，先看这几样）

- **DeepLearning.AI 短课系列**（吴恩达，多为免费，1-2h/门）——转岗 AI 的最佳辅助，几乎每门对应 V3 一个主题：
  `ChatGPT Prompt Engineering for Developers`、`LangChain for LLM App Development`、`LangChain: Chat with Your Data`(RAG)、`Functions, Tools and Agents with LangChain`、`Building and Evaluating Advanced RAG`、`AI Agents in LangGraph`、`Multi AI Agent Systems with crewAI`、`AI Agentic Design Patterns with AutoGen`
- **Anthropic 官方**：`anthropics/courses`（GitHub 交互式 Prompt 工程课）+ **Anthropic Cookbook** + 文章《Building effective agents》（Agent 设计基石）
- **Next.js 官方 Learn 课**（nextjs.org/learn）——免费交互式，前端主线直接跟做
- **FastAPI 官方 Tutorial**——作者亲写，后端主线直接跟做

### 📚 按阶段补充

| 阶段 | 辅助教程 |
|:--|:--|
| P1 Python | Real Python（进阶教程）；《Fluent Python》（深挖时翻） |
| P1 TS/React | React 官方 `react.dev/learn`；Total TypeScript（含免费篇）；官方 "Thinking in React"（Vue→React 迁移） |
| P2 LLM/Prompt | DLAI Prompt 课 + Anthropic 交互教程；OpenAI Cookbook（GitHub） |
| P3 前端 | Vercel AI SDK 官方 examples；shadcn/ui 官方示例 |
| P4 RAG | DLAI `Chat with Your Data` + `Advanced RAG`；LlamaIndex `Building Agentic RAG`；freeCodeCamp 长视频 RAG 实战 |
| P5 Agent | LangChain Academy 免费 LangGraph 课；DLAI LangGraph/crewAI/AutoGen 三门；《Building effective agents》 |
| P6 后端/DB | Cosmic Python（《Architecture Patterns with Python》免费在线）；Use The Index, Luke（SQL 索引）；MongoDB University / Redis University |
| P7 部署运维 | TechWorld with Nana（YouTube，Docker/K8s/CI-CD）；Kubernetes 官方 Tutorials；KodeKloud K8s 入门 |
| P8 多模态 | Hugging Face 免费课：`Audio Course`(ASR/TTS)、`Diffusion Models Course`(SD)；ComfyUI 社区教程 |
| P9 系统设计/面试 | 《System Design Interview》Vol.1/2（Alex Xu）+ ByteByteGo；进阶《Designing Data-Intensive Applications》 |
| 附录（推理加速） | vLLM 官方 docs + 示例；Hugging Face TGI docs |

### 使用原则

**别当「课程收藏家」**——每个主题挑 **1 门主线课 + 官方 cookbook** 跟做即可，看完立刻用到当周作品里。课程是血肉，**动手做才长肌肉**。

---

## 学习资料使用原则

1. **主线深读，支线备查**：每阶段挑 1-2 个核心资料吃透，其余遇到问题再查。
2. **官方 > 博客 > 视频**：优先一手文档，博客用于补充视角，视频用于建立直觉。
3. **边读边做**：所有资料都服务于当日产出，不做「只读不练」的收藏家。
4. **版本敏感**：AI 生态迭代快，注意文档/库版本，以官方最新为准。
