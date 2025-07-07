#include "return.hpp"

namespace ast {
    return_stmt::return_stmt(token::token token)
        : token(std::move(token)),
          value(nullptr) {}

    std::string return_stmt::token_literal() const {
        return token.literal;
    }

    return_stmt::~return_stmt() {
        delete value;
    };
} // namespace ast
