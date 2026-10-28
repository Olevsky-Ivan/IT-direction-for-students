#pragma once

#include <string>

namespace career {

class Skill {
public:
    Skill(std::string name, int level);

    const std::string& name() const;
    int level() const;
    void setLevel(int level);

private:
    std::string name_;
    int level_;
};

}
