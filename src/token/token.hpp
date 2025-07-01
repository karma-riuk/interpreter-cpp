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

    inline std::ostream& operator<<(std::ostream& os, token tok) {
        return os << tok.type << '(' << tok.literal << ')';
    }
} // namespace token
