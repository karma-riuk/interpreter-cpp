#include "let.hpp"

namespace ast {
    let_stmt::let_stmt(token::token token)
        : token(std::move(token)),
          name(nullptr),
          value(nullptr) {}

    std::string let_stmt::token_literal() const {
        return token.literal;
    }

    let_stmt::~let_stmt() {
        delete name;
        delete value;
    };
} // namespace ast
