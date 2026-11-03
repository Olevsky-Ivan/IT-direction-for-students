import career_core


def draw_questions(bank, count, seed):
    questions = [
        career_core.QuizQuestion(item["id"], item["skill"], item["correct"])
        for item in bank
    ]
    drawn = career_core.draw_questions(questions, count, seed)
    return [
        {"id": item.id, "skill": item.skill, "correct": item.correct_option_id}
        for item in drawn
    ]


def score_questions(questions, answers):
    asked = [
        career_core.QuizQuestion(item["id"], item["skill"], item["correct"])
        for item in questions
    ]
    raw = career_core.score_questions(asked, {str(key): str(value) for key, value in answers.items()})
    levels = [
        {
            "skill": item.skill,
            "correct": item.correct,
            "asked": item.asked,
            "level": item.level,
        }
        for item in raw
    ]
    smallest = min((item["asked"] for item in levels), default=0)
    return {
        "levels": levels,
        "smallest": smallest,
        "note": career_core.accuracy_note(smallest),
    }
