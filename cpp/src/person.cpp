#include "career/person.hpp"

#include <stdexcept>
#include <utility>

namespace career {

Person::Person(int id, std::string name)
    : id_(id)
    , name_(std::move(name)) {
    if (name_.empty()) {
        throw std::invalid_argument("person name is empty");
    }
}

int Person::id() const {
    return id_;
}

const std::string& Person::name() const {
    return name_;
}

void Person::setName(std::string name) {
    if (name.empty()) {
        throw std::invalid_argument("person name is empty");
    }
    name_ = std::move(name);
}

}
