#include "expression.hpp"

namespace ast {

    expression_stmt::expression_stmt(token::token token)
        : token(std::move(token)),
          expression(nullptr) {}

    std::string expression_stmt::token_literal() const {
        return token.literal;
    }

    expression_stmt::~expression_stmt() {
        delete expression;
    }
} // namespace ast
