# 企业级 AI Agent 全栈工程师学习计划（V3）

> 定制规格：工作日 2h/天 · 周末 8h/天 = 26h/周
> **全栈复合路线**：共 38 周，总计 **988 小时**
> **目标**：从 0 到 1 独立交付**企业级 AI Agent 应用**——前端交互 + 后端架构 + 数据库 + 大模型集成全流程
> **适用对象**：3.5+ 年全栈经验（Java / Node.js / Vue）
> **第一要务**：以最快路径练成「AI 应用开发能力」并到达**可投简历门槛**，此后边投边学

---

## 核心策略：两阶段 + 求职前置

把整条路线切成两段，**第一目标是尽快到达「可投简历」**：

```
══ Stage A：先具备 AI 应用开发能力 ════════════════►│门槛│══ Stage B：边投边学 ════════════►
P1     P2      P3       P4         P5               │    │  P6       P7       P8      P9
双地基  LLM+    AI对话   RAG全栈    Agent核心        │D147│  后端架构  部署运维  多模态   综合项目
       Prompt  前端     应用★      链路             │可投│  多数据库  +可观测  语音/图像 +作品集冲刺
                        软启动(D105)               │简历│
                                                   ↑
                                     P5 末 Agent 就绪，转全力求职；P6-P9 边投边学
```

- **Stage A（P1-P5，约 5.5 月）**：聚焦"能开发并上线 AI 应用"的核心能力。每个阶段产出一个**可部署、可演示**的作品。
- **软启动门槛**：P4 末（D105 / 2026-09-13）——首个 RAG 全栈应用上线，即可开始零星投递、收集面试反馈。
- **正式门槛**：P5 末（D147 / 2026-10-25）——Agent 就绪，转全力求职。
- **Stage B（P6-P9，约 4.5 月）**：后端架构、云原生、多模态、综合项目——**边面试边补强**，面试反馈反向指导学习重点。

> **附录（后续学习，不计入 988h）**：推理加速（vLLM/TGI/显存量化）、Go 后端（可选第二语言）。这些是 JD 加分项，达成核心目标后按机会择期补攻，见 `appendix-后续学习.md`。

---

## 学习节奏

| 时间段 | 学习时长 |
|:---|:---|
| 周一至周五 | 2 小时/天 |
| 周六、周日 | 8 小时/天 |
| 每周合计 | 26 小时 |
| 38 周总计 | **988 小时**（含约 128h 缓冲） |

**计划周期**：2026-06-01（周一）~ 2027-02-21（周日），共 38 周 / 266 天

---

## 设计理念：融合式全栈

AI 能力一落地，立即用前端把它「看得见」、用后端把它「扛得住」：做 LLM 客户端时同步搭对话 UI；做 Agent 时同步搭配置后台；做 RAG 时同步搭上传与引用界面。不搞「先学完前端，再学后端，最后做 AI」的割裂串行。每个阶段都产出**可运行、可演示、可写进作品集、且保持线上部署**的完整系统。

---

## 阶段总览

| 阶段 | 文件 | 周次 | 天 | 小时 | 核心 | 阶段作品（持续部署） |
|:--|:--|:--|:--|:--|:--|:--|
| 1 | phase1-foundations.md | W1-2 | D1-14 | 52h | Python 现代化 + TS/React 启蒙 | CLI 工具 + React SPA |
| 2 | phase2-llm-prompt.md | W3-5 | D15-35 | 78h | 多厂商 LLM + Prompt 精通 + Function Calling | LLM 客户端库 + Prompt 工作台 |
| 3 | phase3-frontend.md | W6-9 | D36-63 | 104h | React/Next.js + 对话界面 + 配置后台 | ★ Chatbot Web 应用上线 |
| 4 | phase4-rag.md | W10-15 | D64-105 | 156h | RAG 全链路 + FastAPI/Redis/PGVector/Milvus | ★★ RAG 知识库问答上线（**软启动求职**） |
| 5 | phase5-agent.md | W16-21 | D106-147 | 156h | ReAct/Planning/Memory/Tool Use/Multi-Agent | ★★ 多智能体系统上线（**正式可投简历**） |
| — | — | — | **D147** | — | **★ 可投简历门槛：Stage A 完成，转边投边学** | — |
| 6 | phase6-backend-arch.md | W22-25 | D148-175 | 104h | 网关/WebSocket/MySQL/Mongo/Redis/高并发 | 高并发网关 + 多数据库层 |
| 7 | phase7-deploy-ops.md | W26-29 | D176-203 | 104h | Docker/K8s/CI/CD/监控/SLA | 主线项目云原生上线 |
| 8 | phase8-multimodal.md | W30-32 | D204-224 | 78h | 多模态：ASR/TTS/SD + 多模态 Agent | 主线项目多模态升级 |
| 9 | phase9-project.md | W33-38 | D225-266 | 156h | 综合项目 + 作品集 + 面试 | ★★★ 2 个上线项目 + 作品集 |

**总计**：52+78+104+156+156+104+104+78+156 = **988 小时**

> 相比删改前：移除 Go 整周、推理加速 2 周移入附录，由 40 周/1040h 收敛为 **38 周/988h**，并新增「可投简历」门槛与每阶段作品要求。

---

## 里程碑详情

### M1（D14 / 2026-06-14）— 双栈地基
- [ ] Python async/await、类型注解、pytest，能写带测试的异步程序
- [ ] TypeScript 类型系统（接口/泛型/工具类型）
- [ ] React + Hooks 构建带状态管理的 SPA（借 Vue 心智迁移）

### M2（D35 / 2026-07-05）— Prompt 大师
- [ ] 统一 LLM 客户端：Claude/OpenAI/国产模型，流式 + 结构化输出
- [ ] Function Calling（工具调用/并行/参数校验）
- [ ] Prompt 精通：CoT/Few-shot/Self-consistency/ToT/上下文窗口管理
- [ ] Token 计数、成本估算、幻觉治理（引用/自检/置信度）

### M3（D63 / 2026-08-02）— 可用 Chatbot（首个上线作品）
- [ ] Next.js + Vercel AI SDK 流式逐字对话，Markdown/代码高亮
- [ ] 智能体配置后台（react-hook-form + zod）+ 文档上传界面
- [ ] 前端对接 P2 LLM 后端，端到端可用并**部署上线**

### M4（D105 / 2026-09-13）— RAG 全栈应用　★软启动求职
- [ ] 裸写 + LangChain 两种 RAG；多格式文档；混合检索 + Rerank + HyDE
- [ ] PGVector 与 Milvus 两种向量库 + 选型对比
- [ ] FastAPI RAG API（SSE）+ Redis 语义缓存 + RAGAs 评估
- [ ] 前端问答界面（含引用）端到端上线 → **首个完整 AI 应用，开始零星投递**

### M5（D147 / 2026-10-25）— 多智能体系统　★正式可投简历
- [ ] ReAct/CoT/Plan-and-Execute/Tool-Use 模式与选型
- [ ] Planning（任务分解/重规划）+ Memory（短/长/情景 + 向量存储）
- [ ] Tool Use：MCP Server 开发 + Function Calling 工程化
- [ ] Multi-Agent：LangGraph Supervisor + AutoGen GroupChat + Dify 二次开发
- [ ] 智能体配置后台全栈打通 + LangSmith 观测 → **Agent 系统上线，转全力求职**

### M6（D175 / 2026-11-22）— 高并发 Agent 网关
- [ ] Agent API 网关（路由/鉴权/限流/计费）+ WebSocket 会话管理
- [ ] MySQL/PostgreSQL 业务库 + MongoDB 对话日志 + Redis 会话/分布式锁
- [ ] 高并发：连接池/限流/熔断/幂等；压测达标

### M7（D203 / 2026-12-20）— 云原生上线
- [ ] 全栈 Docker 化 + Compose 一键启动
- [ ] GitHub Actions 全栈 CI/CD（测试门禁→构建→部署→回滚）
- [ ] K8s 部署 + HPA + Prometheus/Grafana + OTel + SLA 告警

### M8（D224 / 2027-01-10）— 多模态
- [ ] 语音对话 Agent 全链路（ASR Whisper → LLM → TTS）+ 流式 + 前端
- [ ] Stable Diffusion 文生图/图生图集成进 Agent；多模态 LLM 图像理解
- [ ] 多模态能力接入主线产品（语音输入 + 图像生成）

### M9（D266 / 2027-02-21）— 作品集 + 面试就绪
- [ ] 项目 1：企业知识库 AI 客服（RAG + Agent + 全栈 + 上线）
- [ ] 项目 2：AI 自动化工具/多智能体平台（配置后台 + 工具生态 + 上线）
- [ ] 作品集：GitHub + README + 部署链接 + 演示视频，量化成果
- [ ] 面试就绪：AI/Agent/前端/后端/系统设计/行为面试全覆盖

---

## JD 覆盖矩阵

| JD 要点 | 落点 |
|:--|:--|
| 全流程独立交付（前端+后端+DB+大模型集成） | 贯穿，集大成于 **P9** |
| Prompt Engineering / Planning / Tool Use / Memory / Multi-Agent | P2 + **P5** |
| 前端 React/Vue/Next.js + TypeScript | P1 + **P3** |
| AI 对话界面 + 智能体配置后台 | **P3** + P5 |
| 后端 FastAPI + RESTful + WebSocket + 会话管理 + 高并发 | **P6** |
| MySQL/PostgreSQL + Redis + MongoDB | **P6** |
| 向量数据库 Milvus/Pinecone/PGVector | **P4** |
| LLM 对接 + Token 优化 + 延迟 + 幻觉 + 上下文窗口 | **P2** + 贯穿 |
| LangChain/LangGraph/AutoGen/Dify 二次开发 | P4 + **P5** |
| ReAct/CoT + Function Calling + RAG | P2 + P4 + **P5** |
| Docker/K8s + CI/CD + AI 编程工具 | **P7** + 贯穿 |
| 部署 + 监控 + 故障排查 + SLA | **P7** |
| 多模态 ASR/TTS/Stable Diffusion | **P8** |
| 独立交付案例 + 作品集（Chatbot/AI客服/AI自动化） | **P9** + 每阶段作品 |
| 推理加速 vLLM/TGI + 显存优化（**JD 加分项**） | **附录**（后续学习） |
| 后端 Go（JD「Python *或* Go」，**加分项**） | **附录**（后续学习） |

---

## 全栈优势盘点

| 你的旧技能（3.5+ 年） | 对应的新能力 | 转化成本 |
|:--|:--|:--|
| Vue 生态 / 前端工程 | React + Next.js + TS（心智模型相通） | 低 |
| Node.js / Java 后端 | FastAPI 服务（HTTP 逻辑迁移） | 低 |
| 前后端全栈经验 | 独立交付完整 AI 产品 | 无 |
| 数据库设计 / SQL | MySQL/PG + 索引/事务（直接复用） | 极低 |
| 消息队列 / 异步处理 | Celery / WebSocket / 高并发 | 低 |
| HTTP / JSON / REST | LLM API 调用（本质是 HTTP POST） | 极低 |

**重点补强**：① 大模型/Agent 原理与工程化（核心壁垒）② React/Next.js（已有 Vue 底子）③ 向量库/多模态（增量新知）。

---

## 贯穿项目主线（作品集驱动，持续部署）

每阶段产出一个"活作品"，主线项目逐阶段长大，**始终保持线上可访问**：

```
P1  CLI 工具 + React SPA（地基练手）
P2  LLM 客户端库 + Prompt 工作台（开源）
P3  ★ Chatbot Web 应用（上线）
P4  ★★ RAG 知识库问答（全栈上线）── 软启动求职
P5  ★★ 多智能体系统 + 配置后台（上线）── 正式可投简历
P6  高并发 Agent 网关 + 多数据库（升级后端）
P7  云原生部署（K8s + 监控 + SLA）
P8  多模态升级（语音 + 图像插件）
P9  ★★★ 企业知识库 AI 客服 + AI 自动化工具（2 个上线项目，作品集定稿）
```

**面试叙事**：用「问题 → 方案 → 量化效果」讲故事。如「RAG 检索慢 → Redis 语义缓存，命中率 20%→65%」「首字延迟高 → SSE 流式 + 小模型路由，2s→400ms」。

---

## 缓冲安排

每个 Phase 末的周末为缓冲（复盘 + 里程碑验收 + 补短板）：

| 缓冲 | 位置 | 天 | 小时 |
|:--|:--|:--|:--|
| Buffer 1 | P1 末 | D14 | 8h |
| Buffer 2 | P2 末 | D34-35 | 16h |
| Buffer 3 | P3 末 | D62-63 | 16h |
| Buffer 4 | P4 末 | D104-105 | 16h |
| Buffer 5 | P5 末 | D146-147 | 16h |
| Buffer 6 | P6 末 | D174-175 | 16h |
| Buffer 7 | P7 末 | D202-203 | 16h |
| Buffer 8 | P8 末 | D224 | 8h |
| Buffer 9 | P9 末 | D265-266 | 16h |

**总缓冲**：约 **128 小时**

---

## 强度与弹性提示（务必正视）

26h/周连续 38 周强度很高，若在职推进，倦怠是真实风险。建议：

1. **以里程碑达成度衡量进度，而非死磕日历**——落后于 D 编号不是失败，里程碑产出才是。
2. 每月可留 1 个完整周末弹性休整（不排任务），接受总周期可能拉长到 42-46 周。
3. Stage B 与求职并行后，**面试反馈优先级高于课表**——市场考什么，就先补什么。

---

## 工具与账号

- **必装**：Python 3.11+ / Node.js 20+ / VS Code / Git / Docker Desktop / **Claude Code 或 Cursor**（贯穿提效）
- **账号**：GitHub；LLM API（Claude/OpenAI/智谱/DeepSeek，国内免费额度优先）；云服务器（P7 后）
- **本地中间件（Docker）**：PostgreSQL / MySQL / MongoDB / Redis / RabbitMQ / Milvus
- **附录阶段**：云 GPU（按时租，用于 vLLM/SD 实验）

---

## 学习方法论

1. **做中学**：每阶段都有可运行、可演示、且部署上线的系统
2. **问题驱动**：遇到真实问题时学，记忆深刻
3. **全栈融合**：AI 能力一落地，立即前端「看见」、后端「扛住」
4. **作品导向 + 求职前置**：尽快上线首个 AI 应用，边投边学
5. **善用 AI 工具**：Claude Code/Cursor 加速编码，精力留给设计与调试

**每周节奏**：周一-周五（2h 学新知 + 编码）；周六（8h 深度项目）；周日（8h 复盘 + 文档 + 下周规划，Stage B 加入求职复盘）。

---

## 成功标志

- [ ] 完成 9 个里程碑，每个都有可验证、已部署的产出
- [ ] 最快约 5.5 月（P5 末）到达可投简历门槛，此后边投边学
- [ ] GitHub 上 2-3 个完整上线项目（前端 + 后端 + DB + 大模型集成）
- [ ] 能 15 分钟讲清一个企业级 Agent 系统的全栈架构
- [ ] 通过 AI 应用全栈岗位面试（或获得 offer）

---

**开始日期**：2026-06-01　|　**预计完成**：2027-02-21（核心可投简历门槛：2026-10-25）
