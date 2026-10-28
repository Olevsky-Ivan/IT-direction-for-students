#include "career/directions/09_mobile_direction.hpp"

#include <memory>

namespace career {

std::string MobileDirection::category() const {
    return "mobile";
}

// Вимоги з групою platform взаємозамінні: зараховується найкраща з них.
// Назви платформ у класі не зашиті. Решта вимог рахується звичайно.
double MobileDirection::calculateMatch(const Student& student) const {
    return clamp01(coverageWithBestGroup(student, "platform"));
}

std::unique_ptr<ITDirection> MobileDirection::clone() const {
    return std::make_unique<MobileDirection>(*this);
}

}
