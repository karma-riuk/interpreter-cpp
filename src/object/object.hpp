#pragma once

#include "type.hpp"

#include <string>

namespace object {
    struct object {
        ::object::type type;
        virtual std::string inspect() = 0;
    };

} // namespace object
