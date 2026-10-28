#pragma once

#include "career/directions/01_it_direction.hpp"

namespace career {

class SecurityDirection : public ITDirection {
public:
    using ITDirection::ITDirection;

    std::string category() const override;
    double calculateMatch(const Student& student) const override;
    std::unique_ptr<ITDirection> clone() const override;
};

}
