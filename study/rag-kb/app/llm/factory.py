"""LLM 工厂，根据配置返回对应实现。"""
from app.llm.base import BaseLLM
from app.core.config import get_settings


def get_llm() -> BaseLLM:
    provider = get_settings().llm.provider
    if provider == "ollama":
        from app.llm.ollama import OllamaLLM
        return OllamaLLM()
    elif provider == "cloud":
        from app.llm.cloud import CloudLLM
        return CloudLLM()
    raise ValueError(f"未知 LLM provider: {provider}")
