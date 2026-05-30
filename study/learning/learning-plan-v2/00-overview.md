# AI 应用开发 + 后端架构 28 周学习计划

## 学习节奏

| 时间段 | 学习时长 |
|:---|:---|
| 周一至周五 | 2 小时/天 |
| 周六、周日 | 8 小时/天 |
| 每周合计 | 26 小时 |
| 28 周总计 | **728 小时**（含 112h 缓冲） |

**计划周期**：2026-04-06 ~ 2026-10-18（28 周）

---

## 阶段地图

```
W01      W02-04      W05-09      W10-12      W13-17      W18-20      W21-22      W23-28
│        │           │           │           │           │           │           │
▼        ▼           ▼           ▼           ▼           ▼           ▼           ▼
┌──────┐ ┌─────────┐ ┌─────────┐ ┌─────────┐ ┌─────────┐ ┌─────────┐ ┌─────────┐ ┌─────────┐
│Phase1│→│ Phase2  │→│ Phase3  │→│ Phase4  │→│ Phase5  │→│ Phase6  │→│ Phase7  │→│ Phase8  │
│Python│ │LLM+Prompt│ │RAG+Redis│ │工程化   │ │Agent+MCP│ │高级模式 │ │基础设施 │ │综合项目 │
│Async │ │+MCP基础 │ │+FastAPI │ │+Docker  │ │+Celery  │ │+并发    │ │+K8s     │ │+面试   │
│      │ │         │ │         │ │+PostgreSQL│ │+Nginx LB│ │+PG高级  │ │+系统设计│ │        │
└──────┘ └─────────┘ └─────────┘ └─────────┘ └─────────┘ └─────────┘ └─────────┘ └─────────┘
   │         │           │           │           │           │           │           │
里程碑1    里程碑2      里程碑3      里程碑4      里程碑5      里程碑6      里程碑7      里程碑8
Async+Test LLM多厂商   RAG API+缓存  生产就绪    多智能体    性能优化    分布式架构  作品集+面试
```

---

## 阶段总览

| 阶段 | 文件名 | 周次 | 小时 | AI 内容 | 后端内容（融合） | 里程碑 |
|:---|:---|:---|:---|:---|:---|:---|
| 1 | phase1-python.md | W01 | 26h | — | Python async/type hints/pytest/packaging | Async 程序 + 单元测试通过 |
| 2 | phase2-llm-prompt.md | W02-04 | 78h | 多厂商 LLM API + Prompt 工程 + MCP 基础 | API 客户端设计、错误处理、流式响应 | 多厂商 LLM 客户端（Claude/OpenAI/Zhipu）+ 结构化输出 + Prompt 缓存 |
| 3 | phase3-rag.md | W05-09 | 130h | RAG 原始实现→框架→高级技巧 | FastAPI 服务、Redis 语义缓存、向量库集成 | RAG API（FastAPI）+ Redis 缓存 + RAGAs 评估 |
| 4 | phase4-engineering.md | W10-12 | 78h | AI 管道生产化 | Docker 容器化、CI/CD、PostgreSQL 持久化、日志系统 | Dockerized 应用 + GitHub Actions + JWT 认证 |
| 5 | phase5-agent.md | W13-17 | 130h | LangGraph + MCP 工具集成 + 多智能体 | Celery 异步任务、消息队列、Nginx 负载均衡 | LangGraph 多智能体系统 + MCP 工具 + Celery 异步 + Nginx LB |
| 6 | phase6-advanced.md | W18-20 | 78h | 高级 RAG/Agent 模式 | 并发优化、PostgreSQL pgvector、Prometheus/Grafana 监控、OpenTelemetry 追踪 | 性能优化（并发）+ PG 高级特性 + 可观测性 |
| 7 | phase7-infra.md | W21-22 | 52h | — | Redis 集群、Kubernetes 部署、系统设计 | Redis 集群 + K8s 部署 + 100K 用户系统设计白板 |
| 8 | phase8-project.md | W23-28 | 156h | 综合项目 | 全栈集成、面试准备 | 完整作品集 + 系统设计面试就绪 |

**总计**：26 + 78 + 130 + 78 + 130 + 78 + 52 + 156 = **728 小时**

---

## 里程碑详情

### 里程碑 1（W01 末）
**产出**：能用 Python 写异步程序，单元测试通过

**验收标准**：
- [ ] 掌握 Python async/await 语法，能写异步函数
- [ ] 能用 pytest 编写和运行单元测试
- [ ] 理解类型提示（type hints），代码有完整注解
- [ ] 能用 setuptools/pyproject.toml 打包 Python 项目

---

### 里程碑 2（W04 末）
**产出**：多厂商 LLM 客户端（Claude/OpenAI/Zhipu），支持流式 + 结构化输出 + Prompt 缓存

**验收标准**：
- [ ] 实现统一的 LLM 客户端接口，支持 Claude、OpenAI、Zhipu 三家 API
- [ ] 支持流式输出（streaming）和完整响应两种模式
- [ ] 实现结构化输出（JSON mode / tool use）
- [ ] 理解 Prompt 缓存机制，能配置缓存参数
- [ ] MCP（Model Context Protocol）基础概念理解，能集成简单工具

---

### 里程碑 3（W09 末）
**产出**：RAG API（FastAPI）+ Redis 语义缓存，支持多格式文档

**验收标准**：
- [ ] FastAPI 服务支持文档上传（PDF/Word/MD/TXT/Excel/CSV）
- [ ] 实现向量检索（raw 实现 + LangChain 框架两种）
- [ ] Redis 语义缓存集成完成，缓存命中率 > 60%
- [ ] 用 RAGAs 评估检索质量（Faithfulness/Answer Relevancy）
- [ ] 能用 Postman/curl 调用 API，返回结果准确

---

### 里程碑 4（W12 末）
**产出**：生产就绪的 RAG 应用（容器化、认证、CI/CD）

**验收标准**：
- [ ] Docker 镜像构建成功，容器可正常运行
- [ ] 实现 JWT 认证，API 端点受保护
- [ ] GitHub Actions CI/CD 流程完整（测试 → 构建 → 推送）
- [ ] PostgreSQL 持久化集成，文档元数据存储
- [ ] 日志系统完善，能追踪请求链路

---

### 里程碑 5（W17 末）
**产出**：LangGraph 多智能体系统 + MCP 工具集成 + Celery 异步化

**验收标准**：
- [ ] 用 LangGraph 实现多智能体协作（Retriever + Analyzer + Orchestrator）
- [ ] MCP 工具集成完成，Agent 能调用外部工具
- [ ] Celery 异步任务队列集成，文档摄入异步化
- [ ] 消息队列（RabbitMQ/Redis）配置完成
- [ ] Nginx 负载均衡配置，支持多实例部署

---

### 里程碑 6（W20 末）
**产出**：性能优化完成，可观测性就绪

**验收标准**：
- [ ] 并发优化：asyncio 连接池、批量处理性能提升 > 50%
- [ ] PostgreSQL pgvector 扩展集成，向量查询性能优化
- [ ] Prometheus + Grafana 监控面板完成
- [ ] OpenTelemetry 分布式追踪集成
- [ ] 性能压测数据对比（吞吐量、延迟、资源占用）

---

### 里程碑 7（W22 末）
**产出**：分布式架构设计能力

**验收标准**：
- [ ] Redis 集群部署和故障转移理解
- [ ] Kubernetes 基础部署（Pod/Service/Deployment）
- [ ] 能白板设计 100K 用户 RAG 系统架构
- [ ] 理解 CAP 定理、一致性哈希、分布式锁
- [ ] 后端架构设计题训练完成（3+ 道真题）

---

### 里程碑 8（W28 末）
**产出**：完整作品集 + 面试就绪

**验收标准**：
- [ ] 1-2 个完整项目托管在 GitHub，README 完善
- [ ] 能清晰讲解技术实现细节和架构设计
- [ ] 系统设计面试白板演练 3+ 次
- [ ] 行为面试准备（STAR 法则讲述项目经历）
- [ ] 代码质量达到生产级别（测试覆盖率 > 80%）

---

## 全栈开发者优势盘点

### 你已经有的能力

| 你的旧技能 | 对应的 AI 开发能力 | 转化成本 |
|:---|:---|:---|
| Node.js REST API 开发 | FastAPI 服务开发（换语法，逻辑相同） | 极低 |
| Spring Boot 分层架构 / 依赖注入 | AI 服务的分层设计（Config / Service / API） | 极低 |
| 前后端全栈经验 | 独立交付完整 AI 产品 | 无需转化 |
| HTTP 请求 / JSON 处理 | 调用 LLM API（本质就是一个 HTTP POST） | 极低 |
| 工业领域知识（AGV） | 垂直行业 AI 落地的场景感，作品集差异化 | 无需转化 |
| 数据库设计 / SQL | PostgreSQL + pgvector 快速上手 | 极低 |
| 消息队列 / 异步处理 | Celery + MQ 架构迁移 | 极低 |

### AI 应用开发的技能优先级

| 技能 | 优先级 | 说明 |
|:---|:---|:---|
| LLM API 调用 + Prompt 工程 | ★★★★★ | 核心中的核心 |
| RAG 系统（向量检索、分块、重排序） | ★★★★★ | 企业需求最大的场景 |
| Agent 框架（LangGraph / 自建） | ★★★★☆ | 进阶必备 |
| Python 工程化（FastAPI / async） | ★★★★☆ | 有 Node.js 底子，学习曲线平缓 |
| Docker 容器化部署 | ★★★☆☆ | 交付上线必须 |
| 多线程 / 高并发 / 分布式 / 消息队列 | ★★★☆☆ | **规模化阶段才需要**，不是入门门槛 |
| 缓存 / 数据库调优 | ★★★☆☆ | 同上，后期按需补充 |

---

## AI + 后端融合策略

### 为什么后端知识要融合进 AI 学习？

**传统分离模式的问题**：
- 先学 AI（LLM/RAG/Agent），再学后端 → 知识孤立，难以形成系统观
- 学完后端再做项目 → 时间浪费，重复学习

**融合模式的优势**：

1. **即时反馈**：每个 AI 功能完成后，立即用后端知识优化它
   - 写完 LLM 客户端 → 立即学 API 设计、错误处理、流式响应
   - 写完 RAG → 立即集成 Redis 缓存、FastAPI 服务化
   - 写完 Agent → 立即用 Celery 异步化、Nginx 负载均衡

2. **问题驱动**：遇到真实问题时学习后端知识，记忆深刻
   - "RAG 检索太慢" → 学 Redis 缓存、并发优化
   - "单机处理不了" → 学分布式、消息队列、K8s
   - "无法追踪问题" → 学日志、监控、链路追踪

3. **持续构建**：每个阶段都有可运行的完整系统
   - W01：Python CLI 工具
   - W04：多厂商 LLM 客户端
   - W09：RAG API 服务
   - W12：生产级容器化应用
   - W17：分布式多智能体系统
   - W22：云原生部署
   - W28：完整作品集

4. **面试叙事**：能讲出"为什么这样设计"的故事
   - 不是"我学了 Redis"，而是"RAG 检索慢，我用 Redis 语义缓存，命中率从 20% 提升到 60%"
   - 不是"我会 K8s"，而是"系统从单机 100 QPS 扩展到 10K QPS，用 K8s 自动扩缩容"

---

## 缓冲安排

| 缓冲 | 位置 | 时间 | 小时 | 用途 |
|:---|:---|:---|:---|:---|
| Buffer 1 | W04 末 | D27-28 | 16h | 复习 Phase 1-2：Python 基础 + LLM 多厂商客户端 |
| Buffer 2 | W09 末 | D62-63 | 16h | 复习 Phase 3：RAG 原始实现 + FastAPI + Redis 缓存 |
| Buffer 3 | W12 末 | D83-84 | 16h | 复习 Phase 4：Docker + CI/CD + PostgreSQL + 认证 |
| Buffer 4 | W17 末 | D118-119 | 16h | 复习 Phase 5：LangGraph + MCP + Celery + Nginx LB |
| Buffer 5 | W20 末 | D139-140 | 16h | 复习 Phase 6：并发优化 + pgvector + 可观测性 |
| Buffer 6 | W22 末 | D153-154 | 16h | 复习 Phase 7：Redis 集群 + K8s + 系统设计 |
| Buffer 7 | W28 末 | D195-196 | 16h | 最终复习 + 作品集打磨 + 面试模拟 |

**总缓冲**：7 × 16h = **112 小时**

---

## 先修要求

| 要求 | 说明 |
|:---|:---|
| 编程经验 | 3.5+ 年全栈开发（Java/Node.js/Vue）✓ |
| Python 基础 | 无需精通，Phase 1 会系统补充 |
| 网络 | 能访问 GitHub、OpenAI/Claude/Zhipu API（推荐备好代理） |
| 英语 | 能读懂技术文档（借助翻译工具即可） |
| 数学 | **不需要**微积分/线代基础，AI 应用开发不涉及 |
| 电脑 | Windows / Mac / Linux 均可，8GB 内存以上 |

---

## 工具清单

### 必装软件
- [ ] Python 3.11+：https://www.python.org/downloads/
- [ ] VS Code：https://code.visualstudio.com/
- [ ] Git：https://git-scm.com/
- [ ] Docker Desktop：https://www.docker.com/products/docker-desktop
- [ ] VS Code 插件：Python, Pylance, GitLens, Docker

### 账号注册
- [ ] GitHub 账号
- [ ] LLM API 账号（三选一或全选）
  - Anthropic Claude：https://console.anthropic.com/
  - OpenAI：https://platform.openai.com/（需信用卡）
  - 智谱 AI：https://open.bigmodel.cn/（国内免费额度）
- [ ] 云服务器账号（可选，Phase 4 后需要）
  - 阿里云 / 腾讯云 / AWS

### 本地开发环境
- [ ] PostgreSQL 15+（本地或 Docker）
- [ ] Redis 7+（本地或 Docker）
- [ ] RabbitMQ（Docker）

---

## 费用预估

| 项目 | 预估费用 | 说明 |
|:---|:---|:---|
| LLM API 调用（28 周学习） | ¥100-300 | Claude + OpenAI + Zhipu 混用 |
| 云服务器（Phase 4 后，可选） | ¥30-100/月 × 5 月 | 部署和测试用 |
| 嵌入模型（本地免费） | ¥0 | sentence-transformers 本地运行 |
| 域名（可选） | ¥50-100/年 | 作品集展示用 |
| **总计** | **¥300-800** | 学生/初创友好 |

**成本优化建议**：
- 优先用国内免费额度（智谱 AI）
- 云服务器用学生优惠或免费额度
- 本地开发用 Docker，减少云资源消耗

---

## 学习资源

### 官方文档（必读）
- Anthropic Claude API：https://docs.anthropic.com/
- LangChain：https://python.langchain.com/
- LangGraph：https://langchain-ai.github.io/langgraph/
- FastAPI：https://fastapi.tiangolo.com/
- PostgreSQL：https://www.postgresql.org/docs/

### 推荐课程
- DeepLearning.AI 短课程（免费）
- Anthropic 官方教程
- 工业级 RAG 系统设计（内部文档）

### 社区资源
- GitHub Discussions
- Stack Overflow
- 技术博客（Medium / Dev.to）

---

## 学习方法论

### 核心原则

1. **做中学**：每个阶段都有可运行的代码
2. **问题驱动**：遇到问题时学习，而不是预先学习
3. **持续反馈**：每周回顾进度，调整计划
4. **作品导向**：最终目标是完整作品集，不是知识点清单

### 每周节奏

- **周一-周五**（2h/天）：学习新知识 + 编码实践
- **周六**（8h）：深度项目工作 + 问题解决
- **周日**（8h）：复习 + 文档整理 + 下周规划

### 遇到卡点时

1. 先尝试 30 分钟自己解决
2. 查阅官方文档 + Stack Overflow
3. 在社区提问（提供最小复现代码）
4. 必要时跳过，继续下一个主题（不要陷入完美主义）

---

## 成功标志

- [ ] 完成 8 个里程碑，每个都有可验证的产出
- [ ] GitHub 上有 2+ 个完整项目，代码质量达到生产级
- [ ] 能用 15 分钟讲清楚一个 RAG 系统的架构
- [ ] 能白板设计一个 100K 用户的 AI 服务系统
- [ ] 系统设计面试通过（或获得面试邀请）
- [ ] 总学习时间 ≤ 728 小时

---

**开始日期**：2026-04-06  
**预计完成**：2026-10-18  
**祝你学习顺利！** 🚀
