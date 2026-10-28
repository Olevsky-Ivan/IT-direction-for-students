#pragma once

#include "career/requirement.hpp"
#include "career/student.hpp"

#include <memory>
#include <string>
#include <vector>

namespace career {

class ITDirection {
public:
    ITDirection(
        int id,
        std::string name,
        std::string description,
        int difficulty,
        std::vector<Requirement> requirements);
    virtual ~ITDirection() = default;

    int id() const;
    const std::string& name() const;
    const std::string& description() const;
    int difficulty() const;

    virtual std::string category() const = 0;
    virtual double calculateMatch(const Student& student) const = 0;
    virtual std::unique_ptr<ITDirection> clone() const = 0;

    bool requiresSkill(const std::string& name) const;
    std::vector<std::string> matchedSkills(const Student& student) const;
    std::vector<std::string> missingSkills(const Student& student) const;

protected:
    double coverage(const Student& student) const;
    double cappedByEssential(const Student& student) const;
    double weakestEssentialRatio(const Student& student) const;
    double weakestEssentialInGroup(const Student& student, const std::string& group) const;
    double weakestRequirementRatio(const Student& student) const;
    double coverageWithBestGroup(const Student& student, const std::string& group) const;
    bool hasEssential() const;
    double interestBonus(const Student& student) const;
    static double clamp01(double value);

private:
    int id_;
    std::string name_;
    std::string description_;
    int difficulty_;
    std::vector<Requirement> requirements_;
};

}
