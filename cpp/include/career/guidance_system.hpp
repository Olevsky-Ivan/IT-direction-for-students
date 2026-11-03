#pragma once

#include "career/recommendation.hpp"

#include <memory>
#include <string>
#include <vector>

namespace career {

class CareerGuidanceSystem {
public:
    void addDirection(std::unique_ptr<ITDirection> direction);
    void addStudent(Student student);

    std::vector<const ITDirection*> findDirectionsBySkill(const std::string& skill) const;
    const Student* findStudentByName(const std::string& name) const;

    std::vector<Recommendation> recommend(const Student& student) const;
    std::vector<Recommendation> sortedByName(const Student& student) const;

private:
    std::vector<Recommendation> build(const Student& student) const;

    std::vector<std::unique_ptr<ITDirection>> directions_;
    std::vector<Student> students_;
};

const Recommendation* binaryFindByName(
    const std::vector<Recommendation>& sortedByName,
    const std::string& name);

}
