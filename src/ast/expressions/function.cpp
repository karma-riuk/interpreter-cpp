#include "function.hpp"

#include <sstream>

namespace ast {
    function_literal::function_literal(token::token token)
        : token(std::move(token)),
          block(nullptr) {};

    std::string function_literal::token_literal() const {
        return token.literal;
    };

    std::string function_literal::str() const {
        std::stringstream ss;
        ss << "fn (";
        bool first = true;
        for (auto& param : parameters) {
            if (!first)
                ss << ", ";
            ss << param->str();
            first = false;
        }
        ss << ")";
        ss << block->str();
        return ss.str();
    };

    function_literal::~function_literal() {
        for (auto& param : parameters)
            delete param;
        if (block != nullptr)
            delete block;
    }
} // namespace ast
