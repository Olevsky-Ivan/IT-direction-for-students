#pragma once

#include <string>

namespace career {

class Requirement {
public:
    Requirement(
        std::string skill,
        int minLevel,
        double weight,
        bool essential,
        std::string group);

    const std::string& skill() const;
    int minLevel() const;
    double weight() const;
    bool essential() const;
    const std::string& group() const;

private:
    std::string skill_;
    int minLevel_;
    double weight_;
    bool essential_;
    std::string group_;
};

}
