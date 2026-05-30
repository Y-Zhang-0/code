# Phase 5：Agent 系统 + 异步化 + 负载均衡

> **时间**：Week 13-17（D85-D119，130 小时）  
> **前提**：Phase 4 生产化工程完成  
> **目标**：掌握 LangGraph Agent 开发、MCP 工具集成、多智能体协作；同时学会 Celery 异步任务、消息队列和 Nginx 负载均衡  
> **融合设计**：Agent 长任务自然需要异步化（Celery），多实例部署需要负载均衡（Nginx），问题驱动学习后端组件

---

## Week 13 (D85-D91)：LangGraph 基础

### D85：Agent 分类（3h）

**学习内容**：
- Agent 核心概念：感知-推理-行动循环，Agent 与普通 Chain 的本质区别
- ReAct 模式：推理（Reasoning）与行动（Acting）交替进行，适用于需要多步推理的通用任务
- Plan-and-Execute 模式：先制定完整计划再逐步执行，适用于复杂多步骤任务
- Tool-Use 模式：LLM 判断何时调用哪个工具，适用于需要外部能力扩展的场景
- Autonomous 模式：自主决策与自我纠错，适用于开放式探索任务
- 模式选择决策框架：根据任务复杂度、可控性要求、延迟容忍度选择合适的 Agent 模式

**检查点**：
- [ ] 能用自己的话解释四种 Agent 模式的核心差异
- [ ] 给定三个具体场景，能判断应使用哪种模式并说明理由
- [ ] 理解 Agent 的优势与风险（幻觉、无限循环、成本失控）

---

### D86：LangGraph 基础（3h）

**学习内容**：
- LangGraph 定位：相比 LangChain AgentExecutor 的优势——显式状态管理、可视化流程、细粒度控制
- StateGraph 核心概念：图（Graph）、节点（Node）、边（Edge）的关系
- 节点定义：每个节点是一个函数，接收当前状态并返回状态更新
- 边的类型：普通边（固定流转）、条件边（基于状态动态路由）
- 条件路由：`add_conditional_edges` 根据状态字段决定下一个节点
- 图的编译与执行：`graph.compile()` 生成可运行的 Runnable 对象，`invoke` 与 `stream` 两种调用方式

**检查点**：
- [ ] 理解 StateGraph 的 节点-边-状态 三元素模型
- [ ] 能画出一个包含条件路由的简单 Agent 流程图
- [ ] 理解 `invoke`（同步等待完整结果）与 `stream`（逐步输出）的使用场景

---

### D87：LangGraph 状态管理（3h）

**学习内容**：
- TypedDict 状态定义：使用 Python TypedDict 声明状态结构，字段类型约束
- Annotated 与 Reducer：`Annotated[list, operator.add]` 实现列表追加而非覆盖
- 状态更新机制：节点返回部分状态字典，框架自动合并到全局状态
- Checkpointing 检查点：`MemorySaver`（内存）、`SqliteSaver`（持久化）实现状态快照
- 时间旅行（Time Travel）：基于检查点回溯到任意历史状态，支持调试与回放
- 状态设计最佳实践：最小化状态字段、避免冗余数据、区分临时状态与持久状态

**检查点**：
- [ ] 定义一个包含消息列表和中间结果的 TypedDict 状态
- [ ] 理解 Reducer 的作用：为什么消息列表需要追加而非替换
- [ ] 配置 MemorySaver 并验证状态可在多轮对话间保持

---

### D88：Tool-Use Agent（3h）

**学习内容**：
- 工具定义规范：函数签名、docstring 描述、JSON Schema 参数声明
- `@tool` 装饰器：LangChain 工具定义的标准方式，自动提取 Schema
- LLM 工具调用流程：LLM 输出工具调用请求 -> 框架执行工具 -> 结果回传 LLM -> LLM 决定下一步
- ToolNode：LangGraph 内置的工具执行节点，自动处理工具调用消息
- 工具绑定：`llm.bind_tools(tools)` 让 LLM 知道可用工具列表
- 循环控制：Agent 在 LLM 节点和 ToolNode 之间循环，直到 LLM 决定不再调用工具

**检查点**：
- [ ] 定义至少两个工具（如搜索、计算），理解 JSON Schema 描述的重要性
- [ ] 理解 LLM -> ToolNode -> LLM 的循环执行流程
- [ ] 知道如何设置最大迭代次数防止无限循环

---

### D89：Human-in-the-loop（3h）

**学习内容**：
- 人机协作的必要性：高风险操作需人工审批、敏感数据访问需确认、纠正 Agent 错误决策
- `interrupt_before` 机制：在指定节点执行前暂停图运行，等待人工输入
- 审批工作流设计：Agent 提出行动方案 -> 暂停 -> 人工审批/拒绝/修改 -> 继续执行
- 状态检查与修改：暂停期间检查当前状态，人工修改状态字段后恢复执行
- `Command` 与 `interrupt` 函数：LangGraph 提供的细粒度中断控制
- 实际应用场景：数据库删除操作审批、大额交易确认、文件系统写操作确认

**检查点**：
- [ ] 理解 `interrupt_before` 的工作机制与检查点的配合关系
- [ ] 能设计一个"危险操作需审批"的 Agent 流程
- [ ] 理解暂停后如何恢复执行（传入新的输入并从检查点继续）

---

### D90 Sat：实战 -- LangGraph ReAct Agent（8h）

**学习内容**：
- 从零构建 ReAct Agent：定义状态、LLM 节点、工具节点、条件路由
- 工具集实现：Web 搜索工具（调用搜索 API）、数学计算工具、文件读取工具
- ReAct 循环编排：LLM 推理 -> 工具调用 -> 观察结果 -> 再推理，直到得出最终答案
- 流式输出：使用 `stream` 方法实时展示 Agent 的推理过程和中间步骤
- 错误处理：工具调用失败时的回退策略、超时处理、异常捕获
- 调试技巧：打印每一步的状态变化，理解 Agent 的决策路径

**检查点**：
- [ ] ReAct Agent 能正确调用搜索、计算、文件操作三种工具
- [ ] Agent 能在多步推理后给出最终答案
- [ ] 流式输出展示完整的推理-行动-观察链
- [ ] 工具调用异常不导致 Agent 崩溃

---

### D91 Sun：实战 -- 带审批流的 Agent（8h）

**学习内容**：
- 在 D90 的 ReAct Agent 基础上增加 Human-in-the-loop 机制
- 工具风险分级：安全工具（搜索、计算）自动执行、危险工具（文件写入、删除）需审批
- 审批流实现：Agent 调用危险工具前暂停，展示操作详情，等待人工确认
- 审批交互界面：命令行交互方式实现审批/拒绝/修改参数
- 检查点持久化：使用 SqliteSaver 保存状态，支持审批中断后恢复
- 完整流程验证：提问 -> Agent 推理 -> 调用安全工具 -> 遇到危险操作暂停 -> 审批 -> 继续执行 -> 返回结果

**检查点**：
- [ ] 安全工具自动执行，危险工具触发审批中断
- [ ] 审批拒绝后 Agent 能选择替代方案继续推理
- [ ] 使用 SqliteSaver 持久化状态，关闭程序后可恢复审批流程
- [ ] 端到端完成一个包含审批环节的复杂查询任务

---

## Week 14 (D92-D98)：MCP 深度

### D92：MCP 架构深入（3h）

**学习内容**：
- MCP（Model Context Protocol）定位：为 LLM 应用提供标准化的工具与资源访问协议
- 架构分层：Host（应用）-> Client（协议层）-> Server（能力提供方），三者职责分离
- 传输层：stdio（本地进程通信，低延迟）vs SSE（HTTP 远程通信，跨网络部署）
- 协议消息格式：JSON-RPC 2.0 规范，request / response / notification 三种消息类型
- Server 生命周期：初始化握手（capabilities 协商）-> 正常通信 -> 优雅关闭
- 安全模型：Server 隔离运行，Host 控制权限授予，最小权限原则

**检查点**：
- [ ] 能画出 Host-Client-Server 三层架构图并说明数据流向
- [ ] 理解 stdio 与 SSE 两种传输方式的适用场景
- [ ] 理解 MCP 与直接函数调用相比的优势（标准化、隔离、可发现）

---

### D93：MCP Server 开发（3h）

**学习内容**：
- Python `mcp` SDK 安装与基本使用，`FastMCP` 高级 API
- 工具注册：`@server.tool()` 装饰器定义工具，参数通过函数签名自动推导
- 资源注册：`@server.resource()` 装饰器暴露数据资源，支持 URI 模板
- Prompt 注册：`@server.prompt()` 装饰器定义 Prompt 模板
- Server 启动：stdio 模式与 SSE 模式的启动方式差异
- 调试方法：MCP Inspector 工具调试 Server，查看工具列表与调用结果

**检查点**：
- [ ] 使用 FastMCP 创建一个包含至少两个工具的 MCP Server
- [ ] Server 能通过 stdio 方式正常启动并响应工具调用
- [ ] 使用 MCP Inspector 验证工具注册与调用

---

### D94：MCP 三种能力（3h）

**学习内容**：
- Tools（工具）：模型主动调用的函数，执行操作并返回结果，适用于需要副作用的场景
- Resources（资源）：应用驱动的数据访问，类似 REST GET，提供上下文信息但不执行操作
- Prompts（提示模板）：预定义的交互模板，用户可选择使用，标准化特定工作流
- 三种能力的选择决策：需要执行操作用 Tool，需要读取数据用 Resource，需要引导交互用 Prompt
- 组合使用模式：Resource 提供上下文 + Tool 执行操作 + Prompt 引导流程
- 能力发现机制：Client 在初始化时获取 Server 的完整能力列表

**检查点**：
- [ ] 给定五个具体需求，能正确判断应实现为 Tool、Resource 还是 Prompt
- [ ] 理解三种能力在 LLM 交互中的控制权差异（模型控制 vs 应用控制 vs 用户控制）
- [ ] 能设计一个同时使用三种能力的 MCP Server 方案

---

### D95：MCP 客户端集成（3h）

**学习内容**：
- MCP Client 实现：使用 `mcp` SDK 的 `ClientSession` 连接 MCP Server
- 工具发现与调用：`list_tools()` 获取可用工具，`call_tool()` 执行工具调用
- LangGraph 集成方案：将 MCP 工具转换为 LangChain Tool 格式，注入 Agent 工具集
- 多 Server 连接：一个 Client 同时连接多个 MCP Server，工具命名空间管理
- 错误处理：Server 连接失败、工具调用超时、返回格式异常的处理策略
- 动态工具加载：运行时发现并加载新的 MCP Server 提供的工具

**检查点**：
- [ ] 实现 MCP Client 连接 Server 并成功调用工具
- [ ] 将 MCP 工具集成到 LangGraph Agent 中，Agent 能自动选择并调用 MCP 工具
- [ ] 处理 Server 不可用时的降级策略

---

### D96：工具设计模式（3h）

**学习内容**：
- 幂等性设计：同一工具多次调用相同参数应产生相同结果，避免重复副作用
- 错误处理规范：工具内部捕获异常，返回结构化错误信息而非抛出异常
- 超时管理：为每个工具设置合理的执行超时，防止 Agent 被单个工具阻塞
- 安全边界：工具权限控制（读写分离）、输入校验（防注入）、输出过滤（防信息泄漏）
- 工具描述优化：清晰的工具名称和描述直接影响 LLM 的工具选择准确率
- 组合工具模式：将多个细粒度工具组合为粗粒度工具，减少 Agent 决策复杂度

**检查点**：
- [ ] 审查已有工具实现，识别幂等性和安全性问题
- [ ] 为工具添加超时控制和结构化错误返回
- [ ] 优化工具描述，对比优化前后 LLM 的工具选择准确率

---

### D97 Sat：实战 -- MCP Server 开发（8h）

**学习内容**：
- 开发三个功能独立的 MCP Server：数据库访问、文件系统操作、Web 搜索
- 数据库访问 Server：查询表结构、执行 SELECT 查询、结果格式化返回
- 文件系统 Server：读取文件内容、列出目录结构、写入文件（需确认）
- Web 搜索 Server：调用搜索 API、解析搜索结果、返回摘要信息
- 每个 Server 实现完整的错误处理、输入校验、超时控制
- 使用 MCP Inspector 逐一测试每个 Server 的所有工具

**检查点**：
- [ ] 三个 MCP Server 分别独立启动并通过 Inspector 测试
- [ ] 数据库 Server 能安全执行只读查询并返回格式化结果
- [ ] 文件系统 Server 的写操作有安全限制（目录白名单、文件大小限制）
- [ ] Web 搜索 Server 处理 API 限流和超时

---

### D98 Sun：实战 -- MCP 驱动的开发助手（8h）

**学习内容**：
- 构建 LangGraph Agent 连接 D97 开发的三个 MCP Server
- 统一工具管理：Agent 自动发现并加载所有 MCP Server 的工具
- 复杂任务验证：Agent 读取代码文件 -> 查询数据库 -> 搜索文档 -> 综合分析回答
- 多 Server 协调：Agent 在一次任务中跨 Server 调用多个工具
- 对话记忆：Agent 在多轮对话中保持上下文，引用之前的工具调用结果
- 性能优化：工具调用结果缓存、并行工具调用、减少不必要的工具调用

**检查点**：
- [ ] Agent 能根据用户问题自动选择合适的 MCP Server 工具
- [ ] 完成一个跨三个 Server 的复杂查询任务
- [ ] 多轮对话中 Agent 正确引用历史上下文
- [ ] 记录整个任务的工具调用链路和 Token 消耗

---

## Week 15 (D99-D105)：多智能体

### D99：多智能体模式（3h）

**学习内容**：
- Supervisor 模式：中央协调者分配任务给专业 Agent，汇总结果，适用于任务可分解的场景
- 层级模式（Hierarchical）：多层 Supervisor 嵌套，顶层规划、中层协调、底层执行
- 点对点模式（Peer-to-Peer）：Agent 之间直接通信，无中央协调，适用于对等协作
- Swarm 模式：动态路由，Agent 之间按需切换，适用于客服等场景
- 模式选择决策：任务结构化程度、Agent 数量、通信开销、容错需求
- 现实世界多智能体案例分析：代码审查系统、内容生产流水线、客服分流系统

**检查点**：
- [ ] 能用图示说明四种多智能体模式的拓扑结构差异
- [ ] 给定一个业务场景，能选择合适的多智能体模式并说明理由
- [ ] 理解多智能体系统的核心挑战（通信开销、状态一致性、死锁）

---

### D100：LangGraph 多智能体（3h）

**学习内容**：
- Sub-graph 概念：每个 Agent 作为独立的 StateGraph，通过 Sub-graph 嵌入主图
- Agent Handoff：一个 Agent 将控制权和上下文传递给另一个 Agent 的机制
- 共享状态设计：定义 Agent 间共享的状态字段，隔离各 Agent 的私有状态
- Supervisor 实现：Supervisor 节点根据任务类型路由到不同的 Agent Sub-graph
- Agent 注册与发现：动态注册 Agent 能力描述，Supervisor 根据能力匹配任务
- 结果聚合：Supervisor 收集多个 Agent 的输出并综合生成最终响应

**检查点**：
- [ ] 理解 Sub-graph 如何封装独立 Agent 的内部逻辑
- [ ] 能设计 Supervisor + 两个专业 Agent 的状态流转图
- [ ] 理解 Agent Handoff 时上下文传递的数据格式

---

### D101：Agent 通信（3h）

**学习内容**：
- 消息传递模式：Agent 通过消息队列异步通信，松耦合但延迟较高
- 共享状态模式：Agent 通过读写共享状态空间通信，LangGraph 的默认方式
- 黑板模式（Blackboard）：公共数据结构供所有 Agent 读写，适用于知识融合场景
- 通信协议设计：消息格式标准化、消息路由规则、消息优先级
- 同步 vs 异步通信：阻塞等待结果 vs 发送后继续执行，各自的适用场景
- 通信失败处理：消息丢失检测、重试机制、超时降级

**检查点**：
- [ ] 对比三种通信模式的优缺点和适用场景
- [ ] 理解 LangGraph 中 Agent 间通过共享状态通信的具体实现方式
- [ ] 设计一个包含异步通信的多 Agent 协作方案

---

### D102：Agent 记忆（3h）

**学习内容**：
- 短期记忆（Short-term）：当前对话上下文，存储在 LangGraph 状态中，会话结束即消失
- 长期记忆（Long-term）：跨会话的知识积累，存储在向量数据库中，支持语义检索
- 情景记忆（Episodic）：过去的完整交互案例，Agent 可参考历史成功/失败经验
- 记忆管理策略：Token 窗口限制下的记忆压缩、摘要、遗忘机制
- 向量存储记忆实现：对话摘要 -> Embedding -> 存入向量库 -> 相似查询召回
- 多 Agent 记忆共享：共享知识库 vs 私有记忆空间的设计权衡

**检查点**：
- [ ] 理解三种记忆类型的存储位置和生命周期差异
- [ ] 设计一个结合短期和长期记忆的 Agent 记忆方案
- [ ] 理解记忆压缩的必要性和常见实现方式（摘要、滑动窗口）

---

### D103：Agent 评估（3h）

**学习内容**：
- 任务完成率：Agent 是否最终完成了用户的请求，成功/失败/部分完成的判定标准
- 工具效率：工具调用次数、冗余调用占比、工具选择准确率
- 多轮一致性：Agent 在多轮对话中是否保持上下文一致，是否自相矛盾
- 延迟与成本：端到端响应时间、Token 总消耗、每次任务的 API 调用费用
- 评估框架搭建：测试用例集设计、自动化评估脚本、评估结果可视化
- 基线对比：与简单 Chain 对比 Agent 的效果，验证 Agent 架构的收益

**检查点**：
- [ ] 定义至少五项 Agent 评估指标及其计算方式
- [ ] 设计一组覆盖不同难度的测试用例集
- [ ] 理解评估驱动优化的迭代流程：评估 -> 发现瓶颈 -> 优化 -> 再评估

---

### D104 Sat：实战 -- 多智能体协作（8h）

**学习内容**：
- 构建 Supervisor + 三个专业 Agent 的多智能体系统
- 研究 Agent：负责信息收集与搜索，调用 Web 搜索和文档检索工具
- 分析 Agent：负责数据分析与推理，调用计算和数据库查询工具
- 写作 Agent：负责内容生成与整理，基于前两个 Agent 的输出生成结构化报告
- Supervisor 编排逻辑：根据用户问题类型分配任务、协调 Agent 执行顺序、聚合最终结果
- 端到端验证：输入一个复杂问题，观察多个 Agent 的协作过程和最终输出

**检查点**：
- [ ] Supervisor 正确识别任务类型并分配给合适的 Agent
- [ ] 三个 Agent 各自完成专业任务并返回结果
- [ ] Supervisor 聚合多个 Agent 输出生成完整的最终回答
- [ ] 记录完整的多 Agent 执行链路（调用顺序、耗时、Token 消耗）

---

### D105 Sun：实战 -- CrewAI 体验 + 框架对比（8h）

**学习内容**：
- CrewAI 核心概念：Agent（角色定义）、Task（任务描述）、Crew（团队编排）、Process（执行模式）
- 使用 CrewAI 快速搭建与 D104 同功能的多智能体系统
- 功能对比：LangGraph vs CrewAI 在状态管理、流程控制、调试能力上的差异
- 开发体验对比：代码量、学习曲线、灵活度、生态集成
- 适用场景对比：LangGraph 适合复杂自定义流程，CrewAI 适合快速原型和标准协作模式
- 技术选型决策框架：根据项目需求（灵活度、上手速度、生产稳定性）选择合适的框架

**检查点**：
- [ ] 使用 CrewAI 实现与 D104 类似的多智能体协作系统
- [ ] 完成 LangGraph vs CrewAI 的对比表格（至少包含六个维度）
- [ ] 给出明确的技术选型建议并说明理由
- [ ] 理解两个框架的核心设计哲学差异

---

## Week 16 (D106-D112)：Celery 异步 + 消息队列（后端融入）

### D106：Celery 基础（3h）

**学习内容**：
- Celery 架构三要素：Worker（执行者）、Broker（消息中间件，Redis/RabbitMQ）、Backend（结果存储）
- 任务定义：`@app.task` 装饰器，任务函数的序列化要求
- 任务调用：`delay()` 快捷调用、`apply_async()` 高级调用（指定队列、倒计时、过期时间）
- 结果获取：`AsyncResult` 对象查询任务状态（PENDING/STARTED/SUCCESS/FAILURE）和返回值
- Worker 管理：启动、停止、并发数设置、prefetch 配置
- Broker 选择：Redis（简单轻量、已有组件复用）vs RabbitMQ（功能完整、消息可靠性更强）

**检查点**：
- [ ] 启动 Celery Worker 并成功执行第一个异步任务
- [ ] 通过 `AsyncResult` 查询任务状态和结果
- [ ] 理解 Broker 和 Backend 在架构中的角色差异

---

### D107：Celery 任务模式（3h）

**学习内容**：
- 任务重试：`self.retry()` 机制，`max_retries`、`countdown` 参数，指数退避策略
- Chain（链式）：任务串行执行，前一个任务的返回值作为下一个任务的输入
- Group（分组）：多个任务并行执行，收集所有结果
- Chord（和弦）：Group + 回调，所有并行任务完成后触发回调任务
- 定时任务：`celery beat` 调度器，crontab 表达式定义周期性任务
- 任务优先级与队列路由：不同类型任务分配到不同队列，高优先级任务优先消费

**检查点**：
- [ ] 实现一个带指数退避的自动重试任务
- [ ] 使用 Chain 编排三个任务的串行执行
- [ ] 使用 Group + Chord 实现并行执行后汇总的模式
- [ ] 配置 celery beat 创建一个每分钟执行的定时任务

---

### D108：Celery + FastAPI 集成（3h）

**学习内容**：
- FastAPI 与 Celery 集成架构：API 接收请求 -> 提交 Celery 任务 -> 返回 task_id -> 客户端轮询结果
- 任务提交端点：接收参数，调用 `task.delay()`，返回 `task_id`
- 进度查询端点：根据 `task_id` 查询 `AsyncResult`，返回状态和进度信息
- 自定义任务状态：使用 `self.update_state()` 报告中间进度（如 "处理中 50%"）
- SSE 进度推送：Server-Sent Events 替代客户端轮询，实时推送任务进度
- 结果获取端点：任务完成后获取最终结果，处理失败任务的错误信息返回

**检查点**：
- [ ] FastAPI 端点提交 Celery 任务并返回 task_id
- [ ] 客户端通过 task_id 查询任务进度和状态
- [ ] 实现自定义进度上报，任务执行中可查看百分比进度
- [ ] 任务失败时返回结构化错误信息

---

### D109：消息队列理论（3h）

**学习内容**：
- 消息队列核心价值：解耦（生产者消费者独立演进）、削峰（缓冲突发流量）、异步（非阻塞处理）
- 消息投递语义：至少一次（at-least-once）、至多一次（at-most-once）、恰好一次（exactly-once）的实现代价
- 消息确认机制（ACK）：自动确认 vs 手动确认，确认失败后的消息重新投递
- 死信队列（DLQ）：处理失败的消息路由到死信队列，人工排查或自动重试
- 消息持久化：Broker 宕机后消息是否丢失，持久化的性能代价
- 消息顺序性：全局有序 vs 分区有序 vs 无序，不同场景的顺序性需求

**检查点**：
- [ ] 能解释三种消息投递语义的差异及各自的实现难度
- [ ] 理解 ACK 机制在消息可靠性中的作用
- [ ] 能判断给定场景需要什么级别的消息可靠性保障

---

### D110：RabbitMQ 基础（3h）

**学习内容**：
- RabbitMQ 核心概念：Exchange（交换机）、Queue（队列）、Binding（绑定规则）
- Exchange 类型：Direct（精确路由）、Fanout（广播）、Topic（模式匹配）、Headers
- 消息路由流程：Producer -> Exchange -> Binding -> Queue -> Consumer
- 死信队列配置：`x-dead-letter-exchange`、`x-dead-letter-routing-key` 参数
- RabbitMQ 管理界面：通过 Web UI 监控队列深度、消费速率、连接状态
- Docker 部署 RabbitMQ：使用 `rabbitmq:management` 镜像，端口映射与持久化配置

**检查点**：
- [ ] 通过 Docker 启动 RabbitMQ 并访问管理界面
- [ ] 理解消息从 Producer 到 Consumer 的完整路由路径
- [ ] 能区分四种 Exchange 类型的适用场景

---

### D111 Sat：实战 -- Agent 长任务 Celery 异步化（8h）

**学习内容**：
- 问题场景：Agent 执行复杂任务耗时数十秒甚至数分钟，同步 API 调用会超时
- 架构设计：API 提交 Agent 任务到 Celery -> Worker 执行 Agent 流程 -> 客户端轮询进度与结果
- Agent 任务封装：将 LangGraph Agent 的 `invoke` 调用封装为 Celery Task
- 进度上报：Agent 每完成一个步骤（工具调用、LLM 推理）上报进度到 Celery Backend
- 结果存储：Agent 最终输出存入数据库，通过 task_id 关联查询
- 端到端验证：提交复杂问题 -> 获取 task_id -> 轮询进度 -> 获取最终结果

**检查点**：
- [ ] Agent 任务通过 Celery 后台执行，API 立即返回 task_id
- [ ] 任务执行期间可查询中间进度（如 "正在搜索..."、"正在分析..."）
- [ ] 任务完成后通过 API 获取完整结果
- [ ] 任务失败时有明确的错误信息和重试机制

---

### D112 Sun：实战 -- 事件驱动文档摄入管道（8h）

**学习内容**：
- 将文档摄入流程重构为事件驱动架构：上传 -> 解析 -> 分块 -> 嵌入 -> 存储，每个阶段通过消息队列连接
- 消息队列选型：RabbitMQ（本阶段重点）或 Redis Streams 作为消息中间件
- 每个阶段作为独立的 Celery Worker：可独立扩缩容、独立部署、故障隔离
- 错误处理与补偿：某个阶段失败后的重试策略、死信队列告警、人工干预入口
- 幂等性保证：重复消费同一消息不产生副作用，通过文档 ID 去重
- 监控与可观测：队列深度监控、各阶段耗时统计、吞吐量仪表板

**检查点**：
- [ ] 文档上传后自动触发异步摄入管道
- [ ] 各阶段 Worker 独立运行，通过消息队列传递数据
- [ ] 某个阶段失败后消息进入死信队列，不影响其他文档处理
- [ ] 同一文档重复提交不产生重复数据

---

## Week 17 (D113-D119)：Nginx + 可观测性 + Buffer 4（后端融入）

### D113：Nginx 基础（3h）

**学习内容**：
- Nginx 定位：高性能 HTTP 服务器、反向代理、负载均衡器
- 反向代理概念：客户端请求 Nginx -> Nginx 转发到后端应用 -> 响应原路返回
- 核心配置结构：`http`、`server`、`location` 三层嵌套
- 静态文件服务：直接由 Nginx 处理静态资源请求，减轻应用服务器负担
- SSL/TLS 终结：Nginx 处理 HTTPS 握手和加解密，后端应用只需处理 HTTP
- Docker 部署 Nginx：使用官方镜像，挂载配置文件和证书

**检查点**：
- [ ] 通过 Docker 启动 Nginx 并成功代理一个后端服务
- [ ] 理解 `proxy_pass` 指令的工作机制
- [ ] 能编写基本的 Nginx 配置文件实现反向代理

---

### D114：Nginx 负载均衡（3h）

**学习内容**：
- 负载均衡的必要性：单实例性能瓶颈、高可用、滚动更新
- upstream 配置块：定义后端服务器组，Nginx 在组内分发请求
- 均衡算法：Round-Robin（默认轮询）、Least-Conn（最少连接）、Weighted（加权）、IP Hash（会话保持）
- 健康检查：被动检查（`max_fails` + `fail_timeout`）、主动检查（Nginx Plus / 第三方模块）
- 会话亲和性：IP Hash 或 Cookie 保持同一用户路由到同一后端实例
- 算法选择决策：无状态服务用 Round-Robin，长连接用 Least-Conn，有状态会话用 IP Hash

**检查点**：
- [ ] 配置 upstream 块定义多个后端实例
- [ ] 对比 Round-Robin 和 Least-Conn 的请求分发效果
- [ ] 理解健康检查机制如何自动剔除故障实例

---

### D115：多实例部署（3h）

**学习内容**：
- Docker Compose 多实例扩展：`deploy.replicas` 或手动定义多个同类服务
- Nginx + 多 FastAPI 实例架构：一个 Nginx 容器代理三个 FastAPI 容器
- 网络配置：Docker 自定义网络中 Nginx 通过服务名发现后端实例
- 共享资源处理：多实例共享同一数据库、同一 Redis、同一 ChromaDB
- 无状态设计验证：任意请求打到任一实例都能正确处理（Session 不依赖本地内存）
- 日志聚合：多实例的日志统一收集与标记（标注来源实例）

**检查点**：
- [ ] Docker Compose 启动 Nginx + 3 个 FastAPI 实例
- [ ] 通过 Nginx 访问 API，请求被均匀分发到三个实例
- [ ] 单个实例停止后其他实例继续提供服务，无用户感知
- [ ] 所有实例共享同一数据源，数据一致性无问题

---

### D116：Agent 可观测性（3h）

**学习内容**：
- LangSmith 平台：LangChain 官方的 Agent 追踪与调试平台
- Tracing 集成：通过环境变量启用 LangSmith，自动记录 LLM 调用链
- Token 追踪：每次 LLM 调用的 Token 消耗明细（prompt tokens / completion tokens）
- 决策日志：Agent 的工具选择理由、条件路由决策、状态变化全程记录
- 自定义指标：记录业务维度指标（检索相关度、回答满意度、任务完成率）
- 告警配置：Token 消耗超阈值、响应延迟超标、错误率突增时触发告警

**检查点**：
- [ ] 启用 LangSmith 并在平台上查看 Agent 执行链路
- [ ] 每次 Agent 调用都能追踪到完整的工具调用序列和 Token 消耗
- [ ] 能通过 LangSmith 排查一次 Agent 执行异常的根因

---

### D117：Agent 生产化（3h）

**学习内容**：
- 成本控制：Token 预算设置、每次请求成本上限、月度费用预警
- 超时管理：总超时限制（整体任务）+ 单步超时（单次工具调用/LLM 调用）
- 安全护栏（Guardrails）：输入过滤（拒绝违规问题）、输出过滤（防止敏感信息泄漏）
- 最大迭代次数：防止 Agent 进入无限循环，`recursion_limit` 设置
- 降级策略：LLM API 不可用时的降级方案（缓存回答、固定话术、转人工）
- 生产检查清单：上线前必须验证的安全、性能、可靠性检查项

**检查点**：
- [ ] 为 Agent 配置 Token 预算和最大迭代次数
- [ ] 实现输入输出过滤的安全护栏
- [ ] 设计 LLM API 不可用时的完整降级方案
- [ ] 完成 Agent 生产上线检查清单

---

### D118 Sat：Buffer 4 -- Phase 5 复盘 + Agent 系统验收（8h）

**学习内容**：
- Phase 5 知识点全面回顾：LangGraph Agent、MCP 工具集成、多智能体协作、Agent 评估
- Agent 系统端到端验收：从单 Agent 到多 Agent，从简单工具到 MCP 集成
- 复盘 Agent 开发中的踩坑记录：常见错误模式、调试技巧、性能瓶颈
- 补齐 Week 13-15 未完成的实战内容
- 整理 Agent 开发最佳实践文档

**检查点**：
- [ ] LangGraph ReAct Agent 端到端功能正常（工具调用、Human-in-the-loop）
- [ ] MCP Server 开发与集成验证通过
- [ ] 多智能体 Supervisor 模式验收：任务分配、协作、结果聚合
- [ ] Agent 可通过 LangSmith 观测完整执行链路

---

### D119 Sun：Buffer 4 -- Celery + Nginx 全链路验收（8h）

**学习内容**：
- 后端组件全链路验证：Celery 异步任务 + RabbitMQ 消息队列 + Nginx 负载均衡
- Celery 验收：Agent 长任务异步执行、进度查询、失败重试
- Nginx 验收：多实例负载均衡、健康检查、故障转移
- 全栈集成测试：Nginx -> FastAPI (x3) -> Celery -> Agent -> MCP Tools
- 压力测试：模拟并发请求验证负载均衡效果和 Celery 队列处理能力
- 补齐 Week 16-17 未完成的实战内容

**检查点**：
- [ ] Agent 长任务通过 Celery 后台执行，支持进度查询
- [ ] Nginx 均衡分发请求到多个 FastAPI 实例
- [ ] 单个实例故障后系统自动切换到健康实例
- [ ] 事件驱动文档摄入管道完整运行（上传 -> 解析 -> 分块 -> 嵌入 -> 存储）
- [ ] 记录全链路架构图和各组件配置要点

---

## 里程碑 5

**LangGraph 多智能体系统 + MCP 工具集成 + Celery 异步化 + Nginx 负载均衡**

验收标准：
- [ ] LangGraph ReAct Agent 支持多工具调用与 Human-in-the-loop 审批
- [ ] MCP Server 开发三种工具服务（数据库/文件/搜索），Agent 可动态调用
- [ ] 多智能体 Supervisor 模式编排三个专业 Agent 协作完成复杂任务
- [ ] Agent 可通过 LangSmith 观测完整执行链路、Token 消耗和决策日志
- [ ] Agent 长任务通过 Celery 后台执行，支持进度查询和失败重试
- [ ] Nginx 负载均衡三个 FastAPI 实例，支持健康检查和故障转移
- [ ] 事件驱动文档摄入管道通过消息队列解耦各处理阶段
- [ ] Agent 生产化配置完备：Token 预算、超时控制、安全护栏、最大迭代次数

---

## 下阶段预告

**Phase 6** 将进入前端与全栈整合阶段，基于 Phase 5 的 Agent 后端系统构建用户交互界面。学习前端基础、React 框架、Agent 交互 UI 设计（流式输出、进度展示、审批界面），最终实现一个完整的多智能体知识库问答 Web 应用。
