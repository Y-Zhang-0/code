"""RAG 核心引擎：检索 → 上下文组装 → LLM 生成。"""
from typing import List, Dict, Any

from langchain_core.documents import Document

from app.store.vector_store import get_vector_store
from app.llm.factory import get_llm

_PROMPT_TEMPLATE = """\
你是一个知识库问答助手。请根据以下参考资料回答用户的问题。
如果参考资料中没有相关信息，请如实说明"知识库中未找到相关内容"，不要编造答案。

参考资料：
{context}

用户问题：{question}

请用与问题相同的语言回答："""


class RAGEngine:
    def __init__(self):
        self._store = get_vector_store()
        self._llm = get_llm()

    async def query(self, question: str) -> Dict[str, Any]:
        """检索相关文档并生成回答，返回答案和引用来源。"""
        docs: List[Document] = self._store.search(question)

        if not docs:
            return {
                "answer": "知识库中未找到相关内容。",
                "sources": [],
            }

        context = "\n\n".join(
            f"[来源: {d.metadata.get('source', '未知')}]\n{d.page_content}"
            for d in docs
        )
        prompt = _PROMPT_TEMPLATE.format(context=context, question=question)
        answer = await self._llm.generate(prompt)

        sources = [
            {
                "source": d.metadata.get("source", ""),
                "doc_id": d.metadata.get("doc_id", ""),
                "content": d.page_content[:200],
            }
            for d in docs
        ]
        return {"answer": answer, "sources": sources}


_engine: RAGEngine | None = None


def get_rag_engine() -> RAGEngine:
    global _engine
    if _engine is None:
        _engine = RAGEngine()
    return _engine
