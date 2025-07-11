#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"

namespace ast {
    struct prefix_expr : expression {
        prefix_expr(token::token token, std::string op);
        token::token token;
        std::string op;
        expression* right;

        std::string token_literal() const override;
        std::string str() const override;
        ~prefix_expr();
    };
} // namespace ast
