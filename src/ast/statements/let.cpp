#include "let.hpp"

#include <sstream>

namespace ast {
    let_stmt::let_stmt(token::token token)
        : token(std::move(token)),
          name(nullptr),
          value(nullptr) {}

    let_stmt::let_stmt(token::token token, identifier* name, expression* value)
        : token(std::move(token)),
          name(name),
          value(value) {}

    std::string let_stmt::token_literal() const {
        return token.literal;
    }

    let_stmt::~let_stmt() {
        delete name;
        delete value;
    };

    std::string let_stmt::str() const {
        std::stringstream ss;

        ss << token_literal() << ' ' << name->str() << " = ";
        if (value != nullptr)
            ss << value->str();

        ss << ';';

        return ss.str();
    };
} // namespace ast
