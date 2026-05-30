# 学习资料推荐

> 原则：每阶段只列 1-3 个核心资料，避免资料过多导致选择困难

---

## Phase 1：Python 速通（Week 1）

| 资料 | 说明 |
|:---|:---|
| [Python 官方教程](https://docs.python.org/zh-cn/3/tutorial/) | 官方中文版，快速过一遍语法和标准库 |
| [Exercism Python Track](https://exercism.org/tracks/python) | 交互式练习，巩固语法和惯用写法 |

## Phase 2：LLM API + Prompt Engineering（Week 2-4）

| 资料 | 说明 |
|:---|:---|
| [Anthropic Claude API 文档](https://docs.anthropic.com/) | Claude API 官方文档，Messages API / Tool Use / Streaming |
| [OpenAI API Reference](https://platform.openai.com/docs/api-reference) | 行业标准 API 设计参考，兼容格式广泛 |
| [智谱 AI 文档](https://open.bigmodel.cn/dev/howuse/model) | 国内大模型 API，无需翻墙，适合本地开发调试 |
| [DeepLearning.AI Prompt Engineering](https://www.deeplearning.ai/short-courses/chatgpt-prompt-engineering-for-developers/) | Andrew Ng 短课程，Prompt 工程入门必看 |
| [MCP 官方文档](https://modelcontextprotocol.io/) | Model Context Protocol，工具调用标准协议 |

## Phase 3：RAG + 服务化（Week 5-9）

| 资料 | 说明 |
|:---|:---|
| [LangChain 官方文档](https://python.langchain.com/) | RAG 全链路框架，Document Loader / Splitter / Retriever |
| [ChromaDB 文档](https://docs.trychroma.com/) | 轻量向量数据库，本地开发首选 |
| [DeepLearning.AI LangChain Chat with Your Data](https://www.deeplearning.ai/short-courses/langchain-chat-with-your-data/) | RAG 实战课程，覆盖文档加载到检索问答全流程 |
| [sentence-transformers 文档](https://www.sbert.net/) | 嵌入模型库，理解 Embedding 原理和使用 |

## Phase 4：生产化工程（Week 10-12）

| 资料 | 说明 |
|:---|:---|
| [FastAPI 官方文档（中文）](https://fastapi.tiangolo.com/zh/) | 异步 Web 框架，自带 OpenAPI 文档 |
| [Docker 官方入门](https://docs.docker.com/get-started/) | 容器化基础，Dockerfile 编写和 Compose 使用 |
| [PostgreSQL 文档](https://www.postgresql.org/docs/) | 生产级关系数据库，重点关注连接池和事务 |
| [GitHub Actions 文档](https://docs.github.com/zh/actions) | CI/CD 流水线，自动化测试和部署 |
| [Ollama 官网](https://ollama.ai/) | 本地运行开源大模型，开发调试利器 |

## Phase 5：Agent + 异步化（Week 13-17）

| 资料 | 说明 |
|:---|:---|
| [LangGraph 官方文档](https://langchain-ai.github.io/langgraph/) | 多步骤 Agent 编排框架，状态图驱动 |
| [MCP SDK for Python](https://github.com/modelcontextprotocol/python-sdk) | MCP 协议 Python 实现，构建 Tool Server |
| [DeepLearning.AI AI Agents in LangGraph](https://www.deeplearning.ai/short-courses/ai-agents-in-langgraph/) | Agent 实战课程，ReAct / Plan-and-Execute 模式 |
| [CrewAI 文档](https://docs.crewai.com/) | 多智能体协作框架，Role-Based Agent 设计 |

## Phase 6：进阶调优（Week 18-20）

| 资料 | 说明 |
|:---|:---|
| [Python asyncio 文档](https://docs.python.org/zh-cn/3/library/asyncio.html) | 异步编程核心，理解事件循环和协程 |
| [Prometheus 文档](https://prometheus.io/docs/) | 监控指标采集，时间序列数据库 |
| [Grafana 文档](https://grafana.com/docs/) | 可视化监控面板，搭配 Prometheus 使用 |
| [OpenTelemetry Python](https://opentelemetry.io/docs/languages/python/) | 分布式追踪标准，链路可观测性 |
| [pgvector GitHub](https://github.com/pgvector/pgvector) | PostgreSQL 向量扩展，生产级向量检索方案 |

## Phase 7：后端强化（Week 21-22）

| 资料 | 说明 |
|:---|:---|
| [Redis 官方文档](https://redis.io/docs/) + [redis-py](https://redis-py.readthedocs.io/) | 缓存 / 消息队列 / 分布式锁 |
| [Kubernetes 官方教程](https://kubernetes.io/zh-cn/docs/tutorials/) | 容器编排，Pod / Service / Deployment |
| [Helm 文档](https://helm.sh/zh/docs/) | K8s 包管理器，简化部署配置 |
| [《数据密集型应用系统设计》(DDIA)](https://book.douban.com/subject/30329536/) | 分布式系统圣经，理解一致性 / 分区 / 复制 |

## Phase 8：综合项目（Week 23-28）

综合运用以上所有资料，按需查阅。重点参考 LangGraph + FastAPI + PostgreSQL + Docker + K8s 相关文档。

---

## 推荐社区

| 社区 | 用途 |
|:---|:---|
| [GitHub](https://github.com/) | 看源码、提 Issue、参与开源项目 |
| [LangChain Discord](https://discord.gg/langchain) | LangChain / LangGraph 技术交流 |
| [Reddit r/LocalLLaMA](https://www.reddit.com/r/LocalLLaMA/) | 本地大模型部署和调优讨论 |
| [掘金](https://juejin.cn/) | 中文技术社区，AI 应用开发和后端架构文章 |

## 参考项目

| 项目 | 说明 |
|:---|:---|
| [PrivateGPT](https://github.com/zylon-ai/private-gpt) | 完全私有化的 RAG 系统，支持本地 LLM |
| [Quivr](https://github.com/QuivrHQ/quivr) | 第二大脑 RAG 应用，功能完善的参考实现 |
| [Open WebUI](https://github.com/open-webui/open-webui) | 本地 LLM 前端，支持 Ollama / OpenAI 兼容 API |
