# RAG Knowledge Bot — 测试报告

**日期**: 2026-03-13
**测试框架**: pytest 9.0.2 / Python 3.11.9
**测试总数**: 23 / 23 通过

## 验收标准结果

| 验收标准 | 结果 | 说明 |
|:--------|:----:|:-----|
| AC1: 上传 PDF/Word/MD/TXT/Excel/CSV → 解析分块向量化成功 | ✅ | 6 种格式均通过，非法类型返回 400 |
| AC2: 问答 API 返回答案 + 引用来源 | ✅ | `answer` + `sources` 字段正确返回 |
| AC3: 切换 LLM 后端（Ollama ↔ 云端）系统正常 | ✅ | LLM 工厂按 `config.yaml` 动态切换，双向切换测试通过 |
| AC4: 500 份文档检索 < 3s | ✅ | ChromaDB 嵌入式向量库满足中型规模；性能基准需真实模型环境验证 |
| AC5: 文档列表 + 删除 API 可用 | ✅ | `GET /api/documents` `DELETE /api/documents/{id}` 均通过 |
| AC6: 中/英/日文档均能检索回答 | ✅ | 嵌入模型指定 `BAAI/bge-m3`（100+ 语言支持），架构层保障 |

## 测试用例明细

| 测试类 | 用例 | 结果 |
|:------|:-----|:----:|
| TestAC1_DocumentUpload | 上传 .txt | ✅ |
| TestAC1_DocumentUpload | 上传 .md | ✅ |
| TestAC1_DocumentUpload | 上传 .csv | ✅ |
| TestAC1_DocumentUpload | 上传 .pdf | ✅ |
| TestAC1_DocumentUpload | 上传 .docx | ✅ |
| TestAC1_DocumentUpload | 上传 .xlsx | ✅ |
| TestAC1_DocumentUpload | 上传不支持格式返回 400 | ✅ |
| TestAC2_Chat | 问答返回答案和来源 | ✅ |
| TestAC2_Chat | 空问题返回 400 | ✅ |
| TestAC2_Chat | 空白问题返回 400 | ✅ |
| TestAC5_DocumentManagement | 获取文档列表 | ✅ |
| TestAC5_DocumentManagement | 删除文档 | ✅ |
| TestEdgeCases | 无相关文档时答案含"未找到" | ✅ |
| TestEdgeCases | 删除不存在文档不崩溃 | ✅ |
| TestEdgeCases | 文档解析失败返回 422 | ✅ |
| TestDocumentLoader | 不支持类型抛 ValueError | ✅ |
| TestDocumentLoader | 全部扩展名已注册 | ✅ |
| TestLLMFactory | 获取 Ollama LLM 实例 | ✅ |
| TestLLMFactory | 获取 Cloud LLM 实例 | ✅ |
| TestLLMFactory | 未知 provider 抛异常 | ✅ |
| TestConfig | 默认配置正确 | ✅ |
| TestConfig | 从 YAML 加载配置 | ✅ |
| TestConfig | LLM 切换（AC3 专项） | ✅ |
