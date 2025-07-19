#pragma once
#include "object.hpp"

namespace object {
    struct boolean : object {
        bool value;
        ::object::type type = type::BOOLEAN_OBJ;

        std::string inspect();
    };
} // namespace object
