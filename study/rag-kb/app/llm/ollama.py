"""Ollama 本地 LLM 实现。"""
import httpx
from app.llm.base import BaseLLM
from app.core.config import get_settings


class OllamaLLM(BaseLLM):
    def __init__(self):
        cfg = get_settings().llm.ollama
        self._base_url = cfg.base_url.rstrip("/")
        self._model = cfg.model
        self._timeout = cfg.timeout

    async def generate(self, prompt: str) -> str:
        url = f"{self._base_url}/api/generate"
        payload = {"model": self._model, "prompt": prompt, "stream": False}
        async with httpx.AsyncClient(timeout=self._timeout) as client:
            resp = await client.post(url, json=payload)
            resp.raise_for_status()
            return resp.json()["response"]
