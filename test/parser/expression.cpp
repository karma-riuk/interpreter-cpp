#include "ast/expressions/identifier.hpp"
#include "ast/expressions/integer.hpp"
#include "ast/expressions/prefix.hpp"
#include "utils.hpp"

#include <doctest.h>

TEST_SUITE("Parser: expression") {
    TEST_CASE_FIXTURE(
        ParserFixture,
        "Simple expression statement with identifier"
    ) {
        setup("foobar;");
        REQUIRE(program->statements.size() == 1);
        ast::expression_stmt* expression_stmt =
            cast<ast::expression_stmt>(program->statements[0]);

        ast::identifier* ident =
            cast<ast::identifier>(expression_stmt->expression);

        REQUIRE(ident->value == "foobar");
        REQUIRE(ident->token_literal() == "foobar");
    };

    TEST_CASE_FIXTURE(
        ParserFixture,
        "Simple expression statement with integer"
    ) {
        setup("5;");
        REQUIRE(program->statements.size() == 1);

        ast::expression_stmt* expression_stmt =
            cast<ast::expression_stmt>(program->statements[0]);

        ast::integer_literal* int_lit =
            cast<ast::integer_literal>(expression_stmt->expression);

        REQUIRE(int_lit->value == 5);
        REQUIRE(int_lit->token_literal() == "5");
    };

    // TEST_CASE_FIXTURE(
    //     ParserFixture,
    //     "Simple expression statement with prefix before integer"
    // ) {
    //     SUBCASE("Prefix: '!'") {
    //         setup("!5;");
    //
    //         REQUIRE(program->statements.size() == 1);
    //         ast::expression_stmt* expression_stmt =
    //             cast<ast::expression_stmt>(program->statements[0]);
    //
    //         ast::prefix_expr* prefix_expr;
    //         REQUIRE_NOTHROW(
    //             prefix_expr =
    //                 dynamic_cast<ast::prefix_expr*>(expression_stmt->expression)
    //         );
    //         REQUIRE_MESSAGE(
    //             prefix_expr != nullptr,
    //             "Couldn't cast expression to an identifier"
    //         );
    //
    //         REQUIRE(prefix_expr->value == 5);
    //         REQUIRE(prefix_expr->token_literal() == "5");
    //     }
    //     SUBCASE("Prefix: '-'") {
    //         setup("-15;");
    //
    //         REQUIRE(program->statements.size() == 1);
    //         ast::expression_stmt* expression_stmt =
    //             get_expression_stmt(program->statements[0]);
    //
    //         ast::integer_literal* int_lit;
    //         REQUIRE_NOTHROW(
    //             int_lit = dynamic_cast<ast::integer_literal*>(
    //                 expression_stmt->expression
    //             )
    //         );
    //         REQUIRE_MESSAGE(
    //             int_lit != nullptr,
    //             "Couldn't cast expression to an identifier"
    //         );
    //
    //         REQUIRE(int_lit->value == 5);
    //         REQUIRE(int_lit->token_literal() == "5");
    //     }
    // }
}
