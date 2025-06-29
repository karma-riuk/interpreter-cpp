#pragma once

#include "type.hpp"

#include <string>

namespace token {
    struct token {
        token::Type type;
        std::string literal;
    };
} // namespace token
