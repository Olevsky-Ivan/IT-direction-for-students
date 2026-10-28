#include "career/directions/10_ai_direction.hpp"

#include <memory>

namespace career {

std::string AiDirection::category() const {
    return "ai";
}

// Частка всіх вимог.
// Групи math і programming обмежують оцінку, якщо такі обов'язкові вимоги в напрямку є.
// Сильний бік не перекриває слабку другу опору.
double AiDirection::calculateMatch(const Student& student) const {
    double score = coverage(student);
    double mathRatio = weakestEssentialInGroup(student, "math");
    double programmingRatio = weakestEssentialInGroup(student, "programming");
    if (mathRatio < score) {
        score = mathRatio;
    }
    if (programmingRatio < score) {
        score = programmingRatio;
    }
    return clamp01(score);
}

std::unique_ptr<ITDirection> AiDirection::clone() const {
    return std::make_unique<AiDirection>(*this);
}

}
