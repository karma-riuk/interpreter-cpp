#pragma once

#include <string>
#include <vector>

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

    struct program : public node {
        std::vector<statement*> statements;
        std::string token_literal() const override;

        ~program() {
            for (const auto& ref : statements)
                delete ref;
        };
    };
} // namespace ast
