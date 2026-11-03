from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles

from app.api.routers.quiz import router

app = FastAPI(title="Підбір ІТ-напрямку")
app.mount("/static", StaticFiles(directory="static"), name="static")
app.include_router(router)
