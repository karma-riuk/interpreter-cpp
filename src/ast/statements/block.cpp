#include "block.hpp"

#include <sstream>

namespace ast {
    block_stmt::block_stmt(token::token token): token(std::move(token)) {}

    std::string block_stmt::token_literal() const {
        return token.literal;
    }

    block_stmt::~block_stmt() {
        for (const auto& stmt : statements)
            delete stmt;
    };

    std::string block_stmt::str() const {
        std::stringstream ss;
        ss << "{";
        for (const auto& stmt : statements)
            ss << stmt->str();
        ss << "}";
        return ss.str();
    };
} // namespace ast
