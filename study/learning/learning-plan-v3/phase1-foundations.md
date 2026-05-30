# Phase 1：双地基 — Python 现代化 + TS/React 启蒙

> **时间**：Week 1-2（D1-D14，52 小时）
> **前提**：有编程基础（Java / Node.js / Vue），无需 Python 与 React 经验
> **目标**：掌握 Python 现代化与异步工程（类型注解 / async / pytest / 包管理）+ TypeScript / React 地基（类型系统 / 组件 / Hooks / 状态管理）
> **融合设计**：借 Vue / Node 的心智模型平滑迁移 React / TS——async/await 对照 Node 事件循环、JSX 对照 Vue 模板、Hooks 对照 Composition API；地基理论与练手实战并行，每周末用一个完整项目把当周知识「跑起来」

---

## Week 1 (D1-D7)：Python 现代化

### D1 周一：类型注解 + Pydantic + f-string（2h）

**学习内容**：
- 类型注解基础：变量、函数参数与返回值的标注语法（`x: int`、`-> str`），对照 Java 的静态类型与 TS 的类型声明
- 容器与复合类型：`list[str]`、`dict[str, int]`、`Optional`、`Union`（`X | Y`）、`Any` 的语义与取舍
- 类型注解不强制运行时检查：Python 类型是「提示」，需配合 mypy / IDE 才生效，与 Java 编译期强约束不同
- Pydantic 模型：`BaseModel` 声明带类型的数据结构，自动完成解析、校验与序列化，是 FastAPI 请求体的基础
- Pydantic 校验能力：字段默认值、`Field` 约束（范围/长度）、校验失败抛 `ValidationError`，对照后端入参校验场景
- f-string 格式化：`f"{var}"` 内嵌表达式、`{value:.2f}` 格式说明符、`{var=}` 调试写法，替代旧式 `%` 与 `.format()`

**检查点**：
- [ ] 能为一个函数写出完整的参数与返回值类型注解，并说明它不影响运行时行为
- [ ] 能定义一个含必填/选填/带约束字段的 Pydantic 模型，并触发一次校验错误
- [ ] 能用 f-string 完成数字格式化与多变量拼接

---

### D2 周二：async/await + 装饰器 + 对比 Node.js（2h）

**学习内容**：
- 协程与事件循环：`async def` 定义协程、`await` 挂起等待，与 Node.js 单线程事件循环模型同源，理解「并发非并行」
- `asyncio` 运行入口：`asyncio.run()` 启动事件循环，对照 Node 的隐式事件循环差异（Python 需显式驱动）
- 并发原语：`asyncio.gather` 并发等待多任务、`create_task` 提交后台任务，对照 `Promise.all`
- 同步阻塞陷阱：在协程里调用阻塞 IO 会卡死事件循环，需用异步库或线程池，对照 Node 的非阻塞约束
- 装饰器本质：函数是一等对象，装饰器是「接收函数返回函数」的高阶函数，对照 Java 注解（语义不同）
- 实用装饰器：`@functools.wraps` 保留元信息、带参数的装饰器三层嵌套、计时/缓存等常见用途

**检查点**：
- [ ] 能写出一个用 `asyncio.gather` 并发执行多个协程的示例，并解释为何比串行快
- [ ] 能说清协程里调用阻塞操作的后果，以及 Python async 与 Node 事件循环的异同
- [ ] 能手写一个保留原函数元信息的计时装饰器

---

### D3 周三：生成器 + 上下文管理器 + httpx（2h）

**学习内容**：
- 生成器函数：`yield` 惰性产出值、节省内存的流式处理，对照普通返回 list 的内存差异
- 生成器表达式与迭代协议：`(x for x in ...)`、`__iter__` / `__next__` 背后的迭代机制
- 上下文管理器：`with` 语句确保资源（文件/连接）正确释放，对照 Java try-with-resources
- 自定义上下文管理器：`__enter__` / `__exit__` 协议与 `@contextmanager` 装饰器两种写法
- httpx 库：现代 HTTP 客户端，同时支持同步 `Client` 与异步 `AsyncClient`，对照 axios / fetch
- httpx 异步用法：`async with AsyncClient()` 发起并发请求、超时与重试配置，为后续调 LLM API 打基础

**检查点**：
- [ ] 能写一个生成器逐条产出数据，并说明它相比一次性返回列表的内存优势
- [ ] 能用 `with` 或 `@contextmanager` 实现一个自动清理资源的上下文管理器
- [ ] 能用 httpx 的 `AsyncClient` 并发发起多个请求并设置超时

---

### D4 周四：pytest 深入（fixtures/parametrize/mock）（2h）

**学习内容**：
- pytest 基础：`test_` 命名约定、`assert` 直接断言（无需断言方法），对照 JUnit / Jest 的差异
- fixture 机制：`@pytest.fixture` 提供可复用的测试前置资源，依赖注入式传参，对照 setUp / beforeEach
- fixture 作用域：`function` / `module` / `session` 控制创建频率，`yield` 实现 setup + teardown
- 参数化：`@pytest.mark.parametrize` 用一份用例覆盖多组输入输出，减少重复测试代码
- mock 与打桩：`unittest.mock` / `pytest-mock` 替换外部依赖（HTTP / 数据库 / LLM），隔离被测单元
- 异步测试与覆盖率：`pytest-asyncio` 测试协程、`pytest-cov` 统计覆盖率，理解覆盖率的意义与局限

**检查点**：
- [ ] 能用 fixture 提供共享资源，并用 `yield` 实现测试后清理
- [ ] 能用 `parametrize` 把一个函数的多组输入输出写成一份参数化测试
- [ ] 能 mock 一个 httpx 请求，使测试不依赖真实网络

---

### D5 周五：包管理（pyproject/venv/uv）+ 项目结构（2h）

**学习内容**：
- 虚拟环境：`venv` 隔离项目依赖，对照 Node 的 node_modules 局部隔离理念
- pyproject.toml：现代 Python 项目的统一配置入口（依赖 / 构建 / 工具配置），对照 package.json
- 依赖管理演进：requirements.txt 的局限，pyproject 声明式依赖 + 锁文件保证可复现
- uv 工具：Rust 实现的极速包管理器，`uv venv` / `uv pip` / `uv run`，对照 npm / pnpm 的速度优势
- 标准项目结构：`src/` 布局、包与模块、`__init__.py` 的作用、可导入性与可测试性
- 代码质量工具链：ruff（lint + format 一体）、mypy（类型检查），在 pyproject 中集中配置

**检查点**：
- [ ] 能创建虚拟环境并在其中安装、隔离一组依赖
- [ ] 能写一份含项目元信息、依赖与工具配置的 pyproject.toml
- [ ] 能搭出一个可被 import、可被 pytest 发现的标准项目目录结构

---

### D6 周六：实战 -- 异步 CLI 工具（Click + asyncio）（8h）

**学习内容**：
- Click 框架：用装饰器定义命令、参数与选项（`@click.command` / `@click.option`），对照 commander.js
- 子命令与命令组：`@click.group` 组织多级命令，构建结构化 CLI（如 `fetch` / `report` 子命令）
- 异步与 CLI 结合：在 Click 命令内驱动 `asyncio.run`，实现并发抓取多个 URL 的批处理工具
- 进度与体验：进度条、彩色输出、错误友好提示，提升命令行工具可用性
- 工程整合：将前几日所学（类型注解 / httpx 异步 / 上下文管理 / Pydantic 配置）落进一个真实小项目
- 健壮性处理：超时、重试、并发上限控制、异常聚合与退出码规范

**检查点**：
- [ ] CLI 工具支持至少两个子命令，参数与选项解析正确
- [ ] 工具能用 asyncio 并发抓取多个 URL，比串行明显更快
- [ ] 单个请求失败不导致整体崩溃，有重试与友好错误提示
- [ ] 代码使用类型注解，并通过 ruff 检查无明显告警

---

### D7 周日：实战 -- 完整测试套件 + 工程化收尾（8h）

**学习内容**：
- 为 D6 的 CLI 工具补齐测试：单元测试 + 集成测试分层，覆盖核心逻辑与命令入口
- mock 外部依赖：用 mock 隔离 httpx 网络请求，使测试快速、确定、可离线运行
- 异步代码测试：用 `pytest-asyncio` 覆盖并发抓取逻辑的正常与异常路径
- 边界与异常用例：参数化覆盖空输入、超时、重试耗尽等边界，验证退出码与错误信息
- 覆盖率达标：用 `pytest-cov` 统计并将核心模块覆盖率提升到 80% 以上，识别未覆盖分支
- 工程化收尾：完善 README、pyproject 元信息、ruff/mypy 配置，整理为可直接运行的作品集级仓库

**检查点**：
- [ ] 测试套件分单元/集成两层，全部通过且可离线运行
- [ ] 外部网络请求被 mock，测试不依赖真实接口
- [ ] 核心模块测试覆盖率超过 80%
- [ ] 仓库含 README + pyproject + lint 配置，他人可一键安装运行

---

## Week 2 (D8-D14)：TypeScript + React 启蒙

### D8 周一：TypeScript 类型系统（类型/接口/泛型/工具类型）（2h）

**学习内容**：
- 基础类型：`string` / `number` / `boolean` / `array` / `tuple` / `enum`，对照 Java 静态类型与 Python 注解
- interface 与 type：两种描述对象结构的方式、可选属性 `?`、只读 `readonly`、二者的区别与选择
- 泛型基础：`Array<T>`、泛型函数与泛型接口，让类型可参数化复用，对照 Java 泛型
- 工具类型：`Partial` / `Required` / `Pick` / `Omit` / `Record` 等内置类型变换，提升类型复用
- 类型推断与显式标注：何时让 TS 自动推断、何时必须显式标注，避免 `any` 滥用
- tsconfig 关键项：`strict` 模式、模块解析、目标版本，理解严格模式对工程质量的价值

**检查点**：
- [ ] 能用 interface 与 type 分别描述同一对象结构，并说明取舍
- [ ] 能写一个泛型函数，使其对多种类型保持类型安全
- [ ] 能用 `Pick` / `Omit` / `Partial` 从已有类型派生新类型

---

### D9 周二：TS 进阶（联合/交叉/类型守卫）+ 对比 Vue/JS（2h）

**学习内容**：
- 联合类型：`A | B` 表示多选一，配合字面量联合（如 `'success' | 'error'`）建模状态
- 交叉类型：`A & B` 合并多个类型，对照接口继承与混入场景
- 类型守卫：`typeof` / `in` / `instanceof` 与自定义类型谓词（`is`）实现联合类型的安全收窄
- 字面量与可辨识联合：用 `kind` 字段构建可辨识联合，配合 switch 穷尽处理
- 对比 Vue/JS：从 JS 动态类型迁移到 TS 静态类型的心智转变，Vue3 `defineProps` 类型化与 TS 的关系
- 实战取向：TS 如何在大型前端项目中减少运行时错误，对照你过往 Vue 项目的痛点

**检查点**：
- [ ] 能用可辨识联合建模一组状态，并用 switch 穷尽处理
- [ ] 能写一个自定义类型守卫（`x is T`）安全收窄联合类型
- [ ] 能写一份「JS → TS」对比笔记，列出三处 TS 带来的安全收益

---

### D10 周三：React 核心（组件/JSX/props/state/事件）对比 Vue（2h）

**学习内容**：
- 函数组件与 JSX：组件即返回 UI 的函数，JSX 是 JS 内的类 HTML 语法，对照 Vue 单文件模板
- props 单向数据流：父传子只读传递，对照 Vue props，理解 React 不可变数据的核心理念
- state 与 useState：组件内部可变状态，`setState` 触发重渲染，对照 Vue `ref` / `reactive`
- JSX 表达式与渲染：花括号嵌表达式、条件渲染（`&&` / 三元）、列表渲染与 `key`，对照 `v-if` / `v-for`
- 事件处理：`onClick={handler}` 驼峰命名、合成事件、传参写法，对照 Vue `@click`
- React 心智差异：「数据驱动视图 + 不可变更新 + 显式重渲染」，对照 Vue 响应式自动追踪

**检查点**：
- [ ] 能写一个接收 props 并渲染的函数组件，理解 props 只读
- [ ] 能用 useState 管理状态并在事件中更新触发重渲染
- [ ] 能列出 React 与 Vue 在数据流与渲染机制上的三点核心差异

---

### D11 周四：React Hooks（useState/useEffect/useRef/useMemo）（2h）

**学习内容**：
- useState 进阶：函数式更新 `setX(prev => ...)`、对象/数组的不可变更新、批处理机制
- useEffect 副作用：处理数据获取/订阅/手动 DOM 操作，对照 Vue `watch` / `onMounted` 生命周期
- 依赖数组：`[]` 仅挂载执行、`[dep]` 依赖变化执行、省略则每次渲染执行，及其常见陷阱
- 清理函数：useEffect 返回清理函数处理取消订阅/清定时器，对照 `onUnmounted`
- useRef：保存跨渲染的可变引用与访问 DOM 节点，不触发重渲染，对照 Vue `ref`(模板引用)
- useMemo 与 useCallback：缓存计算结果与函数引用以优化性能，对照 Vue `computed`，理解何时该用

**检查点**：
- [ ] 能用 useEffect 在组件挂载时获取数据，并在卸载时清理副作用
- [ ] 能正确配置依赖数组，避免无限循环或陈旧闭包
- [ ] 能用 useMemo / useRef 各完成一个恰当场景的优化或引用保存

---

### D12 周五：React 进阶（Context/自定义 Hook/受控组件）（2h）

**学习内容**：
- 受控组件：表单输入由 state 驱动（`value` + `onChange`），对照 Vue `v-model` 的双向绑定差异
- 非受控组件与 ref：用 useRef 读取 DOM 值的场景与适用边界
- Context API：`createContext` + `useContext` 跨层级共享数据，避免 props 逐层透传，对照 Vue provide/inject
- Context 适用边界：Context 解决「透传」而非「全局状态管理」，与 Zustand 的定位区分
- 自定义 Hook：把可复用的有状态逻辑抽成 `useXxx` 函数，对照 Vue Composition 函数（组合式复用）
- 逻辑复用心智：自定义 Hook 是 React 逻辑复用的核心范式，对照 Vue 的 composable

**检查点**：
- [ ] 能实现一个受控表单，并说清它与 Vue `v-model` 的机制差异
- [ ] 能用 Context 跨多层组件共享数据，避免 props 透传
- [ ] 能抽出一个自定义 Hook（如 `useToggle` / `useFetch`）并在组件中复用

---

### D13 周六：实战 -- React + TS 笔记/待办 SPA（8h）

**学习内容**：
- 项目脚手架：用 Vite 创建 React + TS 项目，理解开发服务器、HMR 与构建流程，对照 Vue + Vite 经验
- 组件拆分与类型：用 interface 定义 props 与数据模型（笔记/待办项），组件按职责拆分
- 状态与交互：用 useState 管理列表与表单，实现增删改查、完成态切换、过滤等核心交互
- 副作用与持久化：用 useEffect 将数据持久化到 localStorage，刷新后状态恢复
- 自定义 Hook 抽象：把列表操作或持久化逻辑抽成自定义 Hook，提升复用与可测性
- 样式与体验：基础样式布局、条件渲染空状态、表单校验提示，打磨为可演示成品

**检查点**：
- [ ] SPA 实现笔记/待办的增删改查与状态切换，交互正确
- [ ] 所有组件 props 与数据模型有完整 TS 类型，无 `any`
- [ ] 数据持久化到 localStorage，刷新后不丢失
- [ ] 至少抽出一个自定义 Hook 并在组件中复用

---

### D14 周日：Buffer 1 -- Zustand 状态管理 + API 请求 + 双栈验收（8h）

**学习内容**：
- Zustand 入门：极简全局状态管理，`create` 定义 store、组件按需订阅切片，对照 Pinia 的心智迁移
- Context vs Zustand：从 props 透传到 Context 再到 Zustand 的演进，理解何时引入全局状态库
- 异步数据请求：在前端用 fetch / axios 调用接口，结合 loading / error / data 三态管理请求
- 前后端联调：用 D6-D7 的 Python 异步 CLI/或一个简易接口作为数据源，打通前端请求链路
- 双栈回顾验收：串联 Week 1（Python 异步 + 测试 + 工程化）与 Week 2（TS + React + 状态管理）全部知识点
- 验收报告产出：整理双栈地基掌握情况、踩坑记录、React 与 Vue 差异总结，形成可写进作品集的复盘文档

**检查点**：
- [ ] 能用 Zustand 管理全局状态并在多个组件间共享，理解与 Context 的取舍
- [ ] 前端能发起异步 API 请求并正确处理 loading / error / 成功三态
- [ ] 完成一份双栈地基验收报告，含知识清单、踩坑记录与 React/Vue 差异总结
- [ ] 能口头讲清 Python async 与 React/Hooks 的核心心智模型

---

## 里程碑 1

**产出**：Python 异步工程能力 + React/TS 单页应用

验收标准：
- [ ] 掌握 Python async/await、类型注解、pytest，能写带测试的异步程序
- [ ] 掌握 TypeScript 类型系统（接口/泛型/工具类型）
- [ ] 能用 React + Hooks 构建一个带状态管理的 SPA（借 Vue 心智迁移）
- [ ] 理解 React 与 Vue 的核心差异（JSX / Hooks / 单向数据流）

---

## 下阶段预告

**Phase 2** 将在双栈地基之上正式进入大模型工程：从 HTTP 视角理解 LLM API 调用，构建多厂商统一客户端（Claude / OpenAI / 国产模型），并深入 Prompt 工程与 Function Calling，迈向「Prompt 大师」里程碑。
