#include "precedence.hpp"

namespace parser {
    precedence precedence_for(token::type type) {
        switch (type) {
        case token::type::EQ:
        case token::type::NEQ:
            return precedence::EQUALS;
        case token::type::LT:
        case token::type::GT:
            return precedence::LESS_GREATER;
        case token::type::PLUS:
        case token::type::MINUS:
            return precedence::SUM;
        case token::type::ASTERISK:
        case token::type::SLASH:
            return precedence::PRODUCT;
        case token::type::LPAREN:
            return precedence::CALL;
        default:
            return precedence::LOWEST;
        }
    }
} // namespace parser
