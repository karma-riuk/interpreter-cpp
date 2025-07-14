#pragma once

#include "ast/ast.hpp"
#include "ast/expressions/identifier.hpp"
#include "ast/statements/block.hpp"
#include "token/token.hpp"

#include <string>

namespace ast {
    struct function_literal : expression {
        function_literal(token::token);
        token::token token;
        std::vector<identifier*> parameters;
        ast::block_stmt* body;

        std::string token_literal() const override;
        std::string str() const override;
        ~function_literal();
    };
} // namespace ast
