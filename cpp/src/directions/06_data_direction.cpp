#include "career/directions/06_data_direction.hpp"

#include <memory>

namespace career {

std::string DataDirection::category() const {
    return "data";
}

// Поріг ставить найслабша обов'язкова вимога цього напрямку, а не фіксований список SQL чи статистики.
double DataDirection::calculateMatch(const Student& student) const {
    return clamp01(cappedByEssential(student));
}

std::unique_ptr<ITDirection> DataDirection::clone() const {
    return std::make_unique<DataDirection>(*this);
}

}
