#pragma once

#include <ostream>

enum class TokenType {
    ILLEGAL,
    EOF_,

    IDENT,
    INT,

    ASSIGN,
    PLUS,

    COMMA,
    SEMICOLON,

    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,

    FUNCTION,
    LET
};

inline std::ostream& operator<<(std::ostream& os, TokenType tt) {
    switch (tt) {
    case TokenType::ILLEGAL:
        return os << "ILLEGAL";
    case TokenType::EOF_:
        return os << "EOF";
    case TokenType::IDENT:
        return os << "IDENT";
    case TokenType::INT:
        return os << "INT";
    case TokenType::ASSIGN:
        return os << "=";
    case TokenType::PLUS:
        return os << "+";
    case TokenType::COMMA:
        return os << ",";
    case TokenType::SEMICOLON:
        return os << ";";
    case TokenType::LPAREN:
        return os << "(";
    case TokenType::RPAREN:
        return os << ")";
    case TokenType::LBRACE:
        return os << "{";
    case TokenType::RBRACE:
        return os << "}";
    case TokenType::FUNCTION:
        return os << "FUNCTION";
    case TokenType::LET:
        return os << "LET";
    default:
        return os << "Unknown";
    }
}
