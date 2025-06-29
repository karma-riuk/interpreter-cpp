#include "lexer/lexer.hpp"

#include "token/type.hpp"

#include <doctest.h>
#include <sstream>
#include <string>

TEST_CASE("next token") {
    struct test {
        token::type expectedType;
        std::string expectedLiteral;
    };

    std::string input = "=+(){},;";
    std::istringstream ss(input);

    lexer::lexer l{ss};

    test tests[] = {
        {token::type::ASSIGN, "="},
        {token::type::PLUS, "+"},
        {token::type::LPAREN, "("},
        {token::type::RPAREN, ")"},
        {token::type::LBRACE, "{"},
        {token::type::RBRACE, "}"},
        {token::type::COMMA, ","},
        {token::type::SEMICOLON, ";"},
        {token::type::END_OF_FILE, ""},
    };

    for (const auto& t : tests) {
        token::token tok = l.next_token();
        CHECK(tok.type == t.expectedType);
        CHECK(tok.literal == t.expectedLiteral);
    }
};
