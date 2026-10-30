#include "career/guidance_system.hpp"

#include "career/text.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace career {

void CareerGuidanceSystem::addDirection(std::unique_ptr<ITDirection> direction) {
    if (!direction) {
        throw std::invalid_argument("direction is empty");
    }
    directions_.push_back(std::move(direction));
}

void CareerGuidanceSystem::addStudent(Student student) {
    students_.push_back(std::move(student));
}

std::vector<const ITDirection*> CareerGuidanceSystem::findDirectionsBySkill(
    const std::string& skill) const {
    std::vector<const ITDirection*> found;
    for (const std::unique_ptr<ITDirection>& direction : directions_) {
        if (direction->requiresSkill(skill)) {
            found.push_back(direction.get());
        }
    }
    return found;
}

const Student* CareerGuidanceSystem::findStudentByName(const std::string& name) const {
    for (const Student& student : students_) {
        if (equalsIgnoreCase(student.name(), name)) {
            return &student;
        }
    }
    return nullptr;
}

std::vector<Recommendation> CareerGuidanceSystem::build(const Student& student) const {
    std::vector<Recommendation> items;
    items.reserve(directions_.size());
    for (const std::unique_ptr<ITDirection>& direction : directions_) {
        items.emplace_back(*direction, student);
    }
    return items;
}

std::vector<Recommendation> CareerGuidanceSystem::recommend(const Student& student) const {
    std::vector<Recommendation> items = build(student);
    std::sort(items.begin(), items.end(), byFit);
    return items;
}

std::vector<Recommendation> CareerGuidanceSystem::sortedByName(const Student& student) const {
    std::vector<Recommendation> items = build(student);
    std::sort(items.begin(), items.end(), [](const Recommendation& left, const Recommendation& right) {
        return byName(left, right);
    });
    return items;
}

// Двійковий пошук лише по списку, уже відсортованому через byName.
const Recommendation* binaryFindByName(
    const std::vector<Recommendation>& sortedByName,
    const std::string& name) {
    auto found = std::lower_bound(
        sortedByName.begin(),
        sortedByName.end(),
        name,
        [](const Recommendation& item, const std::string& key) {
            return byName(item, key);
        });
    if (found == sortedByName.end() || !equalsIgnoreCase(found->name(), name)) {
        return nullptr;
    }
    return &(*found);
}

}
