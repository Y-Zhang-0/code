"""配置管理，从 config.yaml 加载。"""
from functools import lru_cache
from pathlib import Path
from typing import List

import yaml
from pydantic import BaseModel


class OllamaConfig(BaseModel):
    base_url: str = "http://localhost:11434"
    model: str = "qwen2:7b"
    timeout: int = 120


class CloudConfig(BaseModel):
    provider: str = "openai"
    api_key: str = ""
    model: str = "gpt-4o-mini"
    base_url: str = ""


class LLMConfig(BaseModel):
    provider: str = "ollama"
    ollama: OllamaConfig = OllamaConfig()
    cloud: CloudConfig = CloudConfig()


class EmbeddingConfig(BaseModel):
    model: str = "BAAI/bge-m3"
    device: str = "cpu"
    normalize: bool = True


class VectorStoreConfig(BaseModel):
    type: str = "chroma"
    persist_dir: str = "./data/chroma_db"
    collection: str = "knowledge_base"
    top_k: int = 5


class SplitterConfig(BaseModel):
    chunk_size: int = 512
    chunk_overlap: int = 64


class UploadConfig(BaseModel):
    dir: str = "./data/uploads"
    max_size_mb: int = 50
    allowed_types: List[str] = ["pdf", "docx", "md", "txt", "xlsx", "csv"]


class ApiConfig(BaseModel):
    host: str = "0.0.0.0"
    port: int = 8000
    debug: bool = False


class Settings(BaseModel):
    llm: LLMConfig = LLMConfig()
    embedding: EmbeddingConfig = EmbeddingConfig()
    vector_store: VectorStoreConfig = VectorStoreConfig()
    splitter: SplitterConfig = SplitterConfig()
    upload: UploadConfig = UploadConfig()
    api: ApiConfig = ApiConfig()


@lru_cache(maxsize=1)
def get_settings(config_path: str = "config.yaml") -> Settings:
    path = Path(config_path)
    if not path.exists():
        return Settings()
    with open(path, encoding="utf-8") as f:
        data = yaml.safe_load(f) or {}
    return Settings(**data)
