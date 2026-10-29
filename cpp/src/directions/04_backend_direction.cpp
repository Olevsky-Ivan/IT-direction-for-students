#include "career/directions/04_backend_direction.hpp"

#include <memory>

namespace career {

std::string BackendDirection::category() const {
    return "backend";
}

// Те саме правило, що у фронтенда: поріг ставить найслабша обов'язкова вимога цього напрямку.
double BackendDirection::calculateMatch(const Student& student) const {
    return clamp01(cappedByEssential(student));
}

std::unique_ptr<ITDirection> BackendDirection::clone() const {
    return std::make_unique<BackendDirection>(*this);
}

}
