#include "infix.hpp"

#include "token/token.hpp"

namespace ast {

    infix_expr::infix_expr(
        token::token token, std::string op, ast::expression* left
    )
        : token(std::move(token)),
          op(op),
          left(left) {}

    std::string infix_expr::token_literal() const {
        return token.literal;
    }

    std::string infix_expr::str() const {
        return "(" + left->str() + " " + op + " " + right->str() + ")";
    }

    infix_expr::~infix_expr() {
        delete left;
        delete right;
    };
} // namespace ast
