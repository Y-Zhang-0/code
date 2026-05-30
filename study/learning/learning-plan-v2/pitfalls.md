# 常见坑点与解决方案

> 收录 AI 应用开发 + 后端架构学习中最容易踩的坑，提前了解少走弯路

---

## 1. API Key 泄漏

**现象**：API Key 被提交到 Git 仓库，产生安全风险和意外计费。

**原因**：Key 硬编码在源码中，或 `.env` 文件未被 `.gitignore` 忽略。

**解决**：所有密钥放入 `.env` 文件，`.gitignore` 中添加 `.env`。项目初始化时第一件事就是配置 `.gitignore`。已泄漏的 Key 必须立即轮换（revoke + regenerate）。

## 2. 对话历史无限增长

**现象**：多轮对话后报错 `context length exceeded` 或响应变慢。

**原因**：每次请求携带完整历史消息，token 数超过模型上下文窗口限制。

**解决**：实现滑动窗口（保留最近 N 轮）或摘要压缩（定期将旧对话总结为摘要）。发送前用 `tiktoken` 预估 token 数，超限时主动截断。

## 3. Embedding 模型首次下载慢

**现象**：首次运行时卡在模型下载，甚至超时失败。

**原因**：HuggingFace 模型仓库在国内访问不稳定。

**解决**：设置 HuggingFace 镜像 `export HF_ENDPOINT=https://hf-mirror.com`。或提前用 `huggingface-cli download` 下载到本地缓存目录。

## 4. RAG 检索不到正确内容

**现象**：问答结果与文档内容无关，检索得分低。

**原因**：可能出现在链路的任何环节。

**解决**：按以下顺序逐步排查：
1. **导入**：确认文档是否成功解析和存入向量库（检查文档数量）
2. **检索**：直接调用向量库查询，确认是否能召回相关文档
3. **分块**：检查分块大小是否合理，关键信息是否被截断
4. **Prompt**：检查系统提示词是否正确引导模型使用检索结果
5. **模型**：换用更强的模型测试，排除模型能力问题

## 5. Agent 无限循环

**现象**：Agent 反复调用工具，不输出最终结果，消耗大量 token。

**原因**：缺少终止条件，模型无法判断何时停止。

**解决**：必须设置 `max_iterations` 上限。在系统提示词中明确告知模型何时应该给出最终答案。添加循环检测逻辑（如连续相同工具调用超过 N 次则强制终止）。

## 6. 流式输出乱码

**现象**：SSE 流式响应中出现乱码或截断字符。

**原因**：UTF-8 多字节字符被 chunk 边界截断。

**解决**：服务端设置 `Content-Type: text/event-stream; charset=utf-8`。客户端使用 `TextDecoder` 处理，或在服务端按完整 token 边界切割。

## 7. 虚拟环境混乱

**现象**：`import` 报错、版本冲突、全局包污染。

**原因**：多个项目共用全局 Python 环境，依赖版本互相覆盖。

**解决**：每个项目单独创建 `venv`（`python -m venv .venv`）。激活后确认 `which python` 指向项目目录。IDE 中设置解释器路径为项目 `.venv`。

## 8. Docker 构建慢

**现象**：每次修改代码后 `docker build` 耗时很长。

**原因**：Dockerfile 中依赖安装层写在代码复制层之后，导致每次改代码都重新安装依赖。

**解决**：调整 Dockerfile 层顺序——先复制 `requirements.txt` 并安装依赖，再复制源码。利用 Docker 缓存机制，依赖不变时跳过安装步骤。

## 9. ChromaDB 数据丢失

**现象**：重启服务后向量库中的文档消失。

**原因**：使用了 `EphemeralClient`（内存模式），数据不持久化。

**解决**：使用 `PersistentClient(path="./chroma_db")` 持久化到磁盘。Docker 部署时挂载数据目录为 Volume。

## 10. LangChain 版本不兼容

**现象**：升级 LangChain 后大量 `ImportError` 或 `DeprecationWarning`。

**原因**：LangChain 0.3+ 重构了包结构，社区包拆分到 `langchain-community`、`langchain-openai` 等独立包。

**解决**：查阅 [迁移指南](https://python.langchain.com/docs/versions/v0_3/)，使用新 import 路径。锁定版本号（`pip freeze > requirements.txt`），升级前先在分支上测试。

## 11. 用错参照系

**现象**：学习方向迷茫，不清楚该投入 AI 还是传统后端。

**原因**：AI 应用开发和后端架构师是两条不同路线，技能树有交叉但侧重不同。

**解决**：明确自己的主线目标。本学习计划的定位是 **AI 应用开发为主线，后端架构能力为加分项**。后端知识在 AI 项目中自然融入（API 服务化、部署运维、数据库），不需要单独刷后端八股。

## 12. Redis 集群连接错误

**现象**：连接 Redis 集群时报 `MOVED` 或 `CROSSSLOT` 错误。

**原因**：使用了单机模式的 `Redis()` 客户端连接集群模式的 Redis。

**解决**：集群模式使用 `RedisCluster()` 客户端。注意区分 Sentinel 模式、Cluster 模式和 Standalone 模式，三者客户端不同。操作多个 key 时需确保在同一 slot（使用 hash tag `{prefix}`）。

## 13. Celery Worker 启动后不执行任务

**现象**：任务发送成功但 Worker 端无日志、无执行。

**原因**：Broker URL 配置错误，或 Worker 启动时未发现任务模块（task autodiscover 失败）。

**解决**：检查 Broker URL（Redis/RabbitMQ）是否可达。确认 `celery -A app worker` 启动参数中的 app 路径正确。检查 `include` 或 `autodiscover_tasks()` 是否覆盖了任务所在模块。启动时加 `--loglevel=debug` 查看详细日志。

## 14. PostgreSQL 连接池耗尽

**现象**：高并发时报 `too many connections` 或请求长时间等待。

**原因**：默认连接池参数过小，或连接泄漏（未正确释放）。

**解决**：调整 SQLAlchemy 连接池参数——`pool_size`（常驻连接数）、`max_overflow`（临时溢出连接数）、`pool_recycle`（连接存活时间，避免被数据库端超时断开）。确保使用 `with session` 上下文管理器自动归还连接。

## 15. K8s Pod CrashLoopBackOff

**现象**：Pod 反复重启，状态卡在 `CrashLoopBackOff`。

**原因**：通常是以下几种之一——资源限制（OOMKilled）、健康检查配置不当、环境变量缺失导致启动失败。

**解决**：按以下顺序排查：
1. `kubectl logs <pod>` 查看容器日志
2. `kubectl describe pod <pod>` 查看事件（Events）
3. 检查 `resources.limits.memory` 是否过小
4. 检查 `livenessProbe` / `readinessProbe` 配置是否合理
5. 检查 ConfigMap / Secret 中的环境变量是否完整

## 16. MCP Server 连接失败

**现象**：MCP 客户端无法连接 Server，报超时或协议错误。

**原因**：传输层配置不匹配——stdio 模式和 SSE 模式的连接方式完全不同。

**解决**：确认 Server 和 Client 使用相同的传输协议。stdio 模式下确保进程路径和参数正确。SSE 模式下检查端口、URL 路径和 CORS 配置。查看 Server 端日志确认是否成功启动监听。

---

## 调试技巧总结

遇到问题时遵循 **五步排查法**：

1. **复现**：找到稳定的最小复现步骤，确认问题边界
2. **定位**：缩小范围——是前端/后端/数据库/外部服务？用二分法逐层排除
3. **假设**：基于日志和现象提出假设，一次只验证一个
4. **验证**：修改后测试，确认假设是否成立
5. **记录**：将问题和解决方案记录下来（写入本文件或项目 CLAUDE.md）

## 有效提问模板

向社区或 AI 提问时，提供以下信息能大幅提高获得有效回答的概率：

```
## 环境
- OS / Python 版本 / 相关库版本

## 问题描述
- 期望行为 vs 实际行为

## 复现步骤
1. ...
2. ...

## 已尝试
- 尝试了什么，结果如何

## 错误日志
（关键日志片段，脱敏后粘贴）
```

## Git 工作流规范

**分支策略**：
- `main` — 稳定分支，保护分支
- `feat/<name>` — 功能分支，从 main 创建
- `fix/<name>` — 修复分支
- `chore/<name>` — 杂项（依赖更新、配置调整）

**Commit 规范**：
- 格式：`<type>: <description>`
- type 取值：`feat` / `fix` / `refactor` / `test` / `docs` / `chore`
- 示例：`feat: implement RAG retrieval pipeline`

**.gitignore 必须包含**：
- `.env` / `.env.*` — 环境变量和密钥
- `__pycache__/` / `*.pyc` — Python 编译缓存
- `.venv/` / `venv/` — 虚拟环境
- `chroma_db/` — 向量库本地数据
- `node_modules/` — 前端依赖
- `.idea/` / `.vscode/` — IDE 配置
