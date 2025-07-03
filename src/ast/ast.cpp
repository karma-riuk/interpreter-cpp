#include "ast.hpp"

namespace ast {
    std::string program ::token_literal() const {
        if (statements.size() > 0)
            return statements[0]->token_literal();
        return "";
    }
} // namespace ast
