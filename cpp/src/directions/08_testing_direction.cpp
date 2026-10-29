#include "career/directions/08_testing_direction.hpp"

#include <memory>

namespace career {

std::string TestingDirection::category() const {
    return "testing";
}

// Оцінку ставить найслабша обов'язкова вимога, без усереднення.
// Бажана навичка на нулі напрямок не обнуляє.
double TestingDirection::calculateMatch(const Student& student) const {
    if (hasEssential()) {
        return clamp01(weakestEssentialRatio(student));
    }
    return clamp01(weakestRequirementRatio(student));
}

std::unique_ptr<ITDirection> TestingDirection::clone() const {
    return std::make_unique<TestingDirection>(*this);
}

}
