#include "identifier.hpp"

namespace ast {
    identifier::identifier(token::token token, std::string value)
        : token(std::move(token)),
          value(std::move(value)) {}

    std::string identifier::token_literal() const {
        return token.literal;
    }
} // namespace ast
