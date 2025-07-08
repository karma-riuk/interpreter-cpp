#pragma once

#include "ast.hpp"

#include <string>
#include <vector>

namespace ast {
    struct program : public node {
        std::vector<statement*> statements;
        std::string token_literal() const override;

        virtual std::string str() const override;

        ~program();
    };
} // namespace ast
