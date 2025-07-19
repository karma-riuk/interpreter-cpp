#pragma once
#include "object.hpp"

namespace object {
    struct integer : object {
        int value;
        ::object::type type = type::INTEGER_OBJ;

        explicit integer(int value): value(value) {}

        std::string inspect();
    };
} // namespace object
