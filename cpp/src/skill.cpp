#include "career/skill.hpp"

#include <stdexcept>
#include <utility>

namespace career {

Skill::Skill(std::string name, int level)
    : name_(std::move(name))
    , level_(level) {
    if (name_.empty()) {
        throw std::invalid_argument("skill name is empty");
    }
    if (level_ < 0 || level_ > 5) {
        throw std::invalid_argument("skill level is out of range");
    }
}

const std::string& Skill::name() const {
    return name_;
}

int Skill::level() const {
    return level_;
}

void Skill::setLevel(int level) {
    if (level < 0 || level > 5) {
        throw std::invalid_argument("skill level is out of range");
    }
    level_ = level;
}

}
