#include "let.hpp"

namespace ast {
    let::let(token::token token)
        : token(std::move(token)),
          name(nullptr),
          value(nullptr) {}

    std::string let::token_literal() const {
        return token.literal;
    }

    let::~let() {
        delete name;
        delete value;
    };
} // namespace ast
