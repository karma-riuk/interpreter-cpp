#include "program.hpp"

#include <sstream>

namespace ast {
    std::string program ::token_literal() const {
        if (statements.size() > 0)
            return statements[0]->token_literal();
        return "";
    }

    program::~program() {
        for (const auto& ref : statements)
            delete ref;
    };

    std::string program::str() const {
        std::stringstream ss;
        for (const auto& stmt : statements)
            ss << stmt->str();

        return ss.str();
    };
} // namespace ast
