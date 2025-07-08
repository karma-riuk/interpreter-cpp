#pragma once

#include <string>

namespace ast {
    struct node {
        virtual std::string token_literal() const = 0;
        virtual ~node() = default;
    };

    struct statement : node {
        virtual std::string token_literal() const override = 0;
    };

    struct expression : node {
        virtual std::string token_literal() const override = 0;
    };
} // namespace ast
