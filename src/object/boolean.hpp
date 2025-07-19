#pragma once
#include "object.hpp"

namespace object {
    struct boolean : object {
        bool value;
        ::object::type type = type::BOOLEAN_OBJ;

        explicit boolean(bool value): value(value) {}

        std::string inspect();
    };
} // namespace object
