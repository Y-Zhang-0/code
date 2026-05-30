# Phase 4：生产化工程

> **时间**：Week 10-12（D64-D84，78 小时）  
> **前提**：Phase 3 RAG API + Redis 缓存完成  
> **目标**：将 RAG 应用容器化部署，建立数据库持久化、测试与 CI/CD 体系，实现安全认证  
> **融合设计**：Docker/PostgreSQL/CI/CD 都围绕已有的 RAG API 应用进行，不是抽象学习

---

## Week 10 (D64-D70)：Docker 容器化

### D64：Docker 基础（3h）

**学习内容**：
- Docker 核心概念：镜像（Image）、容器（Container）、仓库（Registry）
- 基础命令：`docker run`、`docker ps`、`docker images`、`docker logs`、`docker exec`
- 容器生命周期管理：启动、停止、重启、删除
- 数据卷（Volume）与网络（Network）基础概念
- Docker Hub 镜像拉取与版本管理

**检查点**：
- [ ] 成功运行 `docker run hello-world` 验证安装
- [ ] 启动 Redis 容器并通过 `redis-cli` 连接测试
- [ ] 理解镜像分层机制与容器隔离原理

---

### D65：Dockerfile 编写（3h）

**学习内容**：
- Dockerfile 指令详解：`FROM`、`COPY`、`RUN`、`CMD`、`ENTRYPOINT`、`WORKDIR`、`EXPOSE`、`ENV`、`ARG`
- 多阶段构建（Multi-stage Build）：构建阶段与运行阶段分离，减小最终镜像体积
- 缓存层优化策略：指令顺序对构建缓存的影响，依赖安装与源码复制的正确顺序
- `.dockerignore` 文件编写：排除无关文件加速构建上下文传输
- 基础镜像选择：`python:3.12-slim` vs `python:3.12-alpine` 的权衡

**检查点**：
- [ ] 为 RAG API 编写 Dockerfile，成功构建镜像
- [ ] 使用多阶段构建，最终镜像体积控制在合理范围
- [ ] 验证缓存层优化效果：修改源码后重新构建仅重建最后几层

---

### D66：Docker Compose 多服务编排（3h）

**学习内容**：
- Docker Compose 核心概念：服务（services）、网络（networks）、卷（volumes）
- `docker-compose.yml` 编写：多服务定义（app + redis + chroma）
- 服务间依赖：`depends_on` 与 `healthcheck` 配合实现正确启动顺序
- 数据持久化：named volumes 挂载，容器重启后数据不丢失
- 重启策略（restart policy）：`always`、`unless-stopped`、`on-failure` 的适用场景

**检查点**：
- [ ] 编写 `docker-compose.yml` 定义至少三个服务
- [ ] `docker compose up` 一键启动所有服务并正常通信
- [ ] 验证服务重启后持久化数据仍然存在

---

### D67：.dockerignore + 镜像瘦身 + Docker 网络（3h）

**学习内容**：
- `.dockerignore` 最佳实践：排除 `.git`、`__pycache__`、`node_modules`、测试数据等
- 镜像瘦身技巧：减少 RUN 层数、清理缓存、使用 slim 基础镜像、不安装调试工具
- `docker image inspect` 分析镜像层结构与大小分布
- Docker 网络模型：bridge、host、none 三种模式的区别与适用场景
- 自定义网络下的服务名 DNS 解析机制：容器间通过服务名互相访问

**检查点**：
- [ ] `.dockerignore` 覆盖所有不必要文件，构建上下文大小显著降低
- [ ] 对比优化前后的镜像大小，确认瘦身效果
- [ ] 理解自定义 bridge 网络中容器间通过服务名通信的原理

---

### D68：实战周五 -- 容器化 RAG API（3h）

**学习内容**：
- 将 Phase 3 完成的 RAG API 项目完整容器化
- 编写生产级 Dockerfile：多阶段构建、非 root 用户运行、健康检查端点
- 编写 Docker Compose 初稿：app + redis + chroma 三服务协同
- 环境变量管理：`.env` 文件与 `environment` 配置项的配合使用
- 端口映射与服务暴露策略：仅对外暴露必要端口

**检查点**：
- [ ] `docker compose up` 启动 RAG API，API 端点正常响应
- [ ] 文档上传、检索、问答功能在容器环境下全部验证通过
- [ ] Redis 缓存在容器环境中正常工作

---

### D69 Sat：实战 -- 完整多服务 Docker Compose（8h）

**学习内容**：
- 扩展 Docker Compose 为完整四服务架构：app + redis + chroma + postgres
- PostgreSQL 容器配置：初始化脚本挂载、数据卷持久化、环境变量设置
- 服务健康检查（healthcheck）编写：每个服务的探活方式（HTTP / TCP / 命令）
- `depends_on` + `condition: service_healthy` 实现严格启动顺序
- 开发环境 vs 生产环境 Compose 文件拆分：`docker-compose.yml` + `docker-compose.override.yml`
- 日志查看与调试：`docker compose logs -f`、进入容器排查问题

**检查点**：
- [ ] 四服务全部启动且健康检查通过
- [ ] PostgreSQL 数据在容器重启后持久化
- [ ] 服务间网络互通，app 可访问 redis、chroma、postgres
- [ ] 开发/生产配置文件分离，环境变量正确覆盖

---

### D70 Sun：实战 -- Ollama 本地模型集成（8h）

**学习内容**：
- Ollama 安装与基础使用：`ollama run`、`ollama pull`、模型管理
- Ollama Docker 部署：GPU 直通配置（NVIDIA Container Toolkit）、CPU 回退方案
- 将 Ollama 作为第五个服务加入 Docker Compose：网络配置、模型持久化卷
- RAG API 适配：LLM 调用从云端 API 切换为本地 Ollama 端点
- 零费用开发环境验证：完全离线运行 RAG 问答流程
- 模型选择策略：根据硬件条件选择合适的模型大小（7B/13B/34B）

**检查点**：
- [ ] Ollama 容器成功启动并加载至少一个模型
- [ ] RAG API 通过 Ollama 完成问答，无需外部 API 密钥
- [ ] `docker compose up` 一行命令启动包含 Ollama 的全栈环境
- [ ] 记录 GPU/CPU 模式下的推理延迟差异

---

## Week 11 (D71-D77)：PostgreSQL + CI/CD

### D71：PostgreSQL 基础（3h）

**学习内容**：
- PostgreSQL 通过 Docker 安装与启动，`psql` 命令行客户端使用
- SQL 基础操作：`CREATE TABLE`、`INSERT`、`SELECT`、`UPDATE`、`DELETE`
- 数据类型选择：`TEXT`、`INTEGER`、`TIMESTAMP`、`JSONB`、`UUID`
- 索引基础：B-tree 索引、创建索引、`EXPLAIN ANALYZE` 查看执行计划
- 与 SQLite 的关键差异：并发控制、权限体系、网络访问

**检查点**：
- [ ] 通过 Docker 启动 PostgreSQL 并用 `psql` 连接
- [ ] 完成基本 CRUD 操作并理解事务机制
- [ ] 创建索引并通过 `EXPLAIN ANALYZE` 对比查询性能变化

---

### D72：SQLAlchemy ORM（3h）

**学习内容**：
- SQLAlchemy 2.0 声明式模型定义：`DeclarativeBase`、`Mapped`、`mapped_column`
- 字段类型映射：Python 类型与数据库列类型的对应关系
- 关系定义：`relationship`、`ForeignKey`、一对多与多对多
- 异步会话管理：`async_sessionmaker`、`AsyncSession`、上下文管理器模式
- 基础 CRUD 操作：`session.add()`、`session.execute(select(...))`、`session.delete()`
- 与 FastAPI 集成：依赖注入提供数据库会话

**检查点**：
- [ ] 定义至少两个 ORM 模型并建立关系
- [ ] 通过异步会话完成 CRUD 操作
- [ ] 理解 `session.commit()` 与 `session.flush()` 的区别

---

### D73：Alembic 数据库迁移（3h）

**学习内容**：
- Alembic 初始化：`alembic init`、目录结构与配置文件解读
- 自动生成迁移脚本：`alembic revision --autogenerate -m "message"`
- 迁移执行与回滚：`alembic upgrade head`、`alembic downgrade -1`
- 迁移脚本审查：自动生成的脚本需要人工检查与修正的场景
- 迁移版本管理：线性历史 vs 分支合并、`alembic history` 查看版本链
- 生产环境迁移策略：先备份、灰度执行、回滚预案

**检查点**：
- [ ] 初始化 Alembic 并成功生成第一个迁移脚本
- [ ] 执行 `upgrade` 和 `downgrade` 验证双向迁移
- [ ] 修改模型后自动生成增量迁移并应用

---

### D74：数据库设计（3h）

**学习内容**：
- RAG 应用数据库表设计：用户表（users）、会话历史表（chat_sessions / messages）、文档元数据表（documents）、API 调用记录表（api_logs）
- 表关系设计：用户与会话一对多、会话与消息一对多、用户与文档一对多
- JSONB 字段的使用场景：存储灵活的元数据（文档属性、LLM 参数等）
- 索引策略：高频查询字段建索引、复合索引设计、避免过度索引
- 数据生命周期管理：历史数据归档策略、软删除 vs 硬删除

**检查点**：
- [ ] 完成至少四张表的 ER 图设计
- [ ] 所有表通过 Alembic 迁移创建成功
- [ ] 索引覆盖主要查询路径，`EXPLAIN ANALYZE` 验证命中

---

### D75：GitHub Actions CI/CD（3h）

**学习内容**：
- GitHub Actions 核心概念：Workflow、Job、Step、Runner
- CI 流水线设计：`.github/workflows/ci.yml` 编写
- 流水线阶段：代码检查（lint）-> 单元测试（test）-> 镜像构建（build）
- 矩阵构建（matrix strategy）：多 Python 版本测试
- Secrets 管理：API 密钥等敏感信息通过 GitHub Secrets 注入
- PR 保护规则：要求 CI 通过才能合并、要求 Code Review

**检查点**：
- [ ] 编写 `ci.yml` 并推送触发首次 CI 运行
- [ ] CI 流水线包含 lint、test、build 三个阶段
- [ ] 理解 `on.push` / `on.pull_request` 触发条件配置

---

### D76 Sat：实战 -- FastAPI + PostgreSQL 集成（8h）

**学习内容**：
- RAG API 集成 PostgreSQL：替代内存/文件存储，实现真正的数据持久化
- 会话持久化：用户提问与 AI 回答存入数据库，支持历史回溯
- 文档元数据存储：上传文件的名称、大小、类型、分块数、上传时间等记录到数据库
- API 调用记录：每次请求的耗时、Token 用量、状态码存入日志表
- 数据库连接池配置：`pool_size`、`max_overflow`、`pool_timeout` 参数调优
- 数据一致性保障：向量库与关系库的双写事务处理策略

**检查点**：
- [ ] RAG API 的会话历史可从数据库查询，容器重启后数据不丢失
- [ ] 文档上传后元数据同步写入 PostgreSQL
- [ ] API 调用记录表有数据，可按时间范围查询
- [ ] 数据库连接池参数合理，无连接泄漏

---

### D77 Sun：实战 -- CI/CD 流水线 + 代码覆盖率（8h）

**学习内容**：
- 完善 CI/CD 流水线：增加代码覆盖率收集（pytest-cov + coverage report）
- 覆盖率阈值设置：`--cov-fail-under` 设定最低覆盖率门槛
- PR 保护规则配置：分支保护、必须通过 CI、必须有 Review
- Docker 镜像自动构建：CI 中执行 `docker build` 验证镜像可构建
- 测试数据库隔离：CI 环境中使用独立的 PostgreSQL 服务容器
- 代码质量工具集成：ruff（lint）+ black（format）+ mypy（类型检查）

**检查点**：
- [ ] CI 流水线完整运行：lint -> test -> coverage -> build
- [ ] 代码覆盖率报告自动生成，覆盖率达到设定阈值
- [ ] PR 保护规则生效：CI 失败时无法合并
- [ ] Docker 镜像在 CI 中构建成功

---

## Week 12 (D78-D84)：日志 + 安全 + Buffer 3

### D78：结构化日志（3h）

**学习内容**：
- Python logging 模块：Logger、Handler、Formatter、Filter 的层级关系
- structlog 库：结构化日志输出，JSON 格式化，链式处理器（processors）
- 日志级别策略：DEBUG/INFO/WARNING/ERROR/CRITICAL 在不同环境的配置
- AI 应用专属日志字段：Token 使用量、模型名称、推理延迟、检索结果数量
- 日志与请求追踪：通过 request_id 串联同一请求的所有日志
- 日志输出目标：控制台（开发）vs 文件（生产）vs 日志聚合服务（运维）

**检查点**：
- [ ] RAG API 集成 structlog，所有日志输出为 JSON 格式
- [ ] 每次问答请求记录 Token 用量和响应延迟
- [ ] 日志包含 request_id，可追踪完整请求链路

---

### D79：JWT 认证（3h）

**学习内容**：
- JWT（JSON Web Token）原理：Header、Payload、Signature 三段结构
- 注册与登录流程：密码哈希（passlib + bcrypt）、Token 生成（python-jose）
- Token 验证：FastAPI 依赖注入实现认证中间件，解码并校验过期时间
- Access Token 与 Refresh Token 双令牌机制：短期访问 + 长期刷新
- 受保护路由：未认证请求返回 401，Token 过期返回 401 + 明确错误信息

**检查点**：
- [ ] 实现用户注册与登录接口，返回 JWT Token
- [ ] 受保护的 API 端点拒绝无 Token 请求
- [ ] Token 过期后自动失效，需重新登录或使用 Refresh Token

---

### D80：RBAC 权限控制（3h）

**学习内容**：
- 基于角色的访问控制（Role-Based Access Control）设计思路
- 用户角色枚举：`UserRole`（admin / user / readonly）
- 权限装饰器实现：`require_role` 装饰器检查当前用户角色是否满足端点要求
- 管理员专属路由：用户管理、系统配置、数据清理等操作仅 admin 可执行
- 角色与 JWT 集成：将用户角色信息编码到 Token 的 Payload 中
- 权限粒度设计：粗粒度（角色级）vs 细粒度（资源级）的取舍

**检查点**：
- [ ] 用户模型包含角色字段，注册时默认为普通用户
- [ ] admin-only 路由对普通用户返回 403
- [ ] `require_role` 装饰器可复用于任意受保护端点

---

### D81：安全加固（3h）

**学习内容**：
- CORS 配置：`CORSMiddleware` 设置允许的源、方法、头部，生产环境限制具体域名
- SQL 注入防护：ORM 参数化查询天然防注入，原生 SQL 使用绑定参数
- Refresh Token 安全：HttpOnly Cookie 存储、Token 轮换（Rotation）、黑名单机制
- HTTPS 部署要点：TLS 证书配置、Nginx 反向代理 SSL 终结
- XSS 防护：输入清洗（sanitization）、输出编码、Content-Security-Policy 头
- 输入验证：Pydantic 模型校验、文件上传类型与大小限制、速率限制（rate limiting）

**检查点**：
- [ ] CORS 配置仅允许指定来源访问
- [ ] 所有用户输入经过 Pydantic 校验，非法输入返回 422
- [ ] Refresh Token 通过 HttpOnly Cookie 传输，不暴露给前端 JS
- [ ] 文件上传端点限制文件类型和大小

---

### D82：性能分析（3h）

**学习内容**：
- Python 性能分析工具：`cProfile` 函数级耗时统计、`snakeviz` 可视化火焰图
- `py-spy` 生产环境采样分析：无需修改代码，attach 到运行中的进程
- AI 管线瓶颈识别：嵌入计算、向量检索、LLM 推理各阶段耗时拆分
- 数据库查询性能：慢查询日志、N+1 问题识别、批量查询优化
- 内存分析：`tracemalloc` 追踪内存分配，识别内存泄漏
- 优化决策框架：先测量再优化、关注热点路径、避免过早优化

**检查点**：
- [ ] 使用 cProfile 分析一次完整的 RAG 问答流程，识别耗时最长的环节
- [ ] 用 py-spy 对运行中的容器化应用进行采样分析
- [ ] 基于分析结果提出至少两项具体的优化建议
- [ ] 记录各阶段耗时基线数据，为后续优化提供对比参照

---

### D83 Sat：Buffer 3 -- Phase 4 复盘 + Docker 全栈验收（8h）

**学习内容**：
- Phase 4 知识点回顾与查漏补缺
- Docker 全栈验收：从零开始 `git clone` + `docker compose up`，验证所有服务正常运行
- 容器化最佳实践检查清单：非 root 用户、健康检查、日志输出到 stdout、无硬编码配置
- 补齐 Week 10-11 未完成的实战内容
- 编写 Docker 部署文档：环境要求、配置说明、启动步骤、常见问题

**检查点**：
- [ ] 全新环境下 `docker compose up` 一行命令启动全栈服务
- [ ] 所有 API 端点在容器环境中功能验证通过
- [ ] Dockerfile 和 Compose 文件遵循最佳实践
- [ ] 容器资源占用合理，无明显资源浪费

---

### D84 Sun：Buffer 3 -- CI/CD + 安全认证验收（8h）

**学习内容**：
- CI/CD 流水线端到端验收：提交代码 -> 触发 CI -> lint + test + build 全部通过
- 安全认证端到端验收：注册 -> 登录 -> 获取 Token -> 访问受保护资源 -> Token 刷新
- RBAC 验收：不同角色用户访问不同端点的权限验证
- 集成测试补充：编写覆盖认证 + 数据库 + 缓存的集成测试用例
- Phase 4 成果整理与文档归档

**检查点**：
- [ ] GitHub Actions CI 流水线稳定运行，PR 保护规则生效
- [ ] JWT 认证流程完整可用，Token 过期与刷新逻辑正确
- [ ] RBAC 权限控制按预期工作，admin/user/readonly 角色区分明确
- [ ] 代码覆盖率达到设定阈值

---

## 里程碑 4

**容器化 RAG API + PostgreSQL 持久化 + GitHub Actions CI/CD + JWT 认证 + 结构化日志**

验收标准：
- [ ] 一行 `docker compose up` 命令启动全栈服务（app + redis + chroma + postgres + ollama）
- [ ] PostgreSQL 持久化会话历史、文档元数据、API 调用记录
- [ ] GitHub Actions CI/CD 流水线自动执行 lint + test + coverage + build
- [ ] JWT 认证 + RBAC 权限控制保护所有 API 端点
- [ ] structlog 结构化日志记录请求链路与 AI 指标
- [ ] 代码覆盖率达到设定阈值，PR 保护规则生效

---

## 下阶段预告

**Phase 5：前端与全栈整合**将基于 Phase 4 的容器化后端，构建前端交互界面。学习 HTML/CSS/JavaScript 基础、React 框架、前后端联调，最终实现一个完整的 RAG 知识库问答 Web 应用。重点包括组件化开发、状态管理、API 对接、以及前端容器化与全栈 Docker Compose 部署。
