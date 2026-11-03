import json
import random
from pathlib import Path

from app.services.career_service import draw_questions, score_questions

BANK_PATH = Path(__file__).resolve().parents[2] / "data" / "quiz.json"

SKILL_LABELS = {
    "Development": "Розробка",
    "Frontend": "Фронтенд",
    "Backend": "Бекенд",
    "Fullstack": "Фулстек",
    "Data": "Дані",
    "Security": "Безпека",
    "Testing": "Тестування",
    "Mobile": "Мобільні",
    "AI": "Штучний інтелект",
    "English": "Англійська",
}

MODES = {
    15: {
        "title": "Швидко",
        "lead": "15 питань · 1–2 на напрямок",
        "during": "Короткий прохід: на напрямок випало 1 або 2 питання. Одна відповідь помітно змінює бал.",
        "text": "Короткий прохід по всіх напрямках. Його вистачає, щоб помітити тему, якої майже немає. Бал при цьому хисткий: питань так мало, що одна відповідь багато важить.",
    },
    25: {
        "title": "Рівніше",
        "lead": "25 питань · 2–3 на напрямок",
        "during": "Середній прохід: на напрямок випало 2 або 3 питання. Одна вдала відповідь уже не вирішує тему.",
        "text": "Середня довжина. На напрямок уже є кілька відповідей, тож випадкове влучання менше вирішує бал. Не всі 8 питань напрямку ввійдуть у цей прохід.",
    },
    35: {
        "title": "Найпевніше",
        "lead": "35 питань · 3–4 на напрямок",
        "during": "Повний прохід: на напрямок випало 3 або 4 питання. Бал складається з кількох перевірок.",
        "text": "Найдовший варіант. Кожен напрямок перевіряється кілька разів і з різних боків. Бал найближчий до того, що ви справді знаєте з цього списку питань.",
    },
}


def load_bank():
    with BANK_PATH.open(encoding="utf-8") as bank_file:
        return json.load(bank_file)


def draw_quiz(count, rng=None):
    if count not in MODES:
        raise ValueError("unknown quiz size")
    rng = rng or random.SystemRandom()
    bank = load_bank()
    by_id = {question["id"]: question for question in bank}
    picked = draw_questions(bank, count, rng.randrange(2**31))
    questions = []
    for item in picked:
        question = by_id[item["id"]]
        options = list(question["options"])
        rng.shuffle(options)
        questions.append({
            "id": question["id"],
            "skill": question["skill"],
            "text": question["text"],
            "options": options,
            "correct": question["correct"],
        })
    asked = {}
    for question in questions:
        asked[question["skill"]] = asked.get(question["skill"], 0) + 1
    smallest = min(asked.values()) if asked else 0
    return {
        "count": len(questions),
        "note": MODES[count]["during"],
        "smallest": smallest,
        "questions": questions,
    }


def score_quiz(questions, answers):
    raw = score_questions(questions, answers)
    levels = []
    for item in raw["levels"]:
        levels.append({
            "skill": SKILL_LABELS.get(item["skill"], item["skill"]),
            "correct": item["correct"],
            "asked": item["asked"],
            "level": item["level"],
        })
    levels.sort(key=lambda item: item["skill"])
    return {"levels": levels, "smallest": raw["smallest"], "note": raw["note"]}
