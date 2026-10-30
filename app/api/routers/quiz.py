import secrets

from fastapi import APIRouter, Form, Request
from fastapi.responses import RedirectResponse
from fastapi.templating import Jinja2Templates

from app.services.quiz_engine import MODES, draw_quiz, score_quiz

router = APIRouter()
templates = Jinja2Templates(directory="templates")
sessions = {}


@router.get("/")
def home():
    return RedirectResponse("/quiz", status_code=303)


@router.get("/quiz")
def choose(request: Request):
    return templates.TemplateResponse(request, "quiz_choose.html", {"modes": MODES})


@router.post("/quiz/start")
def start(size: int = Form(...)):
    if size not in MODES:
        return RedirectResponse("/quiz", status_code=303)
    token = secrets.token_hex(8)
    sessions[token] = draw_quiz(size)
    return RedirectResponse(f"/quiz/{token}", status_code=303)


@router.get("/quiz/{token}")
def show(request: Request, token: str):
    quiz = sessions.get(token)
    if quiz is None or "levels" in quiz:
        return RedirectResponse("/quiz", status_code=303)
    return templates.TemplateResponse(request, "quiz_run.html", {"token": token, "quiz": quiz})


@router.post("/quiz/{token}")
async def finish(request: Request, token: str):
    quiz = sessions.get(token)
    if quiz is None:
        return RedirectResponse("/quiz", status_code=303)
    form = await request.form()
    answers = {key: value for key, value in form.items()}
    result = score_quiz(quiz["questions"], answers)
    quiz["levels"] = result["levels"]
    quiz["result_note"] = result["note"]
    return templates.TemplateResponse(
        request,
        "quiz_result.html",
        {"quiz": quiz, "levels": result["levels"]},
    )
