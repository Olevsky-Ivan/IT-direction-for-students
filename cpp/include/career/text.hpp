#pragma once

#include <cctype>
#include <string>

namespace career {

inline std::string toLower(std::string text) {
    for (char& ch : text) {
        unsigned char symbol = static_cast<unsigned char>(ch);
        ch = static_cast<char>(std::tolower(symbol));
    }
    return text;
}

inline bool equalsIgnoreCase(const std::string& left, const std::string& right) {
    return toLower(left) == toLower(right);
}

}
