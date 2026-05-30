"""Pydantic 请求/响应模型。"""
from typing import List, Any, Dict
from pydantic import BaseModel


class ChatRequest(BaseModel):
    question: str


class SourceItem(BaseModel):
    source: str
    doc_id: str
    content: str


class ChatResponse(BaseModel):
    answer: str
    sources: List[SourceItem]


class DocumentItem(BaseModel):
    doc_id: str
    source: str
    file_path: str


class UploadResponse(BaseModel):
    doc_id: str
    filename: str
    chunks: int
    message: str


class DeleteResponse(BaseModel):
    doc_id: str
    message: str
