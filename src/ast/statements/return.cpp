#include "return.hpp"

#include <sstream>

namespace ast {
    return_stmt::return_stmt(token::token token)
        : token(std::move(token)),
          value(nullptr) {}

    return_stmt::return_stmt(token::token token, expression* value)
        : token(std::move(token)),
          value(value) {}

    std::string return_stmt::token_literal() const {
        return token.literal;
    }

    return_stmt::~return_stmt() {
        delete value;
    };

    std::string return_stmt::str() const {
        std::stringstream ss;

        ss << token_literal() << " ";
        if (value != nullptr)
            ss << value->str();

        ss << ';';

        return ss.str();
    };
} // namespace ast
