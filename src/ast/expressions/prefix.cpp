#include "prefix.hpp"

#include "token/token.hpp"

namespace ast {

    prefix_expr::prefix_expr(token::token token, std::string op)
        : token(std::move(token)),
          op(op),
          right(nullptr) {}

    std::string prefix_expr::token_literal() const {
        return token.literal;
    }

    std::string prefix_expr::str() const {
        return token.literal + right->str();
    }
} // namespace ast
