#pragma once

#include <iostream>
#include <string>

namespace ast {
    struct node {
        virtual std::string token_literal() const = 0;
        virtual std::string str() const = 0;
        virtual ~node() = default;
    };

    inline std::ostream& operator<<(std::ostream& os, const node& n) {
        return os << n.str();
    }

    inline std::ostream& operator<<(std::ostream& os, const node* n) {
        return os << n->str();
    }

    struct statement : node {};

    struct expression : node {};
} // namespace ast
