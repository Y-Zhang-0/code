# Phase 2：LLM API 调用 + Prompt Engineering

> **时间**：Week 2-3（第 8-21 天）
> **总学时**：44 小时
> **目标**：能调通大模型 API，写出高质量 Prompt，完成支持多轮对话的聊天机器人

---

## 本阶段里程碑

一个命令行聊天机器人：
- 支持多轮对话（有上下文记忆）
- 支持流式输出（逐字显示）
- 可配置角色（System Prompt）
- 对话历史保存到本地

---

## Week 2（第 8-14 天）：LLM API 调用基础

### Day 8（周一，2h）：申请 API Key + 第一个 LLM 调用

#### 上半小时：申请 API

**方案 A：智谱 AI（推荐，国内，有免费额度）**
1. 访问 https://open.bigmodel.cn/
2. 注册账号，实名认证
3. 进入「API Keys」页面，创建新的 Key
4. 复制 Key 备用（格式类似：`zhipu-xxxxx`）
5. 免费额度约 300 万 tokens（足够学习用）

**方案 B：OpenAI（效果最好，需要信用卡）**
1. 访问 https://platform.openai.com/
2. 注册账号，添加支付方式
3. 进入 API Keys，创建 Key

#### API Key 安全存储（重要）
```bash
# 不要把 Key 直接写在代码里！
# 方法：用环境变量

# Windows（PowerShell）
$env:ZHIPU_API_KEY="你的key"

# 或创建 .env 文件（更推荐）
# .env 文件内容：
ZHIPU_API_KEY=你的key

# 安装 python-dotenv 读取 .env
pip install python-dotenv
```

```python
# config.py
from dotenv import load_dotenv
import os

load_dotenv()  # 读取 .env 文件

API_KEY = os.getenv("ZHIPU_API_KEY")
if not API_KEY:
    raise ValueError("请设置 ZHIPU_API_KEY 环境变量")
```

#### 第一个 LLM 调用
```python
# 安装 SDK
pip install zhipuai  # 智谱 AI
# 或
pip install openai   # OpenAI
```

```python
# first_chat.py（智谱 AI 版本）
from zhipuai import ZhipuAI
from dotenv import load_dotenv
import os

load_dotenv()
client = ZhipuAI(api_key=os.getenv("ZHIPU_API_KEY"))

response = client.chat.completions.create(
    model="glm-4-flash",  # 免费模型
    messages=[
        {"role": "user", "content": "你好！请用一句话介绍自己。"}
    ]
)

# 提取回复内容
message = response.choices[0].message.content
print(f"AI 回复：{message}")
print(f"消耗 tokens：{response.usage.total_tokens}")
```

```python
# first_chat.py（OpenAI 版本，结构相同）
from openai import OpenAI
from dotenv import load_dotenv
import os

load_dotenv()
client = OpenAI(api_key=os.getenv("OPENAI_API_KEY"))

response = client.chat.completions.create(
    model="gpt-4o-mini",
    messages=[
        {"role": "user", "content": "你好！请用一句话介绍自己。"}
    ]
)

message = response.choices[0].message.content
print(f"AI 回复：{message}")
```

#### 今日检查点
- [ ] 成功申请并保存 API Key
- [ ] 第一次 LLM 调用成功返回结果
- [ ] 理解 `.env` 文件的作用

---

### Day 9（周二，2h）：理解 messages 结构

#### 核心概念：messages 是大模型的"记忆"

```python
# messages 是一个列表，包含对话历史
messages = [
    # system：设定 AI 的角色和规则（每次对话开头）
    {"role": "system", "content": "你是一个专业的 Python 代码审查员，只回答编程相关问题"},

    # user：用户的消息
    {"role": "user", "content": "如何用 Python 读取 CSV 文件？"},

    # assistant：AI 的回复（多轮对话时需要把历史回复也传进去）
    {"role": "assistant", "content": "可以使用 pandas 或 csv 模块..."},

    # 继续对话
    {"role": "user", "content": "pandas 怎么安装？"}
]
```

**为什么 AI 能"记住"上下文？**
```
❌ 错误理解：AI 有记忆，知道你们之前聊过什么
✓ 正确理解：每次调用都把完整的对话历史传给 AI，所以它"看起来"有记忆
```

#### 实现真正的多轮对话
```python
# multi_turn_chat.py
from zhipuai import ZhipuAI
import os
from dotenv import load_dotenv

load_dotenv()
client = ZhipuAI(api_key=os.getenv("ZHIPU_API_KEY"))

def chat(messages: list) -> str:
    response = client.chat.completions.create(
        model="glm-4-flash",
        messages=messages
    )
    return response.choices[0].message.content

# 维护对话历史
history = [
    {"role": "system", "content": "你是一个友好的 AI 学习助手，帮助用户学习 AI 应用开发"}
]

print("开始对话（输入 quit 退出）\n")

while True:
    user_input = input("你：").strip()
    if user_input.lower() == "quit":
        break

    # 把用户消息加入历史
    history.append({"role": "user", "content": user_input})

    # 把完整历史传给 AI
    response = chat(history)

    # 把 AI 回复也加入历史（下次对话时一并传入）
    history.append({"role": "assistant", "content": response})

    print(f"AI：{response}\n")
```

#### 今日检查点
- [ ] 理解 system/user/assistant 三种角色
- [ ] 能实现有上下文记忆的多轮对话
- [ ] 理解"每次都传全量历史"的原理

---

### Day 10（周三，2h）：Token、流式输出与参数调节

#### Token 是什么？
```
Token ≠ 字符，Token ≈ 词或词片段

英文：约 1 Token = 4 个字符
中文：约 1 Token = 1-2 个汉字

"Hello World" ≈ 2 tokens
"你好世界" ≈ 4 tokens

为什么重要？
- 按 Token 计费（input + output tokens）
- 模型有上下文长度限制（通常 4K-128K tokens）
- 对话历史太长时需要截断
```

#### 成本控制（生产环境必备意识）

```python
# 估算 token 数（不调 API，本地计算）
pip install tiktoken
```

```python
import tiktoken

def count_tokens(text: str, model: str = "gpt-4o-mini") -> int:
    """本地估算 token 数，避免超支"""
    enc = tiktoken.encoding_for_model(model)
    return len(enc.encode(text))

def estimate_cost(input_tokens: int, output_tokens: int, model: str = "gpt-4o-mini") -> float:
    """估算调用费用（美元）"""
    # 价格参考（2025年，以实际官网为准）
    pricing = {
        "gpt-4o-mini":  {"input": 0.15 / 1e6, "output": 0.60 / 1e6},
        "gpt-4o":       {"input": 2.50 / 1e6, "output": 10.0 / 1e6},
        "glm-4-flash":  {"input": 0.0,         "output": 0.0},  # 免费
    }
    p = pricing.get(model, pricing["gpt-4o-mini"])
    return input_tokens * p["input"] + output_tokens * p["output"]

# 使用示例
system = "你是一个助手"
user_msg = "请帮我总结这篇 5000 字的文章：" + "..." * 2500

total_input = count_tokens(system) + count_tokens(user_msg)
print(f"输入 token 数：{total_input}")
print(f"预估费用：${estimate_cost(total_input, 500):.6f}")
```

**防止超支的关键参数**

```python
response = client.chat.completions.create(
    model="gpt-4o-mini",
    messages=messages,
    max_tokens=1000,      # ← 必须设置！限制输出长度，防止模型生成过长内容
    temperature=0.7,
)

# 检查实际消耗
usage = response.usage
print(f"输入: {usage.prompt_tokens} tokens")
print(f"输出: {usage.completion_tokens} tokens")
print(f"合计: {usage.total_tokens} tokens")
print(f"本次费用: ${estimate_cost(usage.prompt_tokens, usage.completion_tokens):.6f}")
```

**学习阶段费用控制建议**

| 场景 | 建议 |
|:---|:---|
| 调试/开发 | 用 `glm-4-flash`（免费）或 Ollama 本地模型 |
| 测试 Prompt | 先用小模型验证格式，再换大模型 |
| 长文档处理 | 先打印 token 数再调用，超过 2000 tokens 要警惕 |
| 生产环境 | 设置 API 账户消费上限（OpenAI 控制台可配置）|

**流式输出（Streaming）**
```python
# 非流式：等 AI 生成完再显示（用户体验差）
response = client.chat.completions.create(
    model="glm-4-flash",
    messages=[{"role": "user", "content": "写一首关于春天的诗"}]
)
print(response.choices[0].message.content)  # 等几秒才显示

# 流式：边生成边显示（像打字机一样）
import sys

response = client.chat.completions.create(
    model="glm-4-flash",
    messages=[{"role": "user", "content": "写一首关于春天的诗"}],
    stream=True  # 开启流式
)

print("AI：", end="", flush=True)
full_response = ""

for chunk in response:
    if chunk.choices[0].delta.content:
        text = chunk.choices[0].delta.content
        print(text, end="", flush=True)  # 逐块打印，不换行
        full_response += text

print()  # 最后换行
print(f"\n完整回复长度：{len(full_response)} 字")
```

**关键参数**
```python
response = client.chat.completions.create(
    model="glm-4-flash",
    messages=messages,
    temperature=0.7,    # 随机性：0=确定性强，1=更有创意（0.7 是常用值）
    max_tokens=1000,    # 最大输出 token 数（控制回复长度）
    top_p=0.9,          # 另一种随机性控制，通常和 temperature 二选一
)

# 什么时候调 temperature？
# 写代码/数据提取：temperature=0（需要准确）
# 写文章/头脑风暴：temperature=0.8-1（需要创意）
# 一般对话：temperature=0.7（平衡）
```

#### 今日检查点
- [ ] 能开启流式输出并逐字显示
- [ ] 理解 temperature 的作用并能调整
- [ ] 理解 Token 计费逻辑

---

### Day 11（周四，2h）：结构化输出（JSON Mode）

#### 为什么需要结构化输出？
```
问题：AI 的回复是自由文本，程序难以解析
解决：让 AI 按固定 JSON 格式回复，直接解析使用
```

```python
import json
from zhipuai import ZhipuAI

client = ZhipuAI(api_key=os.getenv("ZHIPU_API_KEY"))

# 方法 1：Prompt 中要求 JSON 格式
def extract_info(text: str) -> dict:
    response = client.chat.completions.create(
        model="glm-4-flash",
        messages=[
            {
                "role": "system",
                "content": """你是信息提取助手。从用户提供的文本中提取信息，
                以 JSON 格式返回，格式如下：
                {
                    "name": "姓名",
                    "age": 年龄数字,
                    "city": "城市",
                    "skills": ["技能1", "技能2"]
                }
                只返回 JSON，不要其他文字。"""
            },
            {"role": "user", "content": text}
        ]
    )

    raw = response.choices[0].message.content

    # 处理 AI 可能包裹的 ```json 代码块
    if "```json" in raw:
        raw = raw.split("```json")[1].split("```")[0]

    return json.loads(raw.strip())

# 测试
result = extract_info("我叫李四，28岁，在上海工作，会 Python 和 JavaScript")
print(result)
# {'name': '李四', 'age': 28, 'city': '上海', 'skills': ['Python', 'JavaScript']}
```

#### 今日检查点
- [ ] 能通过 Prompt 让 AI 返回 JSON 格式
- [ ] 能解析 AI 返回的 JSON 并使用数据

---

### Day 12（周五，2h）：上下文管理与对话历史截断

#### 上下文长度限制问题

```python
# 问题：对话历史越来越长，超过模型限制会报错
# 解决方案：截断旧的对话记录

class ChatSession:
    def __init__(self, system_prompt: str, max_history: int = 10):
        self.system_prompt = system_prompt
        self.max_history = max_history  # 最多保留的对话轮数
        self.history = []

    def chat(self, user_input: str, client) -> str:
        self.history.append({"role": "user", "content": user_input})

        # 截断：只保留最近的 N 轮对话
        if len(self.history) > self.max_history * 2:
            self.history = self.history[-self.max_history * 2:]

        messages = [
            {"role": "system", "content": self.system_prompt}
        ] + self.history

        response = client.chat.completions.create(
            model="glm-4-flash",
            messages=messages,
            stream=True
        )

        full_response = ""
        for chunk in response:
            if chunk.choices[0].delta.content:
                text = chunk.choices[0].delta.content
                print(text, end="", flush=True)
                full_response += text
        print()

        self.history.append({"role": "assistant", "content": full_response})
        return full_response

    def save(self, filepath: str):
        import json
        with open(filepath, "w", encoding="utf-8") as f:
            json.dump(self.history, f, ensure_ascii=False, indent=2)
```

#### 今日检查点
- [ ] 理解上下文长度限制
- [ ] 实现对话历史截断

---

### Day 13（周六，6h）：Prompt Engineering 基础

#### 上午（3h）：核心 Prompt 技巧

**技巧 1：清晰的角色设定（Role Prompting）**
```python
# 差的 System Prompt
bad_system = "你是助手，帮我回答问题"

# 好的 System Prompt
good_system = """你是一位专业的中文技术文档写作专家，具有 10 年经验。

你的工作原则：
1. 语言：始终使用中文回答
2. 结构：使用清晰的标题和列表
3. 示例：每个概念都附带具体代码示例
4. 长度：回答简洁，避免废话
5. 格式：使用 Markdown 格式

当用户问题不清晰时，先确认需求再回答。"""
```

**技巧 2：Few-shot（示例学习）**
```python
# 让 AI 学习你的格式
messages = [
    {"role": "system", "content": "你是一个文本分类助手，将文本分类为：积极/消极/中性"},

    # 示例 1
    {"role": "user", "content": "这个产品太好用了！"},
    {"role": "assistant", "content": "积极"},

    # 示例 2
    {"role": "user", "content": "物流很慢，等了一周"},
    {"role": "assistant", "content": "消极"},

    # 示例 3
    {"role": "user", "content": "今天天气不错"},
    {"role": "assistant", "content": "中性"},

    # 真正的问题
    {"role": "user", "content": "价格有点贵，但质量确实好"}
]
```

**技巧 3：Chain-of-Thought（让 AI 先思考再回答）**
```python
cot_prompt = """请解决以下数学题，一步一步思考，最后给出答案：

题目：小明有 15 颗糖，给了小红 1/3，又买了 8 颗，现在有多少颗？

请按以下格式：
思考过程：（一步步分析）
最终答案：（数字）"""
```

**技巧 4：输出格式控制**
```python
format_prompt = """分析以下代码的问题，按格式回复：

代码：
```python
def divide(a, b):
    return a / b
```

请按以下格式回复：
问题数量：X 个

问题 1：
- 描述：
- 风险级别：高/中/低
- 修复建议：

问题 2：
...（如有）"""
```

#### 下午（3h）：实战练习

**练习 1**：写一个代码解释器 Prompt，让 AI 用通俗语言解释任意代码
**练习 2**：写一个会议纪要提取器，从自由文本中提取：参与人、决定事项、行动项
**练习 3**：写一个多语言翻译器，自动检测源语言并翻译

#### 今日检查点
- [ ] 能写出结构完整的 System Prompt
- [ ] 能用 Few-shot 引导 AI 输出格式
- [ ] 完成 3 个实战练习

---

### Day 14（周日，6h）：里程碑 2 项目

**构建完整的命令行聊天机器人**

```python
# chatbot.py
import os
import json
import sys
from datetime import datetime
from dotenv import load_dotenv
from zhipuai import ZhipuAI

load_dotenv()

SYSTEM_PROMPTS = {
    "default": "你是一个友好的 AI 助手，用中文回答问题",
    "coder": "你是一个专业的程序员，擅长 Python。回答时提供可运行的代码示例，并解释关键部分",
    "teacher": "你是一个耐心的老师，用简单易懂的语言解释复杂概念，多用比喻和例子",
}

class Chatbot:
    def __init__(self, role: str = "default"):
        self.client = ZhipuAI(api_key=os.getenv("ZHIPU_API_KEY"))
        self.role = role
        self.history = []
        self.system_prompt = SYSTEM_PROMPTS.get(role, SYSTEM_PROMPTS["default"])
        self.session_file = f"chat_{datetime.now().strftime('%Y%m%d_%H%M%S')}.json"

    def chat(self, user_input: str) -> str:
        self.history.append({"role": "user", "content": user_input})

        # 保留最近 20 条消息
        recent = self.history[-20:] if len(self.history) > 20 else self.history

        messages = [{"role": "system", "content": self.system_prompt}] + recent

        print("AI: ", end="", flush=True)
        full_response = ""

        try:
            response = self.client.chat.completions.create(
                model="glm-4-flash",
                messages=messages,
                stream=True,
                temperature=0.7,
            )

            for chunk in response:
                if chunk.choices[0].delta.content:
                    text = chunk.choices[0].delta.content
                    print(text, end="", flush=True)
                    full_response += text

        except Exception as e:
            full_response = f"[错误] {e}"
            print(full_response, end="")

        print("\n")
        self.history.append({"role": "assistant", "content": full_response})
        return full_response

    def save_session(self):
        with open(self.session_file, "w", encoding="utf-8") as f:
            json.dump({
                "role": self.role,
                "history": self.history,
                "saved_at": datetime.now().isoformat()
            }, f, ensure_ascii=False, indent=2)
        print(f"对话已保存到：{self.session_file}")

def main():
    print("=== AI 聊天机器人 ===")
    print("可选角色：default（默认）| coder（程序员）| teacher（老师）")

    role = input("选择角色（回车默认）：").strip() or "default"
    bot = Chatbot(role)

    print(f"\n已启用角色：{role}")
    print("输入 /save 保存对话，/clear 清除历史，/quit 退出\n")

    while True:
        try:
            user_input = input("你: ").strip()
        except KeyboardInterrupt:
            bot.save_session()
            break

        if not user_input:
            continue
        elif user_input == "/quit":
            bot.save_session()
            break
        elif user_input == "/save":
            bot.save_session()
        elif user_input == "/clear":
            bot.history = []
            print("已清除对话历史\n")
        else:
            bot.chat(user_input)

if __name__ == "__main__":
    main()
```

测试要求：
1. 测试 3 种角色切换
2. 测试多轮对话（提问 5+ 次，验证上下文记忆）
3. 测试保存功能
4. 测试异常情况（断网、无效输入）

---

## Week 3（第 15-21 天）：LangChain 入门

### Day 15（周一，2h）：LangChain 基础概念

#### 安装
```bash
pip install langchain langchain-openai langchain-community
# 如果用智谱AI
pip install langchain-community zhipuai
```

#### LangChain 的核心价值
```
原始 API 调用：你写所有代码（灵活但繁琐）
LangChain：封装好的积木块，快速拼装（开发快但需学习抽象）

AI 应用 = LLM + Prompt + 数据 + 工具
LangChain 把这些都封装成统一接口
```

#### 核心组件
```python
from langchain_openai import ChatOpenAI
from langchain_core.messages import HumanMessage, SystemMessage, AIMessage
from langchain_core.prompts import ChatPromptTemplate

# 1. Chat Model（语言模型）
llm = ChatOpenAI(model="gpt-4o-mini", temperature=0.7)

# 2. 直接调用
response = llm.invoke([
    SystemMessage(content="你是一个助手"),
    HumanMessage(content="你好")
])
print(response.content)

# 3. Prompt Template（模板）
prompt = ChatPromptTemplate.from_messages([
    ("system", "你是一个{role}"),
    ("human", "{question}")
])

# 填充模板
messages = prompt.format_messages(role="Python 专家", question="什么是装饰器？")
response = llm.invoke(messages)
print(response.content)
```

#### 今日检查点
- [ ] LangChain 安装成功
- [ ] 能用 LangChain 调用 LLM
- [ ] 理解 ChatPromptTemplate 的作用

---

### Day 16（周二，2h）：LCEL — LangChain 的管道语法

```python
from langchain_core.output_parsers import StrOutputParser, JsonOutputParser

# LCEL：用 | 连接组件，像管道一样
# prompt | llm | parser

# 示例 1：基础链
chain = prompt | llm | StrOutputParser()
result = chain.invoke({"role": "历史学家", "question": "秦始皇统一六国的年份？"})
print(result)

# 示例 2：流式输出
for chunk in chain.stream({"role": "助手", "question": "讲一个笑话"}):
    print(chunk, end="", flush=True)

# 示例 3：批量处理
questions = [
    {"role": "助手", "question": "1+1=?"},
    {"role": "助手", "question": "北京的首都是哪里？"},  # 故意出错的问题
]
results = chain.batch(questions)
```

#### 今日检查点
- [ ] 能用 `|` 语法构建链
- [ ] 能流式输出和批量处理

---

### Day 17-19（周三-周五，各 2h）：综合实践

**Day 17**：用 LangChain 重写聊天机器人

**Day 18**：实现一个文章摘要工具（输入长文本，输出摘要+关键词+评分）

**Day 19（重点）**：Function Calling 初体验 — 为 Phase 4 Agent 铺垫

```python
# 核心概念：让 LLM 决定"调用哪个函数"
# 这是 Agent 的基础，先在 Phase 2 末建立直觉

from openai import OpenAI

client = OpenAI(api_key=os.getenv("OPENAI_API_KEY"))

# 定义工具（告诉模型有哪些工具可用）
tools = [
    {
        "type": "function",
        "function": {
            "name": "get_current_weather",
            "description": "获取指定城市的天气",
            "parameters": {
                "type": "object",
                "properties": {
                    "city": {"type": "string", "description": "城市名"},
                },
                "required": ["city"]
            }
        }
    },
    {
        "type": "function",
        "function": {
            "name": "search_knowledge_base",
            "description": "在知识库中搜索相关文档",
            "parameters": {
                "type": "object",
                "properties": {
                    "query": {"type": "string", "description": "搜索词"},
                },
                "required": ["query"]
            }
        }
    }
]

response = client.chat.completions.create(
    model="gpt-4o-mini",
    messages=[{"role": "user", "content": "北京今天天气怎么样？"}],
    tools=tools,
    tool_choice="auto"  # 让模型自己决定是否调用工具
)

# 查看模型的决定
choice = response.choices[0]
print(f"finish_reason: {choice.finish_reason}")  # tool_calls 或 stop

if choice.finish_reason == "tool_calls":
    for tool_call in choice.message.tool_calls:
        print(f"模型决定调用: {tool_call.function.name}")
        print(f"参数: {tool_call.function.arguments}")
        # → 模型决定调用: get_current_weather
        # → 参数: {"city": "北京"}

# 今日理解目标：
# 1. 工具定义 = 告诉 LLM 有哪些能力
# 2. LLM 负责"决策"，你负责"执行"
# 3. Phase 4 Agent = 把这个循环自动化
```

今日检查点：
- [ ] 理解 Function Calling 中 LLM 的角色（决策者，不是执行者）
- [ ] 能写出工具的 JSON Schema 描述
- [ ] 理解 `finish_reason: tool_calls` 的含义

---

### Day 20（周六，6h）：里程碑 2 完善

- 上午（3h）：给聊天机器人添加 Web 界面（用 Gradio）
```bash
pip install gradio
```
```python
import gradio as gr

def respond(message, history):
    # 调用你的 chatbot 逻辑
    response = bot.chat(message)
    return response

demo = gr.ChatInterface(fn=respond, title="我的 AI 助手")
demo.launch()
```

- 下午（3h）：整理代码，编写 README，推送到 GitHub

---

### Day 21（周日，6h）：复习 + 进阶阅读

- 上午（3h）：重读官方文档，深化理解 LCEL
- 下午（3h）：阅读 DeepLearning.AI Prompt Engineering 课程

### 阶段总结

- [ ] 能独立调用大模型 API
- [ ] 掌握 Prompt Engineering 基本技巧
- [ ] 理解多轮对话的实现原理
- [ ] 能用 LangChain 构建简单应用链
- [ ] 里程碑 2 项目完成并推送 GitHub

**下周预告**：进入 RAG 系统，你将构建一个能"阅读文件回答问题"的 AI 知识库。
