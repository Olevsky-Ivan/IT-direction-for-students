#pragma once

#include "career/person.hpp"
#include "career/skill.hpp"

#include <string>
#include <vector>

namespace career {

class Student : public Person {
public:
    Student(int id, std::string name);

    std::string role() const override;

    void setSkill(const Skill& skill);
    void removeSkill(const std::string& name);
    int skillLevel(const std::string& name) const;

    void addInterest(const std::string& interest);
    void removeInterest(const std::string& interest);
    bool hasInterest(const std::string& interest) const;

private:
    std::vector<Skill> skills_;
    std::vector<std::string> interests_;
};

}
