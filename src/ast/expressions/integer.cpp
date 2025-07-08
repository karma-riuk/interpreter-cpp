#include "integer.hpp"

namespace ast {
    integer_literal::integer_literal(token::token token, int value)
        : token(std::move(token)),
          value(value) {}

    std::string integer_literal::token_literal() const {
        return token.literal;
    };

    std::string integer_literal::str() const {
        return token.literal;
    };
} // namespace ast
