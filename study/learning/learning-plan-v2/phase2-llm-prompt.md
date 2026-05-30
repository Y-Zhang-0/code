# Phase 2：LLM API 多厂商 + Prompt Engineering + MCP 入门

> **时间**：Week 2-4（D8-D28，78 小时）
> **前提**：Phase 1 Python 基础完成
> **目标**：掌握多厂商 LLM API 调用、系统化 Prompt 工程、MCP 协议入门

---

## Week 2（D8-D14）：LLM API 多厂商

### D8：Claude API 基础

**学习内容**

Messages API 完整调用流程。重点掌握 system prompt 设置、user/assistant 角色轮转、streaming 响应处理、max_tokens 与 temperature 参数的实际影响。通过实际调用理解请求/响应结构，观察不同 temperature 下输出的差异。

**检查点**

- [ ] 能独立完成 Claude Messages API 的完整调用（非 streaming）
- [ ] 能实现 streaming 响应并逐 chunk 处理
- [ ] 理解 system prompt 与 user message 的区别及使用场景
- [ ] 能解释 temperature 0 vs 1 对输出的影响，并用实例验证
- [ ] 理解 max_tokens 的计费含义与截断行为

### D9：Claude Structured Output

**学习内容**

通过 tool_use 机制实现强制 JSON Schema 输出——这是现代结构化输出的正确方式，而非在 prompt 中要求"请返回 JSON"。定义 tool schema，使用 `tool_choice: {"type": "tool", "name": "..."}` 强制模型按 schema 生成。理解 tool_use 与 function calling 的本质：让模型填充预定义结构。

**检查点**

- [ ] 能定义 tool schema 并通过 tool_use 获取结构化 JSON 输出
- [ ] 理解 tool_choice 的三种模式（auto / any / tool）
- [ ] 能解释为什么 tool_use 比 prompt-based JSON 更可靠
- [ ] 实现一个提取结构化信息的示例（如从文本提取人名、日期、事件）

### D10：Claude Prompt Caching

**学习内容**

Prompt Caching 机制与 cache_control blocks 的使用方式。理解哪些场景适合缓存（大段 system prompt、长文档上下文、few-shot 示例集），如何在请求中标记缓存边界，缓存命中时的成本节省比例。对比有无缓存时的延迟与费用差异。

**检查点**

- [ ] 能在 API 请求中正确设置 cache_control 块
- [ ] 理解缓存的生效条件（前缀匹配、TTL）
- [ ] 能计算缓存命中 vs 未命中的成本差异
- [ ] 能判断给定场景是否适合使用 Prompt Caching

### D11：OpenAI API

**学习内容**

OpenAI Chat Completions API 调用流程。对比 Claude API 的差异：消息格式、function calling vs tool_use、response_format（JSON mode）、streaming 实现方式。理解 OpenAI 的 function calling 机制及其与 Claude tool_use 的异同。

**检查点**

- [ ] 能独立完成 OpenAI Chat Completions API 调用
- [ ] 能使用 function calling 获取结构化输出
- [ ] 能使用 response_format 启用 JSON mode
- [ ] 能列出 Claude API 与 OpenAI API 的至少 5 个关键差异
- [ ] 理解两家 streaming 实现的协议差异（SSE 细节）

### D12：智谱 AI API

**学习内容**

智谱 AI GLM-4-flash 免费模型的 API 调用。了解国产大模型生态：注册流程、SDK 安装、API 兼容性（兼容 OpenAI 格式的程度）。对比三家 API 的调用风格差异，为 D13-D14 的抽象层设计做准备。

**检查点**

- [ ] 能独立完成智谱 AI GLM-4-flash API 调用
- [ ] 理解智谱 SDK 与 OpenAI SDK 的兼容程度
- [ ] 能对比三家 API 在消息格式、参数命名、响应结构上的差异
- [ ] 整理出统一抽象层需要处理的差异清单

### D13（周六 8h）：实战——多厂商 LLM 客户端抽象层

**学习内容**

设计并实现统一的多厂商 LLM 客户端。定义抽象接口（同步/streaming 调用、结构化输出），使用 Provider 模式封装各厂商差异。重点关注：接口设计的取舍（最大公约数 vs 最小公倍数）、错误处理统一、配置管理。

**检查点**

- [ ] 抽象接口定义完成，覆盖：普通调用、streaming、结构化输出
- [ ] Claude Provider 实现并通过基础调用测试
- [ ] OpenAI Provider 实现并通过基础调用测试
- [ ] Provider 注册与切换机制可用
- [ ] 错误处理统一（网络错误、API 错误、限流错误）

### D14（周日 8h）：实战——三厂商 Provider 切换 + 统一测试

**学习内容**

完成智谱 Provider 实现，编写统一测试套件验证三个 Provider 行为一致性。实现 streaming 的统一封装，确保相同的调用代码可以无缝切换 Provider。编写集成测试验证端到端流程。

**检查点**

- [ ] 智谱 Provider 实现并通过基础调用测试
- [ ] 统一测试套件覆盖三个 Provider 的基础调用
- [ ] streaming 在三个 Provider 上行为一致
- [ ] 结构化输出在支持的 Provider 上正常工作
- [ ] Provider 切换无需修改业务代码，仅改配置

---

## Week 3（D15-D21）：Prompt Engineering + MCP 入门

### D15：Prompt 基础

**学习内容**

系统学习四大基础 Prompt 技术。Role Prompting：通过角色设定约束模型行为边界。Few-shot：提供示例引导输出格式与风格。Chain-of-Thought（CoT）：引导模型展示推理过程以提升复杂任务准确率。格式控制：通过明确的输出格式指令确保可解析输出。

**检查点**

- [ ] 能为同一任务分别编写 zero-shot、few-shot、CoT 版本的 prompt
- [ ] 能解释 Role Prompting 的作用机制与适用场景
- [ ] Few-shot 示例的选择原则（多样性、边界覆盖、格式一致）
- [ ] CoT 对简单任务 vs 复杂推理任务的效果差异
- [ ] 能通过格式指令让模型输出 Markdown 表格、编号列表等结构

### D16：Prompt 进阶

**学习内容**

进阶 Prompt 技术。Self-Consistency：多次采样取多数投票，提升推理可靠性。Tree-of-Thought：让模型探索多条推理路径并自我评估。Prompt Chaining：将复杂任务拆解为多步 prompt 串联，每步结果作为下步输入。理解各技术的适用场景与成本权衡。

**检查点**

- [ ] 能实现 Self-Consistency 采样并编写投票逻辑
- [ ] 能编写 Tree-of-Thought 风格的 prompt 并解释其结构
- [ ] 能将一个复杂任务拆解为 3+ 步 Prompt Chain
- [ ] 理解各技术的 token 成本与延迟影响
- [ ] 能根据任务特征选择合适的 Prompt 策略

### D17：RAG 专用 Prompt

**学习内容**

RAG 场景下的 Prompt 设计。上下文注入模板：如何将检索到的文档片段嵌入 prompt。引用要求：让模型标注信息来源。"仅基于上下文回答"约束：防止模型编造信息。处理上下文不足的情况：模型应明确表示无法回答而非猜测。多文档冲突处理。

**检查点**

- [ ] 能编写包含上下文注入的 RAG prompt 模板
- [ ] 模型能在回答中正确标注引用来源
- [ ] "仅基于上下文"约束有效，模型不会编造超出上下文的内容
- [ ] 上下文不足时模型能正确拒答
- [ ] 能处理多段上下文的优先级与冲突

### D18：Prompt 测试与评估

**学习内容**

建立 Prompt 的系统化测试与评估方法。设计测试用例集（正常 case、边界 case、对抗 case）。定义评估指标（准确率、格式符合率、延迟、成本）。A/B 对比方法论：控制变量、样本量、统计显著性。设计可复用的 Prompt 测试脚手架。

**检查点**

- [ ] 能为一个 prompt 设计至少 10 个测试用例（含边界与对抗）
- [ ] 能定义并计算至少 3 个评估指标
- [ ] 理解 A/B 测试的基本方法论与常见陷阱
- [ ] 设计出 Prompt 测试脚手架的核心接口
- [ ] 能解释为什么 Prompt 测试需要多次运行取统计值

### D19：MCP 协议入门

**学习内容**

Model Context Protocol（MCP）的核心概念与架构。理解 MCP 解决的问题：LLM 与外部工具/数据源的标准化连接。Server-Client 模型：MCP Server 暴露 tools/resources/prompts，Client（如 Claude Desktop）发现并调用。传输层协议（stdio、SSE）。MCP 在 Agent 系统中的角色与价值。

**检查点**

- [ ] 能清晰解释 MCP 是什么以及它解决什么问题
- [ ] 理解 MCP Server 的三种能力（tools / resources / prompts）
- [ ] 理解 MCP 的 Server-Client 架构与通信流程
- [ ] 能区分 stdio 与 SSE 两种传输方式的适用场景
- [ ] 能解释 MCP 与直接 function calling 的区别与优势

### D20（周六 8h）：实战——Prompt 工程工作台 CLI

**学习内容**

构建一个 CLI 工具用于 Prompt 工程的日常工作。功能：加载 prompt 模板、跨模型运行测试（复用 Week 2 的多厂商客户端）、保存运行结果、对比不同 prompt 版本的输出质量。将 D18 设计的测试脚手架落地为可用工具。

**检查点**

- [ ] CLI 能加载 prompt 模板文件并填充变量
- [ ] 能对同一 prompt 在多个模型上运行并收集结果
- [ ] 运行结果能持久化保存（JSON/SQLite）
- [ ] 能对比两个 prompt 版本在同一测试集上的表现
- [ ] 集成 D18 设计的评估指标自动计算

### D21（周日 8h）：实战——MCP Server 基础

**学习内容**

使用 Python MCP SDK 实现一个文件系统工具 MCP Server。暴露基础工具（读取文件、列出目录、搜索文件内容），通过 Claude Desktop 连接测试。理解 MCP Server 的开发流程：定义工具 schema、实现处理函数、配置传输层、在客户端注册。

**检查点**

- [ ] MCP Server 能启动并响应 Client 的能力发现请求
- [ ] 至少实现 3 个文件系统工具（读、列、搜）
- [ ] 工具 schema 定义正确，参数验证有效
- [ ] 能通过 Claude Desktop 成功连接并调用工具
- [ ] 理解 MCP Server 的调试方法与日志查看

---

## Week 4（D22-D28）：进阶 API + Buffer

### D22：Claude Vision API

**学习内容**

Claude 的多模态能力。图片分析：传入图片并获取描述/分析结果。文档 OCR：从图片中提取文本内容。多模态 prompt 设计：如何组合文本与图片指令以获得最佳结果。支持的图片格式、尺寸限制、token 计算方式。

**检查点**

- [ ] 能通过 API 发送图片并获取分析结果（base64 和 URL 两种方式）
- [ ] 能实现基础的文档 OCR（图片转文字）
- [ ] 理解图片的 token 消耗计算方式
- [ ] 能编写有效的多模态 prompt（文本 + 图片组合指令）
- [ ] 将 Vision 能力集成到 Week 2 的多厂商客户端中

### D23：Token 计算 + 成本估算 + 限流策略

**学习内容**

Token 的本质与计算方法。使用 tiktoken 计算 OpenAI 模型的 token 数，Claude 的 token 计算方式。三家厂商的计费模型对比（输入/输出单价、缓存折扣）。限流策略：理解 RPM/TPM 限制、429 响应处理、请求队列设计。

**检查点**

- [ ] 能使用 tiktoken 计算给定文本的 token 数
- [ ] 能对比三家厂商同级别模型的单次调用成本
- [ ] 理解 RPM（每分钟请求数）和 TPM（每分钟 token 数）限制
- [ ] 能实现基础的请求限流器（令牌桶或滑动窗口）
- [ ] 能估算一个 RAG 系统的月度 API 成本

### D24：安全——内容过滤与 Prompt 注入防御

**学习内容**

LLM 应用安全的核心议题。内容过滤：各厂商的安全策略与内容审核机制。Prompt 注入攻击：直接注入、间接注入（通过检索内容）、越狱攻击。防御措施：输入清洗、system prompt 保护、输出验证、权限最小化。System prompt 泄露防护。

**检查点**

- [ ] 能解释 Prompt 注入的三种主要形式并给出示例
- [ ] 能实现基础的输入清洗函数（检测常见注入模式）
- [ ] 理解 system prompt 泄露的风险与防护方法
- [ ] 能解释间接注入在 RAG 场景中的特殊风险
- [ ] 能设计一个基础的安全检查 pipeline（输入检查 -> 调用 -> 输出验证）

### D25：API 最佳实践

**学习内容**

生产级 LLM API 调用的工程实践。重试策略：指数退避（exponential backoff）+ 抖动（jitter）。多 Provider 降级：主 Provider 不可用时自动切换备用。熔断器模式：连续失败达到阈值时暂停调用，定期探测恢复。超时控制、请求去重、幂等性考虑。

**检查点**

- [ ] 能实现带指数退避 + 抖动的重试装饰器
- [ ] 能在多厂商客户端中实现 fallback Provider 切换
- [ ] 能解释熔断器的三种状态（关闭/打开/半开）及转换条件
- [ ] 能实现基础的熔断器逻辑
- [ ] 将重试、降级、熔断整合到 Week 2 的客户端中

### D26：复习——Phase 1-2 薄弱点回顾

**学习内容**

系统回顾 Phase 1（Python 基础）和 Phase 2 前三周的内容。识别薄弱知识点，针对性强化。重新运行之前的检查点，确认掌握程度。整理笔记与代码示例，建立个人知识索引。

**检查点**

- [ ] Phase 1 所有检查点重新自测，通过率 ≥ 90%
- [ ] Phase 2 Week 2-3 检查点重新自测，标记未通过项
- [ ] 薄弱点清单整理完成（按优先级排序）
- [ ] 至少 3 个薄弱点完成针对性强化练习
- [ ] 个人知识索引/笔记整理完成

### D27（周六 8h）：Buffer 1——复盘 + 补短板

**学习内容**

Buffer 时间，用于消化前面积累的技术债务。优先处理 D26 识别的薄弱点。完善多厂商客户端的边界情况处理。补充缺失的测试用例。如果进度超前，可以深入探索感兴趣的技术点。

**检查点**

- [ ] D26 标记的薄弱点全部完成强化
- [ ] 多厂商客户端的异常处理覆盖完善
- [ ] 所有实战项目的测试通过率 100%
- [ ] 代码质量检查通过（lint、类型检查）
- [ ] 技术笔记整理并归档

### D28（周日 8h）：Buffer 1——LLM 客户端验收

**学习内容**

Phase 2 总验收。多厂商 LLM 客户端完整功能验证：三个 Provider 的基础调用、streaming、结构化输出、prompt caching（Claude）。Prompt 工程工作台功能验证。MCP Server 基础功能验证。整体代码审查与重构。

**检查点**

- [ ] Claude Provider：基础调用 + streaming + structured output + prompt caching 全部通过
- [ ] OpenAI Provider：基础调用 + streaming + function calling 全部通过
- [ ] 智谱 Provider：基础调用 + streaming 全部通过
- [ ] Provider 切换仅需改配置，业务代码零修改
- [ ] Prompt 工程工作台能跨模型运行测试并生成对比报告
- [ ] MCP Server 能通过 Claude Desktop 正常连接与调用
- [ ] 所有代码通过 lint + 测试 + 类型检查

---

## 里程碑 2

**多厂商 LLM 客户端**（Claude / OpenAI / 智谱）with streaming + structured output + prompt caching。MCP basics working。Prompt test harness functional。

**验收标准**：

- [ ] 统一接口调用三家 LLM，Provider 切换无需改业务代码
- [ ] streaming 响应在三个 Provider 上行为一致
- [ ] Claude structured output（via tool_use）和 prompt caching 正常工作
- [ ] Prompt 工程工作台 CLI 可用（加载模板、跨模型测试、结果对比）
- [ ] MCP Server 基础实现完成，能通过 Claude Desktop 连接并调用工具
- [ ] 生产级实践集成：重试、降级、熔断、限流
- [ ] Phase 1-2 所有检查点自测通过率 ≥ 90%
