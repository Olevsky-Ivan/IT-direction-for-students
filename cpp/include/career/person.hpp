#pragma once

#include <string>

namespace career {

class Person {
public:
    Person(int id, std::string name);
    virtual ~Person() = default;

    int id() const;
    const std::string& name() const;
    void setName(std::string name);
    virtual std::string role() const = 0;

private:
    int id_;
    std::string name_;
};

}
