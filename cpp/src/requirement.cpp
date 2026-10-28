#include "career/requirement.hpp"

#include <stdexcept>
#include <utility>

namespace career {

Requirement::Requirement(
    std::string skill,
    int minLevel,
    double weight,
    bool essential,
    std::string group)
    : skill_(std::move(skill))
    , minLevel_(minLevel)
    , weight_(weight)
    , essential_(essential)
    , group_(std::move(group)) {
    if (skill_.empty()) {
        throw std::invalid_argument("requirement skill is empty");
    }
    if (minLevel_ < 1 || minLevel_ > 5) {
        throw std::invalid_argument("requirement level is out of range");
    }
    if (weight_ <= 0.0) {
        throw std::invalid_argument("requirement weight must be positive");
    }
}

const std::string& Requirement::skill() const {
    return skill_;
}

int Requirement::minLevel() const {
    return minLevel_;
}

double Requirement::weight() const {
    return weight_;
}

bool Requirement::essential() const {
    return essential_;
}

const std::string& Requirement::group() const {
    return group_;
}

}
