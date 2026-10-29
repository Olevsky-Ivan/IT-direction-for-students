#pragma once

#include "career/directions/02_development_direction.hpp"

namespace career {

class FrontendDirection : public DevelopmentDirection {
public:
    using DevelopmentDirection::DevelopmentDirection;

    std::string category() const override;
    double calculateMatch(const Student& student) const override;
    std::unique_ptr<ITDirection> clone() const override;
};

}
