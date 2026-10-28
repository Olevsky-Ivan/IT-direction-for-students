#include "career/directions/05_fullstack_direction.hpp"

#include <memory>

namespace career {

std::string FullstackDirection::category() const {
    return "fullstack";
}

// Частка всіх вимог.
// Далі дві групи, якщо у вимогах вони позначені: interface і server.
// Оцінка не вища за найслабшу обов'язкову навичку кожної з цих сторін.
double FullstackDirection::calculateMatch(const Student& student) const {
    double score = coverage(student);
    double interfaceRatio = weakestEssentialInGroup(student, "interface");
    double serverRatio = weakestEssentialInGroup(student, "server");
    if (interfaceRatio < score) {
        score = interfaceRatio;
    }
    if (serverRatio < score) {
        score = serverRatio;
    }
    return clamp01(score);
}

std::unique_ptr<ITDirection> FullstackDirection::clone() const {
    return std::make_unique<FullstackDirection>(*this);
}

}
