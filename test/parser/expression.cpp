#include "ast/expressions/identifier.hpp"
#include "utils.hpp"

#include <doctest.h>

TEST_SUITE("Parser: expression") {
    TEST_CASE_FIXTURE(ParserFixture, "Simple expression statement") {
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
}
