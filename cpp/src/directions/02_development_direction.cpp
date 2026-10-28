#include "career/directions/02_development_direction.hpp"

#include <memory>

namespace career {

std::string DevelopmentDirection::category() const {
    return "development";
}

// Загальна розробка: лише частка закритих вимог, без окремого порога.
double DevelopmentDirection::calculateMatch(const Student& student) const {
    return clamp01(coverage(student));
}

std::unique_ptr<ITDirection> DevelopmentDirection::clone() const {
    return std::make_unique<DevelopmentDirection>(*this);
}

}
