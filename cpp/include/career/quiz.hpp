#pragma once

#include <map>
#include <string>
#include <vector>

namespace career {

struct QuizQuestion {
    std::string id;
    std::string skill;
    std::string correctOptionId;
};

struct DrawnQuestion {
    QuizQuestion question;
};

struct SkillLevel {
    std::string skill;
    int correct;
    int asked;
    int level;
};

std::vector<QuizQuestion> drawQuestions(
    const std::vector<QuizQuestion>& bank,
    int count,
    unsigned int seed);

std::vector<SkillLevel> scoreQuestions(
    const std::vector<QuizQuestion>& asked,
    const std::map<std::string, std::string>& answers);

std::string accuracyNote(int smallestAsked);

}
