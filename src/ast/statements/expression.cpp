#include "expression.hpp"

#include <sstream>

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

    std::string expression_stmt::str() const {
        std::stringstream ss;

        if (expression != nullptr)
            ss << expression->str();

        return ss.str();
    };
} // namespace ast
