#include "lexer.hpp"

#include "token/token.hpp"
#include "token/type.hpp"

#include <cctype>
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
        case '-':
            return {token::type::MINUS, c};
        case '!':
            return {token::type::BANG, c};
        case '*':
            return {token::type::ASTERISK, c};
        case '/':
            return {token::type::SLASH, c};
        case '<':
            return {token::type::LT, c};
        case '>':
            return {token::type::GT, c};
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
        default:
            if (is_letter(c)) {
                std::string identifier_or_keyword = read_string(c);
                return {
                    token::lookup_identifier(identifier_or_keyword),
                    identifier_or_keyword
                };
            }
            if (std::isdigit(c))
                return {token::type::INT, read_int(c)};

            return {token::type::ILLEGAL, c};
        }
    }

    bool lexer::is_letter(char c) {
        return c == '_' || std::isalpha(static_cast<unsigned char>(c));
    }

    std::string lexer::read_string(char first_char) {
        std::string result;
        result.push_back(first_char);
        for (char c = input.peek(); is_letter(c); c = input.peek())
            result.push_back(input.get());
        return result;
    }

    std::string lexer::read_int(char first_digit) {
        std::string result;
        result.push_back(first_digit);
        for (char c = input.peek(); std::isdigit(c); c = input.peek())
            result.push_back(input.get());
        return result;
    }


} // namespace lexer
