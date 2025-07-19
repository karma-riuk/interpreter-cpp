#pragma once
#include "object.hpp"

namespace object {
    struct null : object {
        ::object::type type = type::NULL_OBJ;

        std::string inspect();
    };
} // namespace object
