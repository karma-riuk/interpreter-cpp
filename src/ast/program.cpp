#include "program.hpp"

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
} // namespace ast
