#include "parser/parser.hpp"

#include <doctest.h>

TEST_SUITE("Precedence") {
    TEST_CASE("Raw precedence") {
        CHECK(parser::precedence::LOWEST < parser::precedence::EQUALS);
        CHECK(parser::precedence::LOWEST < parser::precedence::LESS_GREATER);
        CHECK(parser::precedence::LOWEST < parser::precedence::SUM);
        CHECK(parser::precedence::LOWEST < parser::precedence::PRODUCT);
        CHECK(parser::precedence::LOWEST < parser::precedence::PREFIX);
        CHECK(parser::precedence::LOWEST < parser::precedence::CALL);

        CHECK(parser::precedence::EQUALS < parser::precedence::LESS_GREATER);
        CHECK(parser::precedence::EQUALS < parser::precedence::SUM);
        CHECK(parser::precedence::EQUALS < parser::precedence::PRODUCT);
        CHECK(parser::precedence::EQUALS < parser::precedence::PREFIX);
        CHECK(parser::precedence::EQUALS < parser::precedence::CALL);

        CHECK(parser::precedence::LESS_GREATER < parser::precedence::SUM);
        CHECK(parser::precedence::LESS_GREATER < parser::precedence::PRODUCT);
        CHECK(parser::precedence::LESS_GREATER < parser::precedence::PREFIX);
        CHECK(parser::precedence::LESS_GREATER < parser::precedence::CALL);

        CHECK(parser::precedence::SUM < parser::precedence::PRODUCT);
        CHECK(parser::precedence::SUM < parser::precedence::PREFIX);
        CHECK(parser::precedence::SUM < parser::precedence::CALL);

        CHECK(parser::precedence::PRODUCT < parser::precedence::PREFIX);
        CHECK(parser::precedence::PRODUCT < parser::precedence::CALL);

        CHECK(parser::precedence::PREFIX < parser::precedence::CALL);
    }

    TEST_CASE("Operator precedence") {
        auto& prec = parser::precedence_for;
        CHECK(prec(token::type::EQ) == prec(token::type::NEQ));
        CHECK(prec(token::type::LT) == prec(token::type::GT));
        CHECK(prec(token::type::PLUS) == prec(token::type::MINUS));
        CHECK(prec(token::type::ASTERISK) == prec(token::type::SLASH));

        CHECK(prec(token::type::EQ) < prec(token::type::LT));
        CHECK(prec(token::type::EQ) < prec(token::type::PLUS));
        CHECK(prec(token::type::EQ) < prec(token::type::ASTERISK));

        CHECK(prec(token::type::LT) < prec(token::type::PLUS));
        CHECK(prec(token::type::LT) < prec(token::type::ASTERISK));

        CHECK(prec(token::type::PLUS) < prec(token::type::ASTERISK));
    }
}
