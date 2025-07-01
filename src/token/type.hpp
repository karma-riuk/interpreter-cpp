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
    X(MINUS, "-")                                                              \
    X(BANG, "!")                                                               \
    X(ASTERISK, "*")                                                           \
    X(SLASH, "/")                                                              \
    X(LT, "<")                                                                 \
    X(GT, ">")                                                                 \
    X(COMMA, ",")                                                              \
    X(SEMICOLON, ";")                                                          \
    X(LPAREN, "(")                                                             \
    X(RPAREN, ")")                                                             \
    X(LBRACE, "{")                                                             \
    X(RBRACE, "}")                                                             \
    X(LET, "LET")                                                              \
    X(FUNCTION, "FUNCTION")                                                    \
    X(IF, "IF")                                                                \
    X(ELSE, "ELSE")                                                            \
    X(TRUE, "TRUE")                                                            \
    X(FALSE, "FALSE")                                                          \
    X(EQ, "==")                                                                \
    X(NEQ, "!=")                                                               \
    X(RETURN, "RETURN")

    // Define the TokenType enum using the X-macro
    enum class type {
#define X(name, str) name,
        TOKEN_LIST
#undef X
    };

    std::ostream& operator<<(std::ostream&, type);
    type lookup_identifier(std::string);
} // namespace token
