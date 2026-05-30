# 并行 Agent 限制 Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 在全局 `~/.claude/CLAUDE.md` 的 `## 约束` 末尾追加一行规则，将 `dispatching-parallel-agents` 的每批并行数上限设为 3。

**Architecture:** 纯文本编辑，无代码改动。在 CLAUDE.md 的 `## 约束` 章节末尾追加一行 Markdown 列表项，Claude 读取后自动遵守。

**Tech Stack:** Markdown 文本编辑

**Spec:** `learning/superpowers/specs/2026-03-20-parallel-agent-limit-design.md`

---

### Task 1: 追加并行 Agent 限制规则

**Files:**
- Modify: `C:\Users\zhangyu\.claude\CLAUDE.md`（`## 约束` 章节末尾）

- [ ] **Step 1: 查看当前 `## 约束` 章节末尾内容**

  读取 `C:\Users\zhangyu\.claude\CLAUDE.md`，确认 `## 约束` 末尾现有内容，记住最后一行，供下一步精确定位使用。

- [ ] **Step 2: 追加规则行**

  在 `## 约束` 末尾追加以下内容（保持与现有列表项相同缩进格式）：

  ```
  - 使用 `dispatching-parallel-agents` 时，根据任务复杂度自行判断并行数量，但每批并行 agent 数不得超过 **3**。若任务总数超过上限，按批次顺序执行，每批不超过该上限。如需调整上限，直接修改此处数字即可。
  ```

- [ ] **Step 3: 验证追加结果**

  重新读取 `C:\Users\zhangyu\.claude\CLAUDE.md`，确认：
  - 新规则行出现在 `## 约束` 章节末尾
  - 原有内容未被改动

- [ ] **Step 4: Commit**

  ```bash
  git -C "C:/Users/zhangyu/.claude" add CLAUDE.md
  git -C "C:/Users/zhangyu/.claude" commit -m "feat: 限制 dispatching-parallel-agents 最大并行数为 3"
  ```

  > **注意：** `~/.claude` 目录若不是 git 仓库则跳过此步，直接保存文件即可。
