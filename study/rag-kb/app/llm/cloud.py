"""云端 LLM 实现（OpenAI 兼容接口预留）。"""
import httpx
from app.llm.base import BaseLLM
from app.core.config import get_settings


class CloudLLM(BaseLLM):
    def __init__(self):
        cfg = get_settings().llm.cloud
        self._api_key = cfg.api_key
        self._model = cfg.model
        self._base_url = cfg.base_url or "https://api.openai.com/v1"

    async def generate(self, prompt: str) -> str:
        url = f"{self._base_url}/chat/completions"
        headers = {"Authorization": f"Bearer {self._api_key}"}
        payload = {
            "model": self._model,
            "messages": [{"role": "user", "content": prompt}],
        }
        async with httpx.AsyncClient(timeout=60) as client:
            resp = await client.post(url, json=payload, headers=headers)
            resp.raise_for_status()
            return resp.json()["choices"][0]["message"]["content"]
