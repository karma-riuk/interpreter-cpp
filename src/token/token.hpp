#pragma once

#include "type.hpp"

#include <string>

namespace token {
    struct token {
        ::token::type type;
        std::string literal;
    };
} // namespace token
