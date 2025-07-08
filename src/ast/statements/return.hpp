#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"

namespace ast {
    struct return_stmt : statement {
        return_stmt(token::token token);
        return_stmt(token::token token, expression* value);

        token::token token;
        expression* value;

        std::string token_literal() const override;
        std::string str() const override;

        ~return_stmt();
    };
} // namespace ast
