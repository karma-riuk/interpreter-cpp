#pragma once
#include "object.hpp"

namespace object {
    struct integer : object {
        int value;
        ::object::type type = type::INTEGER_OBJ;

        std::string inspect();
    };
} // namespace object
