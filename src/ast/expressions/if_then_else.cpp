
#include "if_then_else.hpp"

#include <sstream>

namespace ast {
    if_then_else::if_then_else(token::token token)
        : token(std::move(token)),
          condition(nullptr),
          consequence(nullptr),
          alternative(nullptr) {};

    std::string if_then_else::token_literal() const {
        return token.literal;
    };

    std::string if_then_else::str() const {
        std::stringstream ss;
        ss << "if " << condition->str() << consequence->str();
        if (alternative != nullptr)
            ss << "else" << alternative->str();
        return ss.str();
    };

    if_then_else::~if_then_else() {
        delete condition;
        delete consequence;
        delete alternative;
    }
} // namespace ast
