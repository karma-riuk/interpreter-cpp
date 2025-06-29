#include "lexer.hpp"

#include "token/token.hpp"

#include <iostream>

namespace lexer {
    token::token lexer::next_token() {
        char c;
        if (!(input >> c))
            return {token::type::END_OF_FILE, ""};

        switch (c) {
        case '=':
            return {token::type::ASSIGN, c};
        case '+':
            return {token::type::PLUS, c};
        case ',':
            return {token::type::COMMA, c};
        case ';':
            return {token::type::SEMICOLON, c};
        case '(':
            return {token::type::LPAREN, c};
        case ')':
            return {token::type::RPAREN, c};
        case '{':
            return {token::type::LBRACE, c};
        case '}':
            return {token::type::RBRACE, c};
        }
        return {token::type::ILLEGAL, c};
    };

} // namespace lexer
