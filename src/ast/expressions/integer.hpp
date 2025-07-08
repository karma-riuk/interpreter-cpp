#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"

namespace ast {
    struct integer_literal : expression {
        integer_literal(token::token token, int value);
        token::token token;
        int value;

        std::string token_literal() const override;
        std::string str() const override;
    };
} // namespace ast
