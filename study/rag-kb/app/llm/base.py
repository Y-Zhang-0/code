"""LLM 抽象基类。"""
from abc import ABC, abstractmethod


class BaseLLM(ABC):
    @abstractmethod
    async def generate(self, prompt: str) -> str: ...
