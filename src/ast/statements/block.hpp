#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"

#include <vector>

namespace ast {
    struct block_stmt : statement {
        block_stmt(token::token token);

        token::token token;
        std::vector<ast::statement*> statements;

        std::string token_literal() const override;
        std::string str() const override;

        ~block_stmt();
    };
} // namespace ast
