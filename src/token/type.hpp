#pragma once

#include <ostream>

namespace token {

// X-macro list of token types and their string representations
#define TOKEN_LIST                                                             \
    X(ILLEGAL, "ILLEGAL")                                                      \
    X(END_OF_FILE, "EOF")                                                      \
    X(IDENTIFIER, "IDENTIFIER")                                                \
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

    std::ostream& operator<<(std::ostream&, type);
    type lookup_identifier(std::string);
} // namespace token
