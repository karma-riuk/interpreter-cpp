#pragma once

#include <array>
#include <ostream>
#include <string_view>

namespace token {

// X-macro list of token types and their string representations
#define TOKEN_LIST                                                             \
    X(ILLEGAL, "ILLEGAL")                                                      \
    X(EOF_, "EOF")                                                             \
    X(IDENT, "IDENT")                                                          \
    X(INT, "INT")                                                              \
    X(ASSIGN, "=")                                                             \
    X(PLUS, "+")                                                               \
    X(COMMA, ",")                                                              \
    X(SEMICOLON, ";")                                                          \
    X(LPAREN, "(")                                                             \
    X(RPAREN, ")")                                                             \
    X(LBRACE, "{")                                                             \
    X(RBRACE, "}")                                                             \
    X(FUNCTION, "FUNCTION")                                                    \
    X(LET, "LET")

    // Define the TokenType enum using the X-macro
    enum class type {
#define X(name, str) name,
        TOKEN_LIST
#undef X
    };

    // Array mapping enum values to their string representations
    static constexpr std::
        array<std::string_view, static_cast<size_t>(type::LET) + 1>
            tokenTypeStrings = {
#define X(name, str) str,
                TOKEN_LIST
#undef X
    };

    // Stream insertion operator using the lookup array
    inline std::ostream& operator<<(std::ostream& os, type type) {
        auto idx = static_cast<size_t>(type);
        if (idx < tokenTypeStrings.size())
            return os << tokenTypeStrings[idx];
        return os << "Unknown";
    }
} // namespace token
