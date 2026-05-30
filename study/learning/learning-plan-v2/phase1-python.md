# Phase 1：Python 速通（全栈开发者版）

> **时间**：Week 1（D1-D7，26 小时）
> **前提**：3.5 年 Java/Node.js/Vue 经验
> **目标**：掌握 Python AI 开发必备的特有语法和工具链

---

## 跳过内容（已掌握）

以下概念在 Java/Node.js 中已有对等物，无需从零学习：

- 变量、条件、循环、函数定义等基础语法
- 面向对象编程（类、继承、多态）
- 异常处理（try/except 对应 try/catch）
- 模块导入（import 机制与 Node.js require/ES Module 类似）
- 字典/列表操作（对应 Java Map/List、JS Object/Array）
- HTTP 请求/响应模型（REST API 概念）
- JSON 序列化/反序列化
- 基本的 Git 工作流
- 命令行参数解析的基本概念
- 单元测试的基本理念（断言、隔离、覆盖率）

---

## Day 1（周一，2h）：类型注解 + Pydantic + 推导式 + pathlib

### 学习内容

**类型注解（Type Hints）**

Python 是动态类型语言，但 3.5+ 引入了渐进式类型注解系统。需要掌握：基本类型标注（`int`, `str`, `bool`）、容器类型（`list[str]`, `dict[str, int]`）、可选类型（`Optional`、`X | None`）、`Union` 类型、`TypeAlias`、以及 `typing` 模块中常用的 `Any`、`Callable`、`TypeVar` 等。重点理解类型注解在 Python 中**不强制执行**，仅供 IDE 和类型检查器（mypy）使用，与 Java/TypeScript 的编译期强制检查有本质区别。

**Pydantic 数据模型**

Pydantic 是 FastAPI 的核心依赖，用于数据验证和序列化。需要掌握：`BaseModel` 定义、字段类型与默认值、`Field()` 约束（`min_length`、`ge`、`pattern` 等）、嵌套模型、`model_validate()` / `model_dump()` 方法、自定义验证器（`@field_validator`、`@model_validator`）。理解 Pydantic 在运行时执行类型校验这一特性——它弥补了 Python 类型注解不强制的缺陷。

**f-string 格式化**

Python 3.6+ 的字符串插值语法，对应 JS 模板字符串和 Java 的 `String.format()`。需要掌握：基本插值、表达式求值、格式规范（对齐、精度、千分位）、f-string 中调用方法和使用条件表达式。

**推导式（Comprehensions）**

Python 最具特色的语法之一。需要掌握：列表推导式、字典推导式、集合推导式、带条件过滤的推导式、嵌套推导式。理解推导式与 Java Stream API 和 JS 的 `map/filter` 在思维模型上的对应关系，但语法更简洁。

**pathlib 路径操作**

Python 3.4+ 引入的面向对象路径库，替代 `os.path`。需要掌握：`Path` 对象创建、路径拼接（`/` 运算符）、文件读写（`read_text()` / `write_text()`）、遍历目录（`glob()`、`iterdir()`）、路径属性（`suffix`、`stem`、`parent`）。在 AI 项目中频繁用于文件加载和数据管道。

### 与 Java/Node.js 的对比

| 概念 | Java | Node.js | Python |
|:-----|:-----|:--------|:-------|
| 类型系统 | 编译期强制 | TypeScript 编译期检查 | 运行时不强制，需 mypy 或 Pydantic |
| 数据验证 | Bean Validation / Hibernate Validator | Joi / Zod / class-validator | Pydantic（运行时校验 + 序列化一体） |
| 字符串插值 | `String.format()` / `+` 拼接 | 模板字符串 `` `${}` `` | f-string `f"{}"` |
| 集合变换 | Stream API (`stream().map().filter()`) | `Array.map().filter()` | 推导式 `[x for x in ...]` |
| 路径操作 | `java.nio.file.Path` | `path` 模块 | `pathlib.Path`（运算符重载拼接） |

### 检查点

- [ ] 能为函数参数和返回值添加类型注解，包括 `Optional`、`Union`、容器类型
- [ ] 能定义 Pydantic `BaseModel`，包含字段约束和自定义验证器
- [ ] 能使用 `model_validate()` 从字典创建模型，使用 `model_dump()` 序列化
- [ ] 能用 f-string 实现带格式控制的字符串输出
- [ ] 能用列表/字典推导式替代等价的 `for` 循环 + `append` 模式
- [ ] 能用 `pathlib.Path` 完成路径拼接、文件读写、目录遍历

---

## Day 2（周二，2h）：async/await + 装饰器

### 学习内容

**Python 异步编程模型**

Python 的 `async/await` 语法与 Node.js 的形式相似，但底层模型差异巨大。需要掌握：`async def` 定义协程函数、`await` 等待可等待对象、`asyncio.run()` 作为入口点启动事件循环、`asyncio.gather()` 并发执行多个协程、`asyncio.create_task()` 创建任务。重点理解 Python 的异步是**显式的**——必须手动创建和运行事件循环，而 Node.js 的事件循环是隐式启动的。Python 中同步代码和异步代码的边界非常清晰，混用时需要特别注意（如在异步函数中调用同步阻塞 IO 会阻塞整个事件循环）。

**asyncio 核心概念**

理解事件循环、协程、任务、Future 的关系。掌握 `asyncio.sleep()`（对比 `time.sleep()` 的阻塞行为）、`asyncio.Queue` 异步队列、`asyncio.Semaphore` 并发控制、`asyncio.wait_for()` 超时控制。了解 `async for` 和 `async with` 语法用于异步迭代器和异步上下文管理器。

**装饰器（Decorators）**

Python 装饰器是 AI 开发中的高频工具。需要掌握：装饰器的本质（高阶函数，接收函数返回函数）、使用 `@` 语法糖应用装饰器、`functools.wraps` 保留被装饰函数的元信息、带参数的装饰器（三层嵌套）、`@functools.lru_cache` 记忆化缓存（LLM 调用中常用于缓存结果）、类方法装饰器（`@staticmethod`、`@classmethod`、`@property`）。理解装饰器与 Java 注解（`@Annotation`）的区别——Python 装饰器在定义时**立即执行**并修改函数行为，而 Java 注解是元数据标记，需配合反射或框架读取。

**自定义装饰器场景**

在 AI 应用中常见的装饰器用途：重试逻辑（API 调用失败重试）、计时统计（监控推理耗时）、日志记录、权限验证、结果缓存。理解如何为异步函数编写装饰器（装饰器内部的 wrapper 也需要是 `async def`）。

### 与 Java/Node.js 的对比

| 概念 | Java | Node.js | Python |
|:-----|:-----|:--------|:-------|
| 异步模型 | CompletableFuture / 虚拟线程 | 隐式事件循环 + Promise | 显式事件循环 + 协程 |
| 事件循环 | 无（线程模型） | 自动启动，全局唯一 | 需 `asyncio.run()` 手动启动 |
| 并发等待 | `CompletableFuture.allOf()` | `Promise.all()` | `asyncio.gather()` |
| 装饰器 / 注解 | `@Annotation`（元数据标记） | 无原生支持（TC39 Stage 3） | `@decorator`（立即执行，修改行为） |
| 缓存 | Guava Cache / Spring `@Cacheable` | 手动实现或 node-cache | `@lru_cache`（标准库内置） |

### 检查点

- [ ] 能编写 `async def` 协程并用 `asyncio.run()` 执行
- [ ] 能用 `asyncio.gather()` 并发执行多个异步任务并收集结果
- [ ] 能解释 Python 与 Node.js 事件循环模型的核心差异
- [ ] 能编写带 `functools.wraps` 的自定义装饰器（同步和异步版本）
- [ ] 能正确使用 `@lru_cache` 缓存纯函数的计算结果
- [ ] 能识别在异步函数中调用同步阻塞代码的风险

---

## Day 3（周三，2h）：生成器 + 上下文管理器 + httpx

### 学习内容

**生成器（Generators）与 yield**

生成器是 Python 处理大数据流和 LLM 流式输出的核心机制。需要掌握：`yield` 关键字将函数变为生成器函数、生成器的惰性求值特性（按需生成值，不预先加载到内存）、`yield from` 委托生成器、生成器表达式（`(x for x in iterable)`）、异步生成器（`async def` + `yield`，用于流式接收 LLM 响应）。理解生成器与 Java 的 `Iterator` / `Stream` 和 JS 的 `function*` 的对应关系，但 Python 的生成器语法更简洁且在生态中使用更广泛。

**上下文管理器（Context Managers）**

`with` 语句是 Python 资源管理的标准模式。需要掌握：`with` 语句的执行流程（`__enter__` → 代码块 → `__exit__`）、内置上下文管理器（文件操作、线程锁、数据库连接）、`contextlib.contextmanager` 装饰器用 `yield` 简化自定义上下文管理器、`async with` 异步上下文管理器（数据库连接池、HTTP 会话）。在 AI 开发中，上下文管理器常用于管理 API 客户端生命周期、临时目录、数据库事务等。

**httpx 异步 HTTP 客户端**

httpx 是 Python 异步 HTTP 的现代选择，替代 `requests`（同步）和 `aiohttp`。需要掌握：同步和异步两种使用模式、`AsyncClient` 作为上下文管理器使用、请求方法（GET/POST/PUT/DELETE）、请求参数（headers、json、params、timeout）、流式响应（`aiter_lines()` / `aiter_bytes()`，用于接收 LLM 流式输出）、错误处理（`httpx.HTTPStatusError`、超时处理）、连接池复用。

### 与 Java/Node.js 的对比

| 概念 | Java | Node.js | Python |
|:-----|:-----|:--------|:-------|
| 惰性序列 | `Stream` API（一次性） | 无内置（需 generator 或 RxJS） | 生成器（可暂停/恢复） |
| 流式处理 | `InputStream` / Reactor Flux | `ReadableStream` / 事件监听 | `async for chunk in response.aiter_lines()` |
| 资源管理 | try-with-resources | 无标准模式（手动 finally） | `with` / `async with` 语句 |
| HTTP 客户端 | HttpClient / OkHttp / WebClient | fetch / axios | httpx（同步 + 异步统一 API） |

### 检查点

- [ ] 能编写生成器函数实现惰性数据生产，理解其内存优势
- [ ] 能编写异步生成器（`async def` + `yield`）模拟流式数据接收
- [ ] 能用 `contextlib.contextmanager` 创建自定义上下文管理器
- [ ] 能用 `httpx.AsyncClient` 作为异步上下文管理器发送 HTTP 请求
- [ ] 能用 `aiter_lines()` 处理流式 HTTP 响应
- [ ] 能解释生成器与列表的内存占用差异

---

## Day 4（周四，2h）：pytest 深入

### 学习内容

**pytest 核心机制**

pytest 是 Python 生态的事实标准测试框架。需要掌握：测试发现规则（`test_` 前缀文件和函数）、断言直接使用 `assert` 语句（无需 `assertEqual` 等方法）、pytest 的断言内省（失败时自动展示详细的变量值比较）。

**Fixtures 系统**

pytest 的依赖注入机制，远比 Java 的 `@Before/@After` 和 Node.js 的 `beforeEach` 灵活。需要掌握：`@pytest.fixture` 定义、fixture 的作用域（`function`、`class`、`module`、`session`）、fixture 之间的依赖组合、`yield` fixture（setup + teardown 一体化）、`conftest.py` 共享 fixture、`autouse` 自动应用 fixture、`tmp_path` 等内置 fixture。

**参数化测试**

`@pytest.mark.parametrize` 用一组数据驱动同一测试逻辑，等价于 Java 的 `@ParameterizedTest`。需要掌握：单参数和多参数的参数化、参数 ID 标识、与 fixture 结合使用。

**Mock 与 Monkeypatch**

需要掌握：`unittest.mock.patch` / `MagicMock` / `AsyncMock` 的使用、`monkeypatch` fixture（pytest 内置，用于临时修改环境变量、属性、字典等）、mock 外部 API 调用（LLM API、数据库）。理解 `monkeypatch` 与 `unittest.mock.patch` 的适用场景差异。

**pytest-asyncio**

测试异步代码的插件。需要掌握：`@pytest.mark.asyncio` 标记异步测试、异步 fixture 的定义、`asyncio_mode` 配置选项。

**TDD 思维**

理解在 AI 应用开发中 TDD 的实践：先定义 Agent 的输入输出契约，再实现逻辑；mock 外部依赖（LLM API、向量库）进行单元测试；集成测试使用轻量级替代（内存向量库、本地模型）。

### 与 Java/Node.js 的对比

| 概念 | Java (JUnit) | Node.js (Jest/Vitest) | Python (pytest) |
|:-----|:-------------|:----------------------|:----------------|
| 断言 | `assertEquals()` 等方法 | `expect().toBe()` 链式 | 原生 `assert`（自动内省） |
| 依赖注入 | `@Before` + 手动管理 | `beforeEach` + 手动管理 | `@pytest.fixture`（声明式注入） |
| 参数化 | `@ParameterizedTest` | `test.each()` | `@pytest.mark.parametrize` |
| Mock | Mockito | jest.mock / vi.mock | `unittest.mock` + `monkeypatch` |
| 异步测试 | 直接支持 | 直接支持 | 需 `pytest-asyncio` 插件 |

### 检查点

- [ ] 能编写 pytest 测试用例，使用 `assert` 进行断言并理解失败时的内省输出
- [ ] 能定义 `yield` fixture 实现 setup/teardown，并理解 fixture 作用域
- [ ] 能使用 `@pytest.mark.parametrize` 进行多组数据驱动测试
- [ ] 能使用 `monkeypatch` 临时修改环境变量和对象属性
- [ ] 能使用 `MagicMock` / `AsyncMock` mock 外部 API 调用
- [ ] 能编写异步测试函数并正确配置 `pytest-asyncio`
- [ ] 理解 `conftest.py` 的作用和 fixture 共享机制

---

## Day 5（周五，2h）：Python 包管理与项目配置

### 学习内容

**pyproject.toml 项目配置**

Python 现代项目的统一配置文件，对应 Node.js 的 `package.json` 和 Java 的 `pom.xml`/`build.gradle`。需要掌握：`[project]` 元数据段（name、version、dependencies）、`[project.optional-dependencies]` 开发依赖分组（对应 `devDependencies`）、`[project.scripts]` 命令行入口点（对应 `package.json` 的 `bin`/`scripts`）、`[tool.pytest.ini_options]` 工具配置段、`[build-system]` 构建后端声明。

**虚拟环境管理**

Python 的虚拟环境机制用于项目级依赖隔离，对应 Node.js 的 `node_modules` 目录级隔离。需要掌握：`python -m venv` 创建虚拟环境、激活/停用虚拟环境、理解虚拟环境的原理（独立的 `site-packages` 目录 + 路径优先级）。

**uv 包管理器**

Rust 编写的新一代 Python 包管理器，速度远超 pip。需要掌握：`uv pip install` 替代 `pip install`、`uv venv` 创建虚拟环境、`uv pip compile` 锁定依赖（类似 `npm ci` + `package-lock.json`）、`uv run` 在虚拟环境中执行命令。

**依赖管理实践**

掌握：`pip freeze > requirements.txt` 导出依赖、`requirements.txt` 与 `pyproject.toml` 的关系和适用场景、版本约束语法（`>=`、`~=`、`==`）、开发依赖与生产依赖分离。

**环境变量管理**

需要掌握：`.env` 文件与 `python-dotenv` 库、`pydantic-settings` 从环境变量加载配置（AI 项目中管理 API Key 的标准方式）、`.env.example` 模板的团队协作约定。

### 与 Java/Node.js 的对比

| 概念 | Java | Node.js | Python |
|:-----|:-----|:--------|:-------|
| 项目配置文件 | `pom.xml` / `build.gradle` | `package.json` | `pyproject.toml` |
| 依赖隔离 | Maven 本地仓库（全局） | `node_modules`（项目级） | `venv`（项目级虚拟环境） |
| 包管理器 | Maven / Gradle | npm / pnpm / yarn | pip / uv |
| 依赖锁定 | `pom.xml` 精确版本 | `package-lock.json` | `requirements.txt` / `uv.lock` |
| 命令行入口 | `Main-Class` in MANIFEST | `bin` in package.json | `[project.scripts]` in pyproject.toml |
| 环境变量 | Spring profiles / `.properties` | `dotenv` + `process.env` | `python-dotenv` / `pydantic-settings` |

### 检查点

- [ ] 能阅读和编写 `pyproject.toml`，包括依赖声明、入口点配置和工具配置段
- [ ] 能创建和激活 Python 虚拟环境，理解其隔离原理
- [ ] 能使用 uv 进行依赖安装和虚拟环境管理
- [ ] 能使用 `pip freeze` 导出依赖并理解版本约束语法
- [ ] 能使用 `pydantic-settings` 从 `.env` 文件加载应用配置
- [ ] 能解释 `pyproject.toml` 与 `requirements.txt` 各自的适用场景

---

## Day 6（周六，8h）：实战 -- 异步 CLI 工具

### 项目描述

构建一个异步命令行工具，综合运用 Day 1-5 所学的全部知识点。项目要求：

**功能需求**：构建一个异步 HTTP 健康检查 CLI 工具，接收一组 URL，并发检查其可用性，输出结果报告。

**技术要求覆盖**：
- 使用 Pydantic 定义配置模型和结果数据模型（Day 1）
- 使用类型注解覆盖所有函数签名（Day 1）
- 使用 `pathlib.Path` 处理配置文件和输出文件路径（Day 1）
- 使用推导式处理数据转换（Day 1）
- 使用 `async/await` + `asyncio.gather()` 实现并发请求（Day 2）
- 使用装饰器实现重试逻辑和耗时统计（Day 2）
- 使用 `httpx.AsyncClient` 作为上下文管理器发送请求（Day 3）
- 使用生成器实现结果的流式输出（Day 3）
- 使用 Click 或 Typer 构建 CLI 命令（Day 5）
- 使用 `python-dotenv` 或 `pydantic-settings` 管理配置（Day 5）
- 使用 `pyproject.toml` 配置项目和入口点（Day 5）

**开发流程**：从 `pyproject.toml` 初始化项目开始，创建虚拟环境，安装依赖，逐步实现各模块，确保每一步都能独立运行和验证。

### 检查点

- [ ] 项目使用 `pyproject.toml` 配置，可通过 `pip install -e .` 安装
- [ ] CLI 命令能正确解析参数和选项
- [ ] Pydantic 模型能验证输入配置并拒绝非法数据
- [ ] 并发请求能正确执行，失败的请求有重试机制
- [ ] 输出结果格式清晰，包含状态码、响应时间等信息
- [ ] 使用异步上下文管理器管理 HTTP 客户端生命周期
- [ ] 配置通过 `.env` 文件或环境变量加载

---

## Day 7（周日，8h）：实战 -- 完整测试套件

### 项目描述

为 Day 6 的异步 CLI 工具编写完整的测试套件，覆盖单元测试、集成测试和边界情况。

**测试范围**：

- **Pydantic 模型测试**：验证字段约束、必填/可选字段、自定义验证器的正确性和错误信息，使用参数化测试覆盖多种合法和非法输入
- **装饰器测试**：验证重试装饰器的重试次数和退避策略、耗时统计装饰器的输出格式，分别测试同步和异步版本
- **HTTP 请求测试**：使用 `pytest-httpx` 或 `respx` mock HTTP 响应，测试正常响应、超时、连接错误、非 2xx 状态码等场景，验证流式响应处理
- **CLI 测试**：使用 Click/Typer 的测试客户端（`CliRunner`）测试命令行参数解析、帮助信息输出、错误输入的提示信息
- **异步逻辑测试**：使用 `pytest-asyncio` 测试并发执行逻辑，验证 `gather()` 的异常处理行为，测试 Semaphore 并发限制
- **边界情况**：空 URL 列表、全部请求失败、超大响应体、特殊字符 URL、配置文件不存在

**测试工程化**：
- 使用 `conftest.py` 组织共享 fixture
- 使用 `yield` fixture 管理测试资源的生命周期
- 使用 `monkeypatch` 隔离环境变量依赖
- 使用 `tmp_path` fixture 处理临时文件
- 确保测试之间无状态泄漏

### 检查点

- [ ] 测试套件可通过 `pytest` 一键运行，全部通过
- [ ] 使用 `conftest.py` 集中管理共享 fixture
- [ ] HTTP 请求已 mock，测试不依赖外部网络
- [ ] 使用参数化测试覆盖多种输入场景
- [ ] 异步测试正确使用 `@pytest.mark.asyncio` 标记
- [ ] 使用 `monkeypatch` 隔离环境变量，测试间无副作用
- [ ] 覆盖至少 3 种边界情况（空列表、全失败、超时等）
- [ ] 测试覆盖率不低于 80%（使用 `pytest-cov` 验证）

---

## Phase 1 总结检查点

完成 Week 1 后，应当能够自信地勾选以下全部项目：

**语法与类型**
- [ ] 能熟练使用类型注解、Pydantic 模型和推导式
- [ ] 能编写和使用装饰器（含异步装饰器）
- [ ] 能使用生成器处理大数据流和流式输出

**异步编程**
- [ ] 能使用 `async/await` + `asyncio` 编写并发程序
- [ ] 能用上下文管理器管理异步资源生命周期
- [ ] 能清晰解释 Python 与 Node.js 异步模型的差异

**工程化**
- [ ] 能使用 `pyproject.toml` 配置完整的 Python 项目
- [ ] 能使用 venv/uv 管理虚拟环境和依赖
- [ ] 能使用 pytest 编写包含 fixture、参数化、mock 的测试套件

**实践验证**
- [ ] 完成异步 CLI 工具项目，功能完整可运行
- [ ] 完成测试套件，覆盖率 >= 80%，全部测试通过

---

## 下阶段预告

**Phase 2** 将进入 AI 基础设施层，学习内容包括：

- LangChain / LlamaIndex 框架核心概念
- Embedding 模型与向量数据库（ChromaDB）
- Prompt 工程与 Chain/Agent 模式
- RAG（检索增强生成）完整管道构建

Phase 1 打下的 Python 异步编程、Pydantic 数据建模和 pytest 测试能力，将在 Phase 2 中被密集使用。
