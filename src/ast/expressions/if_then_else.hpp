#pragma once

#include "ast/ast.hpp"
#include "ast/statements/block.hpp"
#include "token/token.hpp"

#include <string>

namespace ast {
    struct if_then_else : expression {
        if_then_else(token::token);
        token::token token;
        ast::expression* condition;
        ast::block_stmt *consequence, *alternative;

        std::string token_literal() const override;
        std::string str() const override;
        ~if_then_else();
    };
} // namespace ast
