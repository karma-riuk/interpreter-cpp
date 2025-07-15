#include "function.hpp"

#include <sstream>

namespace ast {
    function_literal::function_literal(token::token token)
        : token(std::move(token)),
          body(nullptr) {};

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
        ss << body->str();
        return ss.str();
    };

    function_literal::~function_literal() {
        for (auto& param : parameters)
            delete param;
        if (body != nullptr)
            delete body;
    }

    // ---------------------------- FUNCTION CALL ----------------------------
    function_call::function_call(token::token token, expression* target)
        : token(std::move(token)),
          target(target) {};

    std::string function_call::token_literal() const {
        return token.literal;
    };

    std::string function_call::str() const {
        std::stringstream ss;
        ss << target->str() << "(";
        bool first = true;
        for (auto& param : parameters) {
            if (!first)
                ss << ", ";
            ss << param->str();
            first = false;
        }
        ss << ")";
        return ss.str();
    };

    function_call::~function_call() {
        if (target != nullptr)
            delete target;
        for (auto& param : parameters)
            delete param;
    }

} // namespace ast
