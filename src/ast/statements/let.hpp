#pragma once

#include "ast/ast.hpp"
#include "ast/expressions/identifier.hpp"
#include "token/token.hpp"

namespace ast {
    struct let_stmt : statement {
        let_stmt(token::token token);

        token::token token;
        identifier* name;
        expression* value;

        std::string token_literal() const override;

        ~let_stmt();
    };
} // namespace ast
