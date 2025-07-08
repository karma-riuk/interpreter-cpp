#include "ast/ast.hpp"
#include "token/token.hpp"

namespace ast {
    struct expression_stmt : statement {
        expression_stmt(token::token token);

        token::token token;
        ast::expression* expression;

        std::string token_literal() const override;

        ~expression_stmt();
    };
} // namespace ast
