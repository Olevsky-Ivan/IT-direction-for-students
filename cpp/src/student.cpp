#include "career/student.hpp"

#include "career/text.hpp"

#include <algorithm>
#include <utility>

namespace career {

Student::Student(int id, std::string name)
    : Person(id, std::move(name)) {}

std::string Student::role() const {
    return "student";
}

void Student::setSkill(const Skill& skill) {
    for (Skill& current : skills_) {
        if (equalsIgnoreCase(current.name(), skill.name())) {
            current.setLevel(skill.level());
            return;
        }
    }
    skills_.push_back(skill);
}

void Student::removeSkill(const std::string& name) {
    skills_.erase(
        std::remove_if(
            skills_.begin(),
            skills_.end(),
            [&name](const Skill& skill) {
                return equalsIgnoreCase(skill.name(), name);
            }),
        skills_.end());
}

int Student::skillLevel(const std::string& name) const {
    for (const Skill& skill : skills_) {
        if (equalsIgnoreCase(skill.name(), name)) {
            return skill.level();
        }
    }
    return 0;
}

void Student::addInterest(const std::string& interest) {
    if (interest.empty() || hasInterest(interest)) {
        return;
    }
    interests_.push_back(interest);
}

void Student::removeInterest(const std::string& interest) {
    interests_.erase(
        std::remove_if(
            interests_.begin(),
            interests_.end(),
            [&interest](const std::string& current) {
                return equalsIgnoreCase(current, interest);
            }),
        interests_.end());
}

bool Student::hasInterest(const std::string& interest) const {
    for (const std::string& current : interests_) {
        if (equalsIgnoreCase(current, interest)) {
            return true;
        }
    }
    return false;
}

}
