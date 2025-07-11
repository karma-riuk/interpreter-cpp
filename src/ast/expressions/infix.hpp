#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"

namespace ast {
    struct infix_expr : expression {
        infix_expr(token::token, std::string, ast::expression*);
        token::token token;
        expression* left;
        std::string op;
        expression* right;

        std::string token_literal() const override;
        std::string str() const override;
        ~infix_expr();
    };
} // namespace ast
