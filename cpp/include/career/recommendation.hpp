#pragma once

#include "career/directions/01_it_direction.hpp"

#include <string>
#include <vector>

namespace career {

class Recommendation {
public:
    Recommendation(const ITDirection& direction, const Student& student);

    int directionId() const;
    const std::string& name() const;
    const std::string& category() const;
    double match() const;
    const std::vector<std::string>& matchedSkills() const;
    const std::vector<std::string>& missingSkills() const;

private:
    int directionId_;
    std::string name_;
    std::string category_;
    double match_;
    std::vector<std::string> matchedSkills_;
    std::vector<std::string> missingSkills_;
};

bool byName(const Recommendation& left, const Recommendation& right);
bool byName(const Recommendation& item, const std::string& name);
bool byFit(const Recommendation& left, const Recommendation& right);

}
