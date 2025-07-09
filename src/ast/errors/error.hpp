#pragma once

#include "token/token.hpp"
#include "token/type.hpp"

namespace ast::error {
    struct error : public std::runtime_error {
        explicit error(const std::string& message)
            : std::runtime_error(message) {}
    };

    struct parser_error : error {
        explicit parser_error(const std::string& message): error(message) {}
    };

    struct unkown_prefix : parser_error {
        token::token prefix;

        explicit unkown_prefix(token::token prefix, const std::string& message)
            : parser_error(message),
              prefix(prefix) {}
    };

    struct expected_next : parser_error {
        token::type expected_type;

        explicit expected_next(
            token::type expected_type, const std::string& message
        )
            : parser_error(message),
              expected_type(expected_type) {}
    };

} // namespace ast::error
