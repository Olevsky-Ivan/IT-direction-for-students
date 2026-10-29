#include "career/directions/07_security_direction.hpp"

#include <memory>

namespace career {

std::string SecurityDirection::category() const {
    return "security";
}

// Поріг — найслабша обов'язкова навичка, навіть якщо вона не нульова.
// Рівень 1 із потрібних 3 дає стелю 1/3, а не середню частку решти навичок.
double SecurityDirection::calculateMatch(const Student& student) const {
    return clamp01(cappedByEssential(student));
}

std::unique_ptr<ITDirection> SecurityDirection::clone() const {
    return std::make_unique<SecurityDirection>(*this);
}

}
