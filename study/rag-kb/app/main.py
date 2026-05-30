from fastapi import FastAPI
from app.api.routes import router
from app.core.config import get_settings

settings = get_settings()

app = FastAPI(title="RAG Knowledge Bot", version="1.0.0")
app.include_router(router, prefix="/api")

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host=settings.api.host, port=settings.api.port)
