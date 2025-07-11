#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"

#include <string>

namespace ast {
    struct boolean_literal : expression {
        boolean_literal(token::token, bool);
        token::token token;
        bool value;

        std::string token_literal() const override;
        std::string str() const override;
    };
} // namespace ast
