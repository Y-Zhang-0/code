# Phase 6：Agent 智能体系统

> **时间**：Week 10-12（第 64-84 天）
> **总学时**：66 小时
> **目标**：构建能自主完成多步任务的 AI Agent，理解 ReAct 推理框架，掌握 Agent 异步化

---

## 本阶段里程碑

一个 Research Agent：
- 接收研究主题，自动搜索互联网获取最新信息
- 分析、整合多个来源的内容
- 生成结构化研究报告（Markdown 格式）
- 全程自主决策，无需人工干预
- 长任务异步化，支持进度查询

---

## Week 10（第 64-70 天）：Function Calling + Tool Use

### Day 64（周一，2h）：Function Calling 原理

#### 什么是 Function Calling？

```
传统 AI 对话：
用户：帮我查北京今天天气
AI：对不起，我无法获取实时信息 ❌

有了 Function Calling：
用户：帮我查北京今天天气
AI 思考：我需要调用 get_weather 工具
工具执行：调用天气 API → 返回 {"city": "北京", "temp": "15℃", "weather": "晴"}
AI：今天北京天气晴，气温 15℃ ✓
```

**核心流程（ReAct 框架）**
```
Thought（思考）：我需要做什么？需要哪个工具？
Action（行动）：调用工具 X，参数 Y
Observation（观察）：工具返回了什么结果？
Thought：基于结果，下一步怎么做？
...（循环直到有答案）
Final Answer：给出最终回答
```

#### 代码实现
```python
import json
from zhipuai import ZhipuAI
import os

client = ZhipuAI(api_key=os.getenv("ZHIPU_API_KEY"))

# 1. 定义工具（用 JSON Schema 描述）
tools = [
    {
        "type": "function",
        "function": {
            "name": "get_weather",
            "description": "获取指定城市的当前天气信息",
            "parameters": {
                "type": "object",
                "properties": {
                    "city": {
                        "type": "string",
                        "description": "城市名称，例如：北京、上海"
                    }
                },
                "required": ["city"]
            }
        }
    }
]

# 2. 实际的工具函数
def get_weather(city: str) -> str:
    # 真实场景调用天气 API，这里模拟
    weather_data = {
        "北京": {"temp": "15℃", "weather": "晴", "humidity": "30%"},
        "上海": {"temp": "20℃", "weather": "多云", "humidity": "70%"},
    }
    data = weather_data.get(city, {"error": f"未找到城市：{city}"})
    return json.dumps(data, ensure_ascii=False)

# 3. 工具执行器
TOOL_FUNCTIONS = {
    "get_weather": get_weather,
}

def execute_tool(tool_call) -> str:
    name = tool_call.function.name
    args = json.loads(tool_call.function.arguments)
    func = TOOL_FUNCTIONS.get(name)
    if not func:
        return f"工具不存在：{name}"
    return func(**args)

# 4. Agent 循环
def run_agent(user_query: str) -> str:
    messages = [{"role": "user", "content": user_query}]

    while True:
        response = client.chat.completions.create(
            model="glm-4-flash",
            messages=messages,
            tools=tools,
        )

        choice = response.choices[0]

        # 如果 AI 决定调用工具
        if choice.finish_reason == "tool_calls":
            assistant_msg = choice.message
            messages.append(assistant_msg)  # 把 AI 的工具调用记录加入历史

            # 执行所有工具调用
            for tool_call in assistant_msg.tool_calls:
                result = execute_tool(tool_call)
                print(f"[工具调用] {tool_call.function.name}: {result}")

                # 把工具结果加入消息历史
                messages.append({
                    "role": "tool",
                    "tool_call_id": tool_call.id,
                    "content": result
                })

        # 如果 AI 给出最终回答
        elif choice.finish_reason == "stop":
            return choice.message.content

result = run_agent("北京今天天气怎么样？适合出行吗？")
print(f"最终回答：{result}")
```

#### 今日检查点
- [ ] 理解 Function Calling 的工作流程
- [ ] 能定义工具的 JSON Schema
- [ ] 实现了基础的 Agent 调用循环

---

### Day 65-66（周二-周三，各 2h）：实用工具集成

#### Day 65：搜索工具（Tavily）
```bash
pip install tavily-python
# 申请免费 API Key：https://tavily.com/
```

```python
from tavily import TavilyClient

tavily = TavilyClient(api_key=os.getenv("TAVILY_API_KEY"))

def search_web(query: str, max_results: int = 5) -> str:
    """搜索互联网获取最新信息"""
    results = tavily.search(query=query, max_results=max_results)
    formatted = []
    for r in results["results"]:
        formatted.append(f"标题：{r['title']}\nURL：{r['url']}\n内容：{r['content'][:300]}")
    return "\n\n---\n\n".join(formatted)
```

#### Day 66：代码执行工具 + 计算工具
```python
import subprocess
import ast

def execute_python(code: str) -> str:
    """安全执行 Python 代码（仅限数学计算和数据处理）"""
    # 安全检查：只允许基础操作
    forbidden = ["import os", "import sys", "open(", "exec(", "eval("]
    for f in forbidden:
        if f in code:
            return f"错误：不允许执行 {f}"

    try:
        result = subprocess.run(
            ["python", "-c", code],
            capture_output=True, text=True, timeout=5
        )
        return result.stdout or result.stderr
    except subprocess.TimeoutExpired:
        return "错误：执行超时"

def calculator(expression: str) -> str:
    """安全计算数学表达式"""
    try:
        # 只允许数字和基础运算符
        tree = ast.parse(expression, mode='eval')
        result = eval(compile(tree, '<string>', 'eval'))
        return str(result)
    except Exception as e:
        return f"计算错误：{e}"
```

---

### Day 67-68（周四-周五，各 2h）：错误处理与重试

```python
import time
from functools import wraps

def with_retry(max_retries=3, delay=1):
    """重试装饰器"""
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            for attempt in range(max_retries):
                try:
                    return func(*args, **kwargs)
                except Exception as e:
                    if attempt < max_retries - 1:
                        print(f"第 {attempt+1} 次失败：{e}，{delay}秒后重试...")
                        time.sleep(delay * (2 ** attempt))
                    else:
                        raise
        return wrapper
    return decorator

# Agent 增加最大步数限制（防止死循环）
def run_agent_safe(user_query: str, max_steps: int = 10) -> str:
    messages = [{"role": "user", "content": user_query}]
    step = 0

    while step < max_steps:
        step += 1
        print(f"\n[步骤 {step}/{max_steps}]")

        try:
            response = client.chat.completions.create(
                model="glm-4-flash",
                messages=messages,
                tools=tools,
                timeout=30
            )
        except Exception as e:
            return f"API 调用失败：{e}"

        choice = response.choices[0]

        if choice.finish_reason == "tool_calls":
            # ... 处理工具调用
            pass
        else:
            return choice.message.content

    return f"达到最大步数限制（{max_steps}），当前状态：任务未完成"
```

---

### Day 69-70（周末，6h×2）：多工具 Agent 实战

**Day 69（6h）**：构建一个能搜索+计算的综合 Agent

工具集：
1. `search_web(query)` — 搜索互联网
2. `calculator(expression)` — 数学计算
3. `get_current_time()` — 获取当前时间
4. `save_to_file(content, filename)` — 保存结果

测试任务：
- "帮我搜索最近的 AI 发展新闻，总结 3 条"
- "1+1等于几？然后搜索这个结果的意义"

**Day 70（6h）**：添加工具调用日志和可视化

---

## Week 11（第 71-77 天）：LangGraph Agent 框架

### Day 71-72（周一-周二，各 2h）：LangGraph — 状态机式 Agent（主线）

> LangGraph 是 LangChain 官方 2024 年推出的 Agent 框架，已替代 AgentExecutor 成为主推方案。
> 核心思想：把 Agent 的推理过程建模为**有状态的图（Graph）**，比 AgentExecutor 更可控、更稳定。

```bash
pip install langgraph
```

```python
from typing import TypedDict, Annotated
from langgraph.graph import StateGraph, END
from langgraph.prebuilt import ToolNode
from langchain_core.messages import HumanMessage, AIMessage
from langchain_openai import ChatOpenAI
from langchain_core.tools import tool

# Step 1: 定义 Agent 状态（类似 Redux 的 state）
class AgentState(TypedDict):
    messages: list  # 对话历史
    # 可扩展：iteration_count, error_count, task_complete 等

# Step 2: 定义工具
@tool
def search_web(query: str) -> str:
    """搜索互联网获取最新信息"""
    return f"搜索结果：{query} 的相关信息..."

@tool
def calculator(expression: str) -> str:
    """计算数学表达式"""
    import ast
    tree = ast.parse(expression, mode='eval')
    return str(eval(compile(tree, '<string>', 'eval')))

tools = [search_web, calculator]

# Step 3: 定义节点（每个节点是一个处理函数）
llm = ChatOpenAI(model="gpt-4o-mini", temperature=0)
llm_with_tools = llm.bind_tools(tools)

def agent_node(state: AgentState) -> AgentState:
    """LLM 推理节点：决定下一步行动"""
    response = llm_with_tools.invoke(state["messages"])
    return {"messages": state["messages"] + [response]}

tool_node = ToolNode(tools)  # 工具执行节点（自动调用对应工具函数）

# Step 4: 定义路由逻辑（控制流）
def should_continue(state: AgentState) -> str:
    last_message = state["messages"][-1]
    if hasattr(last_message, "tool_calls") and last_message.tool_calls:
        return "tools"   # → 执行工具
    return END           # → 结束

# Step 5: 构建图
graph = StateGraph(AgentState)

graph.add_node("agent", agent_node)
graph.add_node("tools", tool_node)

graph.set_entry_point("agent")
graph.add_conditional_edges(
    "agent",
    should_continue,
    {"tools": "tools", END: END}
)
graph.add_edge("tools", "agent")  # 工具执行完回到 agent 继续推理

app = graph.compile()

# Step 6: 运行
result = app.invoke({
    "messages": [HumanMessage(content="帮我搜索最近的 AI 新闻，然后统计一下有多少条")]
})
print(result["messages"][-1].content)
```

**LangGraph vs AgentExecutor 对比**

| 维度 | AgentExecutor（旧） | LangGraph（新） |
|:---|:---|:---|
| 控制流 | 黑盒循环 | 显式图结构，每步可见 |
| 状态管理 | 隐式 | 显式 TypedDict，可随时检查 |
| 中断/审批 | 不支持 | 原生支持（Human-in-the-loop）|
| 调试 | 困难 | LangSmith 可视化每个节点 |
| 适用场景 | 简单 Agent | 复杂多步 Agent、生产环境 |

### Day 73-74（周三-周四，各 2h）：LangGraph 进阶 — Memory 与 Human-in-the-loop

**Agent Memory：跨会话记忆**

```python
from langgraph.checkpoint.memory import MemorySaver
from langgraph.checkpoint.sqlite import SqliteSaver

# 短期记忆：会话内记忆（默认）
# messages 列表就是短期记忆，会话结束即消失

# 长期记忆：跨会话持久化
# 使用 checkpointer 保存/恢复 Agent 状态

# 内存存储（开发测试用）
checkpointer = MemorySaver()

# SQLite 持久化（生产环境）
checkpointer = SqliteSaver.from_conn_string("./agent_memory.db")

app = graph.compile(checkpointer=checkpointer)

# 每次调用传入 thread_id，自动关联历史状态
config = {"configurable": {"thread_id": "user_123_session_1"}}

# 第一轮
result1 = app.invoke(
    {"messages": [HumanMessage(content="我叫张三")]},
    config=config
)

# 第二轮（自动恢复上一轮状态）
result2 = app.invoke(
    {"messages": [HumanMessage(content="我叫什么名字？")]},
    config=config
)
# AI 会回答：你叫张三（因为记住了上一轮）
```

**Human-in-the-loop：关键操作需人工审批**

```python
# 场景：Agent 要执行危险操作（删除文件、发邮件、下单）时，先暂停等人审批

from langgraph.graph import StateGraph, END, interrupt_before

# 定义一个需要审批的"危险操作"节点
def dangerous_action(state: AgentState) -> AgentState:
    """执行危险操作（如发送邮件、修改数据库）"""
    # 这个节点会在执行前被 interrupt
    print("执行危险操作...")
    return {"messages": state["messages"] + [AIMessage(content="操作已执行")]}

graph.add_node("dangerous_action", dangerous_action)

# 编译时指定在哪些节点前中断
app = graph.compile(
    checkpointer=checkpointer,
    interrupt_before=["dangerous_action"]  # 执行前中断，等人审批
)

# 运行到 dangerous_action 前自动暂停
config = {"configurable": {"thread_id": "approval_flow_1"}}
result = app.invoke({"messages": [HumanMessage(content="帮我发邮件给所有用户")]}, config=config)
# → Agent 推理后判断需要调用 dangerous_action，此时暂停

# 人工查看当前状态
current_state = app.get_state(config)
print("待审批操作：", current_state.next)  # ('dangerous_action',)

# 人工审批：继续执行
user_approved = True
if user_approved:
    final_result = app.invoke(None, config=config)  # None = 继续，不添加新消息
else:
    # 拒绝：修改状态后继续（或直接结束）
    app.update_state(config, {"messages": [..., AIMessage(content="操作已取消")]})
```

### Day 75-76（周五 + 周六，2h + 6h）：CrewAI 了解 + Research Agent 完整实现

```bash
pip install crewai crewai-tools
```

```python
from crewai import Agent, Task, Crew, Process
from crewai_tools import SerperDevTool

# 多 Agent 协作：每个 Agent 专注一件事
search_tool = SerperDevTool()

# Agent 1：研究员
researcher = Agent(
    role="研究员",
    goal="搜索并收集关于{topic}的最新、最全面的信息",
    backstory="你是一个专业的互联网研究员，擅长快速找到高质量信息",
    tools=[search_tool],
    verbose=True,
    llm=ChatOpenAI(model="gpt-4o-mini")
)

# Agent 2：分析师
analyst = Agent(
    role="内容分析师",
    goal="分析研究员提供的信息，提炼关键洞察",
    backstory="你是一个资深分析师，擅长从大量信息中提炼精华",
    verbose=True,
    llm=ChatOpenAI(model="gpt-4o-mini")
)

# Agent 3：写作者
writer = Agent(
    role="报告写作者",
    goal="将分析结果写成专业、易读的报告",
    backstory="你是一个优秀的技术写作者，文章结构清晰，表达准确",
    verbose=True,
    llm=ChatOpenAI(model="gpt-4o-mini")
)

# 任务
task1 = Task(
    description="搜索关于 {topic} 的最新信息，收集至少 5 个可靠来源",
    agent=researcher,
    expected_output="结构化的信息列表，包含来源URL"
)

task2 = Task(
    description="基于研究员收集的信息，分析关键趋势和洞察",
    agent=analyst,
    expected_output="洞察摘要，列出 3-5 个关键发现"
)

task3 = Task(
    description="将分析结果写成一份完整的研究报告（Markdown格式）",
    agent=writer,
    expected_output="完整的 Markdown 格式研究报告"
)

# 执行（顺序模式）
crew = Crew(
    agents=[researcher, analyst, writer],
    tasks=[task1, task2, task3],
    process=Process.sequential,  # 顺序执行
    verbose=True
)

result = crew.kickoff(inputs={"topic": "2025年大型语言模型发展趋势"})
print(result.raw)
```

> CrewAI 适合快速搭建多 Agent 协作场景，了解核心概念即可，生产环境仍推荐 LangGraph。

```python
# research_agent.py — 完整版 Research Agent
import os
import json
from datetime import datetime
from pathlib import Path

class ResearchAgent:
    def __init__(self):
        self.output_dir = Path("reports")
        self.output_dir.mkdir(exist_ok=True)

    def research(self, topic: str) -> str:
        """执行研究任务，生成报告"""
        print(f"\n🔍 开始研究：{topic}")
        print("=" * 50)

        crew = self._build_crew()
        result = crew.kickoff(inputs={"topic": topic})

        # 保存报告
        filename = f"report_{datetime.now().strftime('%Y%m%d_%H%M%S')}.md"
        filepath = self.output_dir / filename
        with open(filepath, "w", encoding="utf-8") as f:
            f.write(result.raw)

        print(f"\n✅ 报告已保存到：{filepath}")
        return result.raw

    def _build_crew(self):
        # ... 组装 Crew（见上方代码）
        pass

if __name__ == "__main__":
    agent = ResearchAgent()
    topic = input("请输入研究主题：")
    report = agent.research(topic)
    print("\n=== 报告预览 ===")
    print(report[:500] + "...")
```

### Day 77（周日，6h）：里程碑 4 完善 + 复习

- 测试 Research Agent（至少 3 个不同主题）
- 对比 CrewAI 多 Agent vs 单 Agent 的效果
- 整理代码，推送 GitHub
- 总结 Agent 开发中遇到的问题和解决方案

---

## Week 12（第 78-84 天）：Agent 进阶 + 异步化

### Day 78-79（周一-周二，各 2h）：Agent 可观测性

```bash
pip install langsmith
```

```python
# 设置 LangSmith（免费 Tracing）
import os
os.environ["LANGCHAIN_TRACING_V2"] = "true"
os.environ["LANGCHAIN_API_KEY"] = "你的LangSmith Key"
os.environ["LANGCHAIN_PROJECT"] = "my-agent"

# 之后所有 LangChain 调用会自动被追踪
# 在 https://smith.langchain.com/ 查看调用链路
```

### Day 80-81（周三-周四，各 2h）：Agent 稳定性优化 + RAG + Agent 融合

**Day 80：Agent 稳定性优化**

```python
# 常见问题和解决方案

# 问题1：工具参数解析错误
# 解决：增加输出验证
from langchain.output_parsers import RetryWithErrorOutputParser

# 问题2：Agent 反复调用相同工具
# 解决：记录已执行的工具调用，避免重复
class DeduplicatedExecutor:
    def __init__(self):
        self.executed_calls = set()

    def should_execute(self, tool_name: str, args: str) -> bool:
        key = f"{tool_name}:{args}"
        if key in self.executed_calls:
            return False
        self.executed_calls.add(key)
        return True

# 问题3：LLM 输出格式不正确
# 解决：使用结构化输出 + 验证
from pydantic import BaseModel, validator

class AgentDecision(BaseModel):
    thought: str
    action: str
    action_input: str

    @validator("action")
    def action_must_be_valid(cls, v, values):
        valid_actions = ["search", "calculator", "finish"]
        if v not in valid_actions:
            raise ValueError(f"无效的 action：{v}")
        return v
```

**Day 81：RAG + Agent 融合**

构建一个结合 RAG + Agent 的智能问答系统

场景：公司内部知识库助手
- 优先查本地知识库（RAG）
- 知识库没有时，自动搜索互联网
- 复杂问题分步骤解决

```python
class IntelligentAssistant:
    def __init__(self):
        self.rag_engine = get_rag_engine()  # 你的 RAG 系统
        self.agent = build_research_agent() # 你的 Agent

    def answer(self, question: str) -> dict:
        # 先尝试 RAG
        rag_result = self.rag_engine.query(question)

        if rag_result["confidence"] > 0.8:
            # RAG 有把握回答
            return {"source": "knowledge_base", "answer": rag_result["answer"]}
        else:
            # RAG 没把握，交给 Agent 搜索
            agent_result = self.agent.run(question)
            return {"source": "internet_search", "answer": agent_result}
```

### Day 82（周五，2h）：Agent 长任务问题

**问题场景**：Research Agent 执行复杂研究任务时，可能需要 5-10 分钟

```
用户：帮我研究"量子计算在金融领域的应用"
API：[等待 8 分钟...] → 超时 ❌

问题：
1. HTTP 请求超时（通常 30-60 秒）
2. 用户体验差（长时间等待无反馈）
3. 服务器资源被长时间占用
```

**解决方案**：引入 Celery 异步任务队列

```
用户 → API → 立即返回 {task_id: "abc123"}
           ↓
       Celery Worker 后台执行 Agent
           ↓
       用户轮询 /tasks/abc123 → 查看进度/结果
```

### Day 83-84（周末，6h×2）：Celery 异步化 Agent

**Day 83（6h）**：集成 Celery 到 Agent 系统

```bash
pip install celery redis flower
```

```python
# tasks.py — Agent 异步任务
from celery import Celery
from research_agent import ResearchAgent

app = Celery(
    "agent_tasks",
    broker="redis://localhost:6379/0",
    backend="redis://localhost:6379/1",
)

@app.task(bind=True, soft_time_limit=600, time_limit=660)
def research_task(self, topic: str) -> dict:
    """异步执行研究任务"""
    try:
        # 更新进度：开始研究
        self.update_state(state="STARTED", meta={"progress": 0, "step": "初始化 Agent"})

        agent = ResearchAgent()

        # 更新进度：搜索中
        self.update_state(state="STARTED", meta={"progress": 30, "step": "搜索信息"})

        # 执行研究（这里可能需要几分钟）
        report = agent.research(topic)

        # 更新进度：完成
        self.update_state(state="STARTED", meta={"progress": 100, "step": "生成报告"})

        return {"status": "done", "report": report}

    except Exception as exc:
        # 失败自动重试
        raise self.retry(exc=exc, countdown=10, max_retries=2)
```

```python
# main.py — FastAPI 集成
from fastapi import FastAPI
from tasks import research_task
from celery.result import AsyncResult

app = FastAPI()

@app.post("/research")
async def create_research(topic: str):
    """提交研究任务"""
    task = research_task.delay(topic)
    return {
        "task_id": task.id,
        "status": "queued",
        "message": "研究任务已提交，后台处理中"
    }

@app.get("/tasks/{task_id}")
async def get_task_status(task_id: str):
    """查询任务状态"""
    result = AsyncResult(task_id)

    response = {
        "task_id": task_id,
        "status": result.status,  # PENDING / STARTED / SUCCESS / FAILURE
    }

    if result.status == "STARTED":
        # 返回进度信息
        response["progress"] = result.info.get("progress", 0)
        response["step"] = result.info.get("step", "")
    elif result.ready():
        # 任务完成，返回结果
        response["result"] = result.result

    return response
```

**启动服务**

```bash
# 终端 1：启动 Redis
redis-server

# 终端 2：启动 Celery Worker
celery -A tasks worker --loglevel=info --concurrency=2

# 终端 3：启动 Flower 监控（可选）
celery -A tasks flower --port=5555

# 终端 4：启动 FastAPI
uvicorn main:app --reload
```

**测试流程**

```bash
# 1. 提交研究任务
curl -X POST "http://localhost:8000/research?topic=量子计算在金融领域的应用"
# 返回：{"task_id": "abc123", "status": "queued"}

# 2. 轮询任务状态
curl "http://localhost:8000/tasks/abc123"
# 返回：{"task_id": "abc123", "status": "STARTED", "progress": 30, "step": "搜索信息"}

# 3. 任务完成后
curl "http://localhost:8000/tasks/abc123"
# 返回：{"task_id": "abc123", "status": "SUCCESS", "result": {"status": "done", "report": "..."}}
```

**Day 84（6h）**：优化与监控

1. **任务优先级**：重要任务优先处理

```python
# 高优先级任务
research_task.apply_async(args=[topic], priority=9)

# 普通任务
research_task.apply_async(args=[topic], priority=5)
```

2. **任务超时处理**

```python
@app.task(bind=True, soft_time_limit=600, time_limit=660)
def research_task(self, topic: str):
    try:
        # ... 执行任务
        pass
    except SoftTimeLimitExceeded:
        # 软超时：保存当前进度，返回部分结果
        return {"status": "partial", "message": "任务超时，返回部分结果"}
```

3. **Flower 监控面板**

4. **多队列路由**（任务分类处理）

```python
# 配置任务路由
app.conf.task_routes = {
    "tasks.research_task": {"queue": "research"},  # 研究任务（慢）
    "tasks.quick_query": {"queue": "quick"},       # 快速查询（快）
}

# 启动不同队列的 Worker
# celery -A tasks worker -Q research --concurrency=2  # 研究队列，少并发
# celery -A tasks worker -Q quick --concurrency=8     # 快速队列，多并发
```

5. **失败重试策略**

```python
@app.task(bind=True, autoretry_for=(Exception,), retry_kwargs={"max_retries": 3})
def research_task(self, topic: str):
    # 失败自动重试，最多 3 次
    pass
```

访问 `http://localhost:5555` 查看：
- Worker 状态（在线/离线）
- 任务执行历史
- 队列积压情况
- 任务平均执行时间

4. **错误处理与重试**

```python
@app.task(bind=True, autoretry_for=(Exception,), retry_kwargs={'max_retries': 3, 'countdown': 10})
def research_task(self, topic: str):
    # 遇到异常自动重试，最多 3 次，每次间隔 10 秒
    pass
```

**今日检查点**：
- [ ] Agent 任务能异步执行，不阻塞 API
- [ ] 能通过 task_id 查询任务进度
- [ ] Flower 监控面板正常工作
- [ ] 理解为什么 Agent 需要异步化（长任务 + 用户体验）

---

## Phase 6 总结

**Week 10 总结检查点**：
- [ ] 理解 Function Calling 和 ReAct 推理框架
- [ ] 能定义和集成多种工具（搜索、计算、文件操作）
- [ ] 实现了基础的 Agent 调用循环
- [ ] 掌握错误处理与重试机制

**Week 11 总结检查点**：
- [ ] 理解 LangGraph 状态机式 Agent 架构
- [ ] 能用 LangGraph 构建复杂 Agent
- [ ] 掌握 Agent Memory 和 Human-in-the-loop
- [ ] 了解 CrewAI 多 Agent 协作框架
- [ ] 完成 Research Agent 里程碑项目

**Week 12 总结检查点**：
- [ ] 掌握 LangSmith 可观测性工具
- [ ] 能优化 Agent 稳定性（去重、验证、结构化输出）
- [ ] 理解 RAG + Agent 融合场景
- [ ] 掌握 Celery 异步化 Agent 长任务
- [ ] 能用 Flower 监控任务执行状态

**下周预告**：工程化与部署，让你的系统真正上线运行。
