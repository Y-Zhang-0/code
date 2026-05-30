# 常见坑点与解决方案

> 这里收录了 AI 应用开发新手最容易踩的坑，提前了解可以少走很多弯路

---

## 坑 1：API Key 泄漏

**症状**：把 API Key 写死在代码里，push 到 GitHub，被他人盗用，产生大额账单

**预防**
```bash
# 永远不要这样写
API_KEY = "sk-xxxxx真实key"  # ❌ 绝对不行

# 正确做法
# 1. 使用 .env 文件
API_KEY=sk-xxxxx  # 写在 .env 文件里

# 2. .env 加入 .gitignore
echo ".env" >> .gitignore

# 3. 代码里从环境变量读取
import os
API_KEY = os.getenv("API_KEY")  # ✓

# 4. 如果不小心已经 push，立即撤销 API Key！
# 去 API 控制台删除泄漏的 Key，生成新的
```

---

## 坑 2：对话历史无限增长

**症状**：长时间对话后，API 返回 "context length exceeded" 错误

**原因**：每轮对话都把完整历史传给 API，历史越来越长，超出模型限制

**解决**
```python
# 错误做法
messages.append(new_message)
# 不限制长度，一直添加

# 正确做法1：限制消息数量
MAX_HISTORY = 20
if len(messages) > MAX_HISTORY:
    # 保留 system prompt + 最近 N 条
    system = messages[0]
    recent = messages[-(MAX_HISTORY-1):]
    messages = [system] + recent

# 正确做法2：按 token 数截断（更精确）
```

---

## 坑 3：Embedding 模型首次下载很慢

**症状**：运行代码时卡在 "Downloading model" 很久，甚至超时失败

**解决**
```python
# BGE-M3 模型约 2.3GB，首次下载需要时间
# 方法1：使用国内镜像
import os
os.environ["HF_ENDPOINT"] = "https://hf-mirror.com"

# 方法2：手动下载后指定本地路径
model = SentenceTransformer("/path/to/downloaded/model")

# 下载命令（需要 git lfs）
git lfs install
git clone https://hf-mirror.com/BAAI/bge-m3
```

---

## 坑 4：RAG 检索不到正确内容

**症状**：文档里明明有答案，AI 却说"我不知道"或给出错误答案

**排查顺序**（按此顺序，不要直接换模型）

```python
# Step 1：验证文档是否正确导入
print(f"向量库文档数：{vectordb.count()}")
# 如果是 0，说明导入失败

# Step 2：直接测试检索（不过 AI）
results = vectordb.similarity_search("你的问题", k=5)
for r in results:
    print(r.page_content[:200])
# 看检索结果里有没有包含答案的内容

# Step 3：检查分块是否把答案切断了
# 查看 chunk 大小，适当增大 chunk_overlap

# Step 4：检查 Prompt 是否清晰告诉 AI 用参考资料回答

# Step 5（最后才考虑）：换更好的模型
```

**常见根因**
| 现象 | 根因 | 解决 |
|:---|:---|:---|
| 检索结果不相关 | embedding 模型不匹配语言 | 换 bge-m3（多语言模型） |
| 明明有但没检索到 | chunk 太小/答案被切断 | 增大 chunk_overlap |
| 检索到了但回答错 | Prompt 不明确 | 加上"只基于以下资料回答" |
| 专有名词检索差 | 向量检索对专有名词弱 | 加入 BM25 关键词检索 |

---

## 坑 5：Agent 无限循环

**症状**：Agent 开始运行后一直在调用工具，无法停止，消耗大量 token

**解决**
```python
# 必须设置最大迭代次数
agent_executor = AgentExecutor(
    agent=agent,
    tools=tools,
    max_iterations=10,  # ← 这个必须设置！
    max_execution_time=60,  # 最多执行 60 秒
    handle_parsing_errors=True
)

# 手动实现时也要加
step = 0
MAX_STEPS = 10
while step < MAX_STEPS:  # ← 不要用 while True
    step += 1
    ...
```

---

## 坑 6：流式输出乱码或中断

**症状**：流式输出时显示乱码，或者中途停止

**解决**
```python
# 问题：中文在流式传输时可能被分在不同 chunk
# 解决：积累完整响应再处理，或确保编码正确

# FastAPI SSE 流式响应
from fastapi.responses import StreamingResponse

async def generate():
    async for chunk in llm.astream(messages):
        content = chunk.content
        if content:
            # 确保 JSON 序列化后发送
            yield f"data: {json.dumps({'text': content}, ensure_ascii=False)}\n\n"
    yield "data: [DONE]\n\n"

# 前端接收时
const reader = response.body.getReader()
const decoder = new TextDecoder('utf-8')  # 指定 UTF-8
```

---

## 坑 7：虚拟环境混乱

**症状**：pip install 成功但 import 报错；不同项目的依赖互相冲突

**解决**
```bash
# 每个项目单独创建虚拟环境，这是铁律
mkdir new-project && cd new-project
python -m venv venv

# 激活（每次开发前都要激活！）
# Windows:
venv\Scripts\activate
# Mac/Linux:
source venv/bin/activate

# 确认当前环境
which python  # 应该指向 venv 目录下的 python

# 每次 pip install 前确认是否在正确的虚拟环境
pip install xxx

# 保存依赖
pip freeze > requirements.txt
```

---

## 坑 8：Docker 构建很慢

**症状**：每次改代码后重新构建 Docker 镜像都要等很久

**解决**
```dockerfile
# 利用 Docker 缓存层
# 不变的内容放前面，经常变的内容放后面

# 错误顺序（每次都要重新安装依赖）
COPY . .           # ← 代码变了，后面全部重新执行
RUN pip install -r requirements.txt

# 正确顺序
COPY requirements.txt .  # ← 只有依赖变化时才重新安装
RUN pip install -r requirements.txt
COPY . .                 # ← 代码变化不影响依赖安装的缓存
```

---

## 坑 9：ChromaDB 数据丢失

**症状**：重启程序后，之前导入的文档消失了

**解决**
```python
# 错误：内存模式（重启就没了）
client = chromadb.Client()  # ❌

# 正确：持久化模式
client = chromadb.PersistentClient(path="./chroma_db")  # ✓

# 使用 LangChain 时
vectordb = Chroma(
    persist_directory="./chroma_db",  # ← 必须指定！
    embedding_function=embeddings
)
```

---

## 坑 10：LangChain 版本不兼容

**症状**：复制网上教程代码，运行时报 ImportError 或 DeprecationWarning

**原因**：LangChain 版本迭代快，旧教程的导入路径已经改变

**解决**
```bash
# 查看当前版本
pip show langchain

# 遇到 import 问题时，查官方文档而非随便找教程
# 官方文档：https://python.langchain.com/docs/introduction/

# 固定版本（项目中推荐）
langchain==0.3.x
langchain-openai==0.2.x
langchain-community==0.3.x
```

```python
# 新版 LangChain 的正确导入（0.3+）
from langchain_openai import ChatOpenAI          # ✓
from langchain.chat_models import ChatOpenAI     # ✗ 已废弃

from langchain_core.prompts import ChatPromptTemplate  # ✓
from langchain.prompts import ChatPromptTemplate       # ✗ 已废弃
```

---

## 坑 11：用错参照系——用"后端架构师"标准衡量"AI 应用开发"

**症状**：花大量时间焦虑自己没有分布式、高并发、消息队列、缓存经验，迟迟没有动手做 AI 项目

**根因**：混淆了两类不同岗位的技能要求

| 岗位 | 核心技能 |
|:---|:---|
| 后端架构师 / 平台工程师 | 分布式系统、高并发、消息队列、缓存 |
| AI 应用开发工程师 | LLM 集成、RAG、Agent、Prompt 工程 |

**解决**：认清当前目标是"AI 应用开发"，先完成本路线 Phase 1-5，规模化需求出现时再按需补充分布式知识。

> 三年半全栈经验 + 工业领域背景（AGV）+ RAG 系统能力，已经是市场上稀缺的组合。
> 专注当下阶段，不要被不必要的焦虑分散精力。

---

## 调试技巧总结

### 遇到问题先做这几件事

1. **完整阅读报错信息**（不要只看最后一行）
2. **最小化复现**（去掉无关代码，确认问题在哪里）
3. **搜索报错信息**（优先搜 GitHub Issues 和 Stack Overflow）
4. **查官方文档**（比搜到的教程更准确）
5. **问 AI**（把完整报错信息和相关代码给 AI，描述你做了什么）

### 有效提问模板

```
我在做：[具体任务]
遇到了：[报错信息/异常现象]
我已经尝试了：[你做过的排查]
相关代码：[最小化的代码片段]
期望的结果：[应该怎样]
```

---

## Git 工作流规范

> 作品集代码质量的直接体现，面试时面试官会看你的提交历史。

### 分支策略

```bash
main          # 主分支，始终保持可部署状态
develop       # 开发分支，功能汇总后合并到 main
feature/xxx   # 功能分支，从 develop 切出
fix/xxx       # 修复分支
```

```bash
# 开始新功能
git checkout develop
git pull origin develop
git checkout -b feature/rag-hybrid-retrieval

# 开发完成，推送并发 PR
git add app/core/retriever.py tests/test_retriever.py
git commit -m "feat: add hybrid retrieval with BM25 + vector"
git push origin feature/rag-hybrid-retrieval
# → GitHub 上发 PR: feature/rag-hybrid-retrieval → develop
```

### Commit 消息规范（Conventional Commits）

```
类型(范围): 描述

类型：
feat     - 新功能
fix      - 修复 bug
docs     - 文档更新
refactor - 重构（无功能变化）
test     - 添加/修改测试
chore    - 构建/工具链变更
perf     - 性能优化

示例：
feat(rag): add HyDE query augmentation
fix(api): handle empty knowledge base gracefully
test(routes): add unit tests for chat endpoint
docs: update README with deployment instructions
```

### .gitignore 必配项

```gitignore
# 环境变量（绝对不能提交！）
.env
.env.local

# Python
__pycache__/
*.pyc
venv/
.venv/
*.egg-info/

# AI 应用特有
chroma_db/          # 向量库数据（可大可小，不提交）
uploads/            # 用户上传文件
*.model             # 模型文件
models/

# 日志
logs/
*.log

# IDE
.vscode/settings.json
.idea/
```

### 作品集 GitHub 整理建议

- 每个项目独立仓库，不要都堆在一个 repo
- `main` 分支代码干净，无调试代码
- README 有：功能截图/GIF、快速启动命令、技术栈徽章
- commit 历史体现开发过程（不是一次性 "initial commit"）
