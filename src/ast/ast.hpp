#pragma once

#include <string>

namespace ast {
    struct node {
        virtual std::string token_literal() const = 0;
        virtual std::string str() const = 0;
        virtual ~node() = default;
    };

    struct statement : node {};

    struct expression : node {};
} // namespace ast
