#pragma once

#include "type.hpp"

#include <string>

namespace token {
    struct token {
        ::token::type type;
        std::string literal;

        token(::token::type t, std::string s): type(t), literal(s) {}

        token(::token::type t, char c): type(t), literal(1, c) {}
    };
} // namespace token
