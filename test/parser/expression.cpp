#include "ast/expressions/identifier.hpp"
#include "ast/expressions/integer.hpp"
#include "utils.hpp"

#include <doctest.h>

TEST_SUITE("Parser: expression") {
    TEST_CASE_FIXTURE(
        ParserFixture,
        "Simple expression statement with identifier"
    ) {
        setup("foobar;");
        REQUIRE(program->statements.size() == 1);
        ast::expression_stmt* expression_stmt;
        REQUIRE_NOTHROW(
            expression_stmt =
                dynamic_cast<ast::expression_stmt*>(program->statements[0])
        );
        REQUIRE_MESSAGE(
            expression_stmt != nullptr,
            "Couldn't cast statement to an expression statement"
        );

        ast::identifier* ident;
        REQUIRE_NOTHROW(
            ident = dynamic_cast<ast::identifier*>(expression_stmt->expression)
        );
        REQUIRE_MESSAGE(
            ident != nullptr,
            "Couldn't cast expression to an identifier"
        );

        REQUIRE(ident->value == "foobar");
        REQUIRE(ident->token_literal() == "foobar");
    };

    TEST_CASE_FIXTURE(
        ParserFixture,
        "Simple expression statement with integer"
    ) {
        setup("5;");
        REQUIRE(program->statements.size() == 1);
        ast::expression_stmt* expression_stmt;
        REQUIRE_NOTHROW(
            expression_stmt =
                dynamic_cast<ast::expression_stmt*>(program->statements[0])
        );
        REQUIRE_MESSAGE(
            expression_stmt != nullptr,
            "Couldn't cast statement to an expression statement"
        );

        ast::integer_literal* int_lit;
        REQUIRE_NOTHROW(
            int_lit =
                dynamic_cast<ast::integer_literal*>(expression_stmt->expression)
        );
        REQUIRE_MESSAGE(
            int_lit != nullptr,
            "Couldn't cast expression to an identifier"
        );

        REQUIRE(int_lit->value == 5);
        REQUIRE(int_lit->token_literal() == "5");
    };
}
