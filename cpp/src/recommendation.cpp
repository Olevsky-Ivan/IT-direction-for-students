#include "career/recommendation.hpp"

#include "career/text.hpp"

#include <cmath>
#include <utility>

namespace career {

Recommendation::Recommendation(const ITDirection& direction, const Student& student)
    : directionId_(direction.id())
    , name_(direction.name())
    , category_(direction.category())
    , match_(direction.calculateMatch(student))
    , matchedSkills_(direction.matchedSkills(student))
    , missingSkills_(direction.missingSkills(student)) {}

int Recommendation::directionId() const {
    return directionId_;
}

const std::string& Recommendation::name() const {
    return name_;
}

const std::string& Recommendation::category() const {
    return category_;
}

double Recommendation::match() const {
    return match_;
}

const std::vector<std::string>& Recommendation::matchedSkills() const {
    return matchedSkills_;
}

const std::vector<std::string>& Recommendation::missingSkills() const {
    return missingSkills_;
}

bool byName(const Recommendation& left, const Recommendation& right) {
    return toLower(left.name()) < toLower(right.name());
}

bool byName(const Recommendation& item, const std::string& name) {
    return toLower(item.name()) < toLower(name);
}

bool byFit(const Recommendation& left, const Recommendation& right) {
    double difference = left.match() - right.match();
    if (difference > 1e-9) {
        return true;
    }
    if (difference < -1e-9) {
        return false;
    }
    return byName(left, right);
}

}
