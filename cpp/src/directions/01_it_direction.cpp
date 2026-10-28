#include "career/directions/01_it_direction.hpp"

#include "career/text.hpp"

#include <stdexcept>
#include <utility>

namespace {

double skillRatio(const career::Student& student, const career::Requirement& requirement) {
    double ratio = static_cast<double>(student.skillLevel(requirement.skill()))
        / static_cast<double>(requirement.minLevel());
    if (ratio > 1.0) {
        return 1.0;
    }
    return ratio;
}

}

namespace career {

ITDirection::ITDirection(
    int id,
    std::string name,
    std::string description,
    int difficulty,
    std::vector<Requirement> requirements)
    : id_(id)
    , name_(std::move(name))
    , description_(std::move(description))
    , difficulty_(difficulty)
    , requirements_(std::move(requirements)) {
    if (name_.empty()) {
        throw std::invalid_argument("direction name is empty");
    }
    if (difficulty_ < 1 || difficulty_ > 5) {
        throw std::invalid_argument("direction difficulty is out of range");
    }
    if (requirements_.empty()) {
        throw std::invalid_argument("direction has no requirements");
    }
}

int ITDirection::id() const {
    return id_;
}

const std::string& ITDirection::name() const {
    return name_;
}

const std::string& ITDirection::description() const {
    return description_;
}

int ITDirection::difficulty() const {
    return difficulty_;
}

bool ITDirection::requiresSkill(const std::string& name) const {
    for (const Requirement& requirement : requirements_) {
        if (equalsIgnoreCase(requirement.skill(), name)) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> ITDirection::matchedSkills(const Student& student) const {
    std::vector<std::string> matched;
    for (const Requirement& requirement : requirements_) {
        if (student.skillLevel(requirement.skill()) >= requirement.minLevel()) {
            matched.push_back(requirement.skill());
        }
    }
    return matched;
}

std::vector<std::string> ITDirection::missingSkills(const Student& student) const {
    std::vector<std::string> missing;
    for (const Requirement& requirement : requirements_) {
        if (student.skillLevel(requirement.skill()) < requirement.minLevel()) {
            missing.push_back(requirement.skill());
        }
    }
    return missing;
}

// Частка закритих вимог: рівень студента ділиться на мінімум вимоги.
// Результат однієї навички не більший за 1, тож рівень понад планку нічого не додає.
// Внесок навички множиться на її вагу.
double ITDirection::coverage(const Student& student) const {
    double weighted = 0.0;
    double weightSum = 0.0;
    for (const Requirement& requirement : requirements_) {
        weighted += requirement.weight() * skillRatio(student, requirement);
        weightSum += requirement.weight();
    }
    return weighted / weightSum;
}

// Оцінка не вища за найслабшу обов'язкову вимогу.
// Якщо обов'язкових немає, лишається звичайна частка.
double ITDirection::cappedByEssential(const Student& student) const {
    double score = coverage(student);
    double essential = weakestEssentialRatio(student);
    if (essential < score) {
        return essential;
    }
    return score;
}

// Найменша частка серед обов'язкових вимог. 1, якщо таких вимог немає.
double ITDirection::weakestEssentialRatio(const Student& student) const {
    bool found = false;
    double weakest = 1.0;
    for (const Requirement& requirement : requirements_) {
        if (!requirement.essential()) {
            continue;
        }
        found = true;
        double ratio = skillRatio(student, requirement);
        if (ratio < weakest) {
            weakest = ratio;
        }
    }
    if (!found) {
        return 1.0;
    }
    return weakest;
}

// Те саме, але лише для обов'язкових вимог однієї групи.
// Порожня група або відсутність таких вимог повертає 1 і нічого не ріже.
double ITDirection::weakestEssentialInGroup(
    const Student& student,
    const std::string& group) const {
    bool found = false;
    double weakest = 1.0;
    for (const Requirement& requirement : requirements_) {
        if (!requirement.essential() || !equalsIgnoreCase(requirement.group(), group)) {
            continue;
        }
        found = true;
        double ratio = skillRatio(student, requirement);
        if (ratio < weakest) {
            weakest = ratio;
        }
    }
    if (!found) {
        return 1.0;
    }
    return weakest;
}

double ITDirection::weakestRequirementRatio(const Student& student) const {
    double weakest = 1.0;
    for (const Requirement& requirement : requirements_) {
        double ratio = skillRatio(student, requirement);
        if (ratio < weakest) {
            weakest = ratio;
        }
    }
    return weakest;
}

// Вимоги з цієї групи взаємозамінні: зараховується найкраща з них.
// Її частка множиться на сумарну вагу всієї групи.
double ITDirection::coverageWithBestGroup(
    const Student& student,
    const std::string& group) const {
    double weighted = 0.0;
    double weightSum = 0.0;
    double groupWeight = 0.0;
    double best = 0.0;
    bool found = false;
    for (const Requirement& requirement : requirements_) {
        weightSum += requirement.weight();
        double ratio = skillRatio(student, requirement);
        if (equalsIgnoreCase(requirement.group(), group) && !group.empty()) {
            found = true;
            groupWeight += requirement.weight();
            if (ratio > best) {
                best = ratio;
            }
            continue;
        }
        weighted += requirement.weight() * ratio;
    }
    if (found) {
        weighted += groupWeight * best;
    }
    return weighted / weightSum;
}

bool ITDirection::hasEssential() const {
    for (const Requirement& requirement : requirements_) {
        if (requirement.essential()) {
            return true;
        }
    }
    return false;
}

// Окремий додаток за інтерес. У відсоток відповідності він не входить.
double ITDirection::interestBonus(const Student& student) const {
    if (student.hasInterest(category()) || student.hasInterest(name_)) {
        return 0.05;
    }
    return 0.0;
}

double ITDirection::clamp01(double value) {
    if (value < 0.0) {
        return 0.0;
    }
    if (value > 1.0) {
        return 1.0;
    }
    return value;
}

}
