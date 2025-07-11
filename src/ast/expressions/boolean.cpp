#include "boolean.hpp"

namespace ast {
    boolean_literal::boolean_literal(token::token token, bool value)
        : token(std::move(token)),
          value(value) {}

    std::string boolean_literal::token_literal() const {
        return token.literal;
    }

    std::string boolean_literal::str() const {
        return token.literal;
    };
} // namespace ast
