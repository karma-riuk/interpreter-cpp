#pragma once

#include "ast/ast.hpp"
#include "token/token.hpp"

#include <string>

namespace ast {
    struct identifier : expression {
        identifier(token::token token, std::string value);
        token::token token;
        std::string value;

        std::string token_literal() const override;
        std::string str() const override;
    };
} // namespace ast
