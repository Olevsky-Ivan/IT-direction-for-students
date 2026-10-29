#include "career/quiz.hpp"

#include <algorithm>
#include <random>

namespace career {
namespace {

std::map<std::string, int> quotasFor(const std::vector<std::string>& skills, int count) {
    std::map<std::string, int> quotas;
    if (skills.empty() || count <= 0) {
        return quotas;
    }
    int base = count / static_cast<int>(skills.size());
    int extra = count % static_cast<int>(skills.size());
    for (const std::string& skill : skills) {
        quotas[skill] = base;
    }
    for (int index = 0; index < extra; ++index) {
        quotas[skills[static_cast<std::size_t>(index)]] += 1;
    }
    return quotas;
}

int levelFrom(int correct, int asked) {
    if (asked <= 0) {
        return 0;
    }
    return (correct * 5 + asked / 2) / asked;
}

}

std::vector<QuizQuestion> drawQuestions(
    const std::vector<QuizQuestion>& bank,
    int count,
    unsigned int seed) {
    std::map<std::string, std::vector<QuizQuestion>> bySkill;
    std::vector<std::string> skills;
    for (const QuizQuestion& question : bank) {
        if (bySkill[question.skill].empty()) {
            skills.push_back(question.skill);
        }
        bySkill[question.skill].push_back(question);
    }
    std::mt19937 rng(seed);
    std::shuffle(skills.begin(), skills.end(), rng);
    std::map<std::string, int> quotas = quotasFor(skills, count);
    std::vector<QuizQuestion> picked;
    for (const auto& entry : bySkill) {
        std::vector<QuizQuestion> pool = entry.second;
        std::shuffle(pool.begin(), pool.end(), rng);
        int take = quotas[entry.first];
        if (take > static_cast<int>(pool.size())) {
            take = static_cast<int>(pool.size());
        }
        for (int index = 0; index < take; ++index) {
            picked.push_back(pool[static_cast<std::size_t>(index)]);
        }
    }
    std::shuffle(picked.begin(), picked.end(), rng);
    return picked;
}

std::vector<SkillLevel> scoreQuestions(
    const std::vector<QuizQuestion>& asked,
    const std::map<std::string, std::string>& answers) {
    std::map<std::string, SkillLevel> totals;
    for (const QuizQuestion& question : asked) {
        SkillLevel& level = totals[question.skill];
        level.skill = question.skill;
        level.asked += 1;
        auto answer = answers.find(question.id);
        if (answer != answers.end() && answer->second == question.correctOptionId) {
            level.correct += 1;
        }
    }
    std::vector<SkillLevel> levels;
    for (auto& entry : totals) {
        entry.second.level = levelFrom(entry.second.correct, entry.second.asked);
        levels.push_back(entry.second);
    }
    return levels;
}

std::string accuracyNote(int smallestAsked) {
    if (smallestAsked <= 1) {
        return "На частину напрямків випало лише одне питання. Прогалину видно, але одна відповідь помітно змінює бал.";
    }
    if (smallestAsked == 2) {
        return "На кожен напрямок випало щонайменше два питання. Одна вдала відповідь уже не вирішує тему.";
    }
    return "На кожен напрямок випало щонайменше три питання. Бал склався з кількох різних перевірок.";
}

}
