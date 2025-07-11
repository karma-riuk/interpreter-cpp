#include "ast/program.hpp"

#include "ast/statements/let.hpp"
#include "ast/statements/return.hpp"
#include "token/type.hpp"

#include <doctest.h>

TEST_SUITE("Program") {
    TEST_CASE("Let string") {
        ast::program program({new ast::let_stmt(
            token::token(token::type::LET, "let"),
            new ast::identifier(
                token::token(token::type::IDENTIFIER, "myVar"),
                "myVar"
            ),
            new ast::identifier(
                token::token(token::type::IDENTIFIER, "anotherVar"),
                "anotherVar"
            )
        )});

        CHECK(program.str() == "let myVar = anotherVar;");
    }

    TEST_CASE("Return string") {
        ast::program program({new ast::return_stmt(
            token::token(token::type::RETURN, "return"),
            new ast::identifier(
                token::token(token::type::IDENTIFIER, "myVar"),
                "myVar"
            )
        )});

        CHECK(program.str() == "return myVar;");
    }
}
