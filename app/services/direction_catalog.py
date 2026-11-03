import json
from pathlib import Path

from app.services.quiz_engine import SKILL_LABELS

CATALOG_PATH = Path(__file__).resolve().parents[2] / "data" / "directions.json"

TYPES = {
    "Development": set(),
    "Frontend": set(),
    "Backend": set(),
    "Data": set(),
    "Security": set(),
    "Testing": set(),
    "Fullstack": {"interface", "server"},
    "Mobile": {"platform"},
    "AI": {"math", "programming"},
}

SKILLS = set(SKILL_LABELS)


def load_catalog():
    with CATALOG_PATH.open(encoding="utf-8") as catalog_file:
        payload = json.load(catalog_file)
    if not isinstance(payload, list):
        raise ValueError("direction catalog must be a list")
    return [read_direction(item) for item in payload]


def read_direction(item):
    name = text_field(item, "name")
    direction_type = text_field(item, "type")
    if direction_type not in TYPES:
        raise ValueError(f"{name}: unknown direction type")
    requirements = item.get("requirements")
    if not isinstance(requirements, list) or not requirements:
        raise ValueError(f"{name}: direction has no requirements")
    read = [read_requirement(name, requirement) for requirement in requirements]
    expect_groups(name, direction_type, read)
    return {
        "id": number_field(item, "id", name),
        "type": direction_type,
        "name": name,
        "description": text_field(item, "description"),
        "difficulty": ranged_int(item, "difficulty", name, 1, 5),
        "requirements": read,
    }


def read_requirement(direction_name, item):
    skill = text_field(item, "skill")
    if skill not in SKILLS:
        raise ValueError(f"{direction_name}: unknown skill {skill}")
    weight = item.get("weight")
    if isinstance(weight, bool) or not isinstance(weight, (int, float)) or weight <= 0:
        raise ValueError(f"{direction_name}: requirement weight must be positive")
    essential = item.get("essential")
    if not isinstance(essential, bool):
        raise ValueError(f"{direction_name}: essential must be true or false")
    group = item.get("group", "")
    if not isinstance(group, str):
        raise ValueError(f"{direction_name}: group must be text")
    return {
        "skill": skill,
        "minLevel": ranged_int(item, "minLevel", direction_name, 1, 5),
        "weight": float(weight),
        "essential": essential,
        "group": group,
    }


def expect_groups(direction_name, direction_type, requirements):
    present = {
        requirement["group"]
        for requirement in requirements
        if requirement["essential"] and requirement["group"]
    }
    missing = TYPES[direction_type] - present
    if missing:
        joined = ", ".join(sorted(missing))
        raise ValueError(f"{direction_name}: missing essential group {joined}")


def text_field(item, key):
    value = item.get(key)
    if not isinstance(value, str) or not value.strip():
        raise ValueError(f"direction field {key} is empty")
    return value.strip()


def number_field(item, key, direction_name):
    value = item.get(key)
    if isinstance(value, bool) or not isinstance(value, int):
        raise ValueError(f"{direction_name}: {key} must be an integer")
    return value


def ranged_int(item, key, direction_name, low, high):
    value = number_field(item, key, direction_name)
    if value < low or value > high:
        raise ValueError(f"{direction_name}: {key} is out of range")
    return value
