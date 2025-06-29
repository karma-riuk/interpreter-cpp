#include "lexer/lexer.hpp"

#include "token/type.hpp"

#include <doctest.h>
#include <string>

TEST_CASE("next token") {
    struct test {
        token::type expectedType;
        std::string expectedLiteral;
    };

    std::string input = "=+(){},;";

    lexer::lexer l{};

    test tests[] = {
        {token::type::ASSIGN, "="},
        {token::type::PLUS, "+"},
        {token::type::LPAREN, "("},
        {token::type::RPAREN, ")"},
        {token::type::LBRACE, "{"},
        {token::type::RBRACE, "}"},
        {token::type::COMMA, ","},
        {token::type::SEMICOLON, ";"},
        {token::type::EOF_, ""},
    };

    for (const auto& t : tests) {
        token::token tok = l.next_token();
        CHECK(tok.type == t.expectedType);
        CHECK(tok.literal == t.expectedLiteral);
    }
};
