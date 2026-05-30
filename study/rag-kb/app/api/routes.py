"""API 路由：文档上传/列表/删除 + 问答。"""
import uuid
import shutil
from pathlib import Path

from fastapi import APIRouter, UploadFile, File, HTTPException

from app.api.schemas import (
    ChatRequest, ChatResponse, DocumentItem,
    UploadResponse, DeleteResponse,
)
from app.loader.document_loader import load_document
from app.store.vector_store import get_vector_store
from app.core.rag_engine import get_rag_engine
from app.core.config import get_settings

router = APIRouter()


def _upload_dir() -> Path:
    d = Path(get_settings().upload.dir)
    d.mkdir(parents=True, exist_ok=True)
    return d


def _validate_file(filename: str) -> str:
    suffix = Path(filename).suffix.lstrip(".").lower()
    allowed = get_settings().upload.allowed_types
    if suffix not in allowed:
        raise HTTPException(status_code=400, detail=f"不支持的文件类型: .{suffix}")
    return suffix


@router.post("/documents/upload", response_model=UploadResponse)
async def upload_document(file: UploadFile = File(...)):
    _validate_file(file.filename)

    doc_id = str(uuid.uuid4())
    save_path = _upload_dir() / f"{doc_id}_{file.filename}"

    with open(save_path, "wb") as f:
        shutil.copyfileobj(file.file, f)

    try:
        docs = load_document(str(save_path))
    except Exception as e:
        save_path.unlink(missing_ok=True)
        raise HTTPException(status_code=422, detail=f"文档解析失败: {e}")

    # 补充原始文件名到 metadata
    for doc in docs:
        doc.metadata["source"] = file.filename

    chunks = get_vector_store().add_documents(docs, doc_id)
    return UploadResponse(
        doc_id=doc_id,
        filename=file.filename,
        chunks=chunks,
        message="文档已成功导入知识库",
    )


@router.get("/documents", response_model=list[DocumentItem])
async def list_documents():
    return get_vector_store().list_documents()


@router.delete("/documents/{doc_id}", response_model=DeleteResponse)
async def delete_document(doc_id: str):
    get_vector_store().delete_document(doc_id)
    # 同步删除上传文件（忽略不存在的情况）
    for f in _upload_dir().glob(f"{doc_id}_*"):
        f.unlink(missing_ok=True)
    return DeleteResponse(doc_id=doc_id, message="文档已从知识库中删除")


@router.post("/chat", response_model=ChatResponse)
async def chat(req: ChatRequest):
    if not req.question.strip():
        raise HTTPException(status_code=400, detail="问题不能为空")
    result = await get_rag_engine().query(req.question)
    return ChatResponse(**result)
