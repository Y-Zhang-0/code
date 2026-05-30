# 学习资料推荐

> 原则：每阶段只列 1-2 个核心资料，避免资料过多导致选择困难

---

## Phase 1：Python 基础

| 类型 | 资料 | 说明 |
|:---|:---|:---|
| 视频 | [黑马程序员 Python 入门教程](https://www.bilibili.com/video/BV1qW4y1a7fU) | B站免费，适合零基础 |
| 文档 | [Python 官方教程（中文）](https://docs.python.org/zh-cn/3/tutorial/) | 权威，可查阅 |
| 练习 | [Exercism Python Track](https://exercism.org/tracks/python) | 每天做 1-2 道题巩固 |

---

## Phase 2：LLM API + Prompt

| 类型 | 资料 | 说明 |
|:---|:---|:---|
| 官方文档 | [OpenAI API Reference](https://platform.openai.com/docs/api-reference) | 最权威 |
| 官方文档 | [智谱 AI 文档](https://open.bigmodel.cn/dev/howuse/model) | 国内 API 参考 |
| 课程 | [DeepLearning.AI - ChatGPT Prompt Engineering](https://www.deeplearning.ai/short-courses/chatgpt-prompt-engineering-for-developers/) | 免费，吴恩达出品，1-2天看完 |
| 中文课程 | [吴恩达提示词工程（中译）](https://github.com/datawhalechina/prompt-engineering-for-developers) | 上面课程的中文版 |

---

## Phase 3：Redis 与缓存

| 类型 | 资料 | 说明 |
|:---|:---|:---|
| 视频 | [黑马程序员 Redis 入门到精通](https://www.bilibili.com/video/BV1cr4y1671t) | B站免费，适合入门 |
| 文档 | [Redis 官方文档](https://redis.io/docs/) + [redis-py 文档](https://redis-py.readthedocs.io/) | 权威参考 |
| 实践 | [Redis University](https://university.redis.com/) | 免费认证课程 |

---

## Phase 4：RAG 系统

| 类型 | 资料 | 说明 |
|:---|:---|:---|
| 框架文档 | [LangChain 官方文档](https://python.langchain.com/docs/introduction/) | 主要框架 |
| 视频 | [LangChain 中文教程（B站）](https://www.bilibili.com/video/BV1zu411P7mq) | 有中文解说 |
| 课程 | [DeepLearning.AI - LangChain Chat with Your Data](https://www.deeplearning.ai/short-courses/langchain-chat-with-your-data/) | 免费，RAG 专项 |
| 向量库 | [ChromaDB 文档](https://docs.trychroma.com/) | 本地向量数据库 |

---

## Phase 5：Celery 与异步任务

| 类型 | 资料 | 说明 |
|:---|:---|:---|
| 文档 | [Celery 官方文档 - First Steps](https://docs.celeryq.dev/en/stable/getting-started/first-steps-with-celery.html) | 官方入门教程 |
| 视频 | [FastAPI + Celery 实战（B站）](https://www.bilibili.com/video/BV1N54y1z7fH) | 中文讲解 |
| 监控 | [Flower 文档](https://flower.readthedocs.io/) | Celery 监控面板 |

---

## Phase 6：Agent 系统

| 类型 | 资料 | 说明 |
|:---|:---|:---|
| 框架文档 | [LangGraph 官方文档](https://langchain-ai.github.io/langgraph/) | **主线**，LangChain 官方推荐 Agent 框架 |
| 课程 | [DeepLearning.AI - AI Agents in LangGraph](https://www.deeplearning.ai/short-courses/ai-agents-in-langgraph/) | 免费，LangGraph 专项 |
| 框架 | [CrewAI 文档](https://docs.crewai.com/) | 多 Agent 框架，了解即可 |
| 论文(选读) | [ReAct: Synergizing Reasoning and Acting](https://arxiv.org/abs/2210.03629) | Agent 原理论文 |

---

## Phase 7：工程化、并发与分布式

| 类型 | 资料 | 说明 |
|:---|:---|:---|
| 框架文档 | [FastAPI 官方文档](https://fastapi.tiangolo.com/zh/) | 有中文版 |
| Docker | [Docker 官方入门教程](https://docs.docker.com/get-started/) | 分步骤很清晰 |
| 视频 | [Docker 入门（B站·狂神说）](https://www.bilibili.com/video/BV1og4y1q7M4) | 中文讲解 |
| 本地模型 | [Ollama 官网](https://ollama.ai/) | 本地运行 LLM，开发必备 |
| 测试 | [pytest 官方文档](https://docs.pytest.org/) | Python 测试框架 |
| CI/CD | [GitHub Actions 文档](https://docs.github.com/zh/actions) | 自动化工作流 |
| 并发编程 | [Python asyncio 深度解析（B站·技术蛋老师）](https://www.bilibili.com/video/BV1oa411b7c9) | asyncio 原理讲解 |
| 书籍 | 《Python 并发编程实战》（O'Reilly） | 有中文版，系统学习 |
| 分布式概念 | [小林 coding - 图解分布式](https://xiaolincoding.com/) | 中文入门友好 |
| 课程（选学）| [MIT 6.824 Distributed Systems](https://pdos.csail.mit.edu/6.824/) | 了解概念足够，不用全学 |

---

## Phase 8：综合项目

参考 Phase 4-7 的资料，综合运用。

---

## 推荐社区

| 社区 | 说明 |
|:---|:---|
| GitHub | 看优秀开源项目是最好的学习方式 |
| LangChain Discord | 官方社区，有问题可以提问 |
| 掘金 / 少数派 | 中文技术分享 |
| Reddit r/LocalLLaMA | 英文社区，前沿信息 |

---

## 参考项目（学习时可以对照阅读）

| 项目 | 说明 | GitHub |
|:---|:---|:---|
| PrivateGPT | 本地 RAG 完整实现 | github.com/zylon-ai/private-gpt |
| Quivr | 生产级 RAG 服务 | github.com/QuivrHQ/quivr |
| Open WebUI | LLM 前端界面 | github.com/open-webui/open-webui |
| AutoGPT | 早期 Agent 项目 | github.com/Significant-Gravitas/AutoGPT |
