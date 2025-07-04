#include "lexer/lexer.hpp"

#include "token/type.hpp"

#include <doctest.h>
#include <sstream>
#include <string>

TEST_CASE("Single character token") {
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

TEST_CASE("Full tokens") {
    struct test {
        token::type expectedType;
        std::string expectedLiteral;
    };

    std::istringstream ss("let five = 5;\
let ten = 10;\
let add = fn(x, y) {\
    x + y;\
};\
let result = add(five, ten);\
");

    lexer::lexer l{ss};

    test tests[] = {
        // clang-format off
        {token::type::LET, "let"},
        {token::type::IDENTIFIER, "five"},
        {token::type::ASSIGN, "="},
        {token::type::INT, "5"},
        {token::type::SEMICOLON, ";"},

        {token::type::LET, "let"},
        {token::type::IDENTIFIER, "ten"},
        {token::type::ASSIGN, "="},
        {token::type::INT, "10"},
        {token::type::SEMICOLON, ";"},

        {token::type::LET, "let"},
        {token::type::IDENTIFIER, "add"},
        {token::type::ASSIGN, "="},
        {token::type::FUNCTION, "fn"},
        {token::type::LPAREN, "("},
        {token::type::IDENTIFIER, "x"},
        {token::type::COMMA, ","},
        {token::type::IDENTIFIER, "y"},
        {token::type::RPAREN, ")"},
        {token::type::LBRACE, "{"},
        {token::type::IDENTIFIER, "x"},
        {token::type::PLUS, "+"},
        {token::type::IDENTIFIER, "y"},
        {token::type::SEMICOLON, ";"},
        {token::type::RBRACE, "}"},
        {token::type::SEMICOLON, ";"},

        {token::type::LET, "let"},
        {token::type::IDENTIFIER, "result"},
        {token::type::ASSIGN, "="},
        {token::type::IDENTIFIER, "add"},
        {token::type::LPAREN, "("},
        {token::type::IDENTIFIER, "five"},
        {token::type::COMMA, ","},
        {token::type::IDENTIFIER, "ten"},
        {token::type::RPAREN, ")"},
        {token::type::SEMICOLON, ";"},
        // clang-format on
    };

    for (const auto& t : tests) {
        token::token tok = l.next_token();
        CHECK(tok.type == t.expectedType);
        CHECK(tok.literal == t.expectedLiteral);
    }
};
