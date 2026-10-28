#include "career/directions/03_frontend_direction.hpp"

#include <memory>

namespace career {

std::string FrontendDirection::category() const {
    return "frontend";
}

// Частка всіх вимог, але не вища за найслабшу обов'язкову.
// Бажана навичка на нулі цю межу не ставить.
double FrontendDirection::calculateMatch(const Student& student) const {
    return clamp01(cappedByEssential(student));
}

std::unique_ptr<ITDirection> FrontendDirection::clone() const {
    return std::make_unique<FrontendDirection>(*this);
}

}
