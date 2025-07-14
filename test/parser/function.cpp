#include "ast/expressions/function.hpp"

#include "ast/statements/return.hpp"
#include "utils.hpp"

#include <doctest.h>

TEST_SUITE("Parser: function") {
    TEST_CASE("Malformed if then else (checking for memory leaks)") {}

    TEST_CASE_FIXTURE(ParserFixture, "Parse well formed function literal") {
        SUBCASE("no param function") {
            setup("\
fn () {\
    return true;\
}\
");
            REQUIRE(program->statements.size() == 1);
            CHECK(program->statements[0]->token_literal() == "fn");

            ast::expression_stmt* expr_stmt =
                cast<ast::expression_stmt>(program->statements[0]);

            ast::function_literal* fun =
                cast<ast::function_literal>(expr_stmt->expression);

            // parameters
            CHECK(fun->parameters.size() == 0);

            // block
            REQUIRE(fun->block->statements.size() == 1);
            ast::return_stmt* ret =
                cast<ast::return_stmt>(fun->block->statements[0]);
            test_boolean_literal(ret->value, true);

            // full string
            CHECK(fun->str() == "fn (){return true;}");
        }

        SUBCASE("one param function") {
            setup("\
fn (x) {\
    return x + 1;\
}\
");
            REQUIRE(program->statements.size() == 1);
            CHECK(program->statements[0]->token_literal() == "fn");

            ast::expression_stmt* expr_stmt =
                cast<ast::expression_stmt>(program->statements[0]);

            ast::function_literal* fun =
                cast<ast::function_literal>(expr_stmt->expression);

            // parameters
            REQUIRE(fun->parameters.size() == 1);
            test_identifier(fun->parameters[0], "x");

            // block
            REQUIRE(fun->block->statements.size() == 1);
            ast::return_stmt* ret =
                cast<ast::return_stmt>(fun->block->statements[0]);
            test_infix_expression(ret->value, "x", "+", 1);

            // full string
            CHECK(fun->str() == "fn (x){return (x + 1);}");
        }

        SUBCASE("two param function") {
            setup("\
fn (x, y) {\
    return x + y;\
}\
");
            REQUIRE(program->statements.size() == 1);
            CHECK(program->statements[0]->token_literal() == "fn");

            ast::expression_stmt* expr_stmt =
                cast<ast::expression_stmt>(program->statements[0]);

            ast::function_literal* fun =
                cast<ast::function_literal>(expr_stmt->expression);

            // parameters
            REQUIRE(fun->parameters.size() == 2);
            test_identifier(fun->parameters[0], "x");
            test_identifier(fun->parameters[1], "y");

            // block
            REQUIRE(fun->block->statements.size() == 1);
            ast::return_stmt* ret =
                cast<ast::return_stmt>(fun->block->statements[0]);
            test_infix_expression(ret->value, "x", "+", "y");

            // full string
            CHECK(fun->str() == "fn (x, y){return (x + y);}");
        }

        SUBCASE("two param function assigned to variable") {
            setup("\
let fun = fn (x, y) {\
    return x + y;\
}\
");
            REQUIRE(program->statements.size() == 1);
            CHECK(program->statements[0]->token_literal() == "let");

            ast::let_stmt* let_stmt =
                cast<ast::let_stmt>(program->statements[0]);

            // let lhs
            test_identifier(let_stmt->name, "fun");

            // let rhs
            CHECK(let_stmt->value->token_literal() == "fn");
            ast::function_literal* fun =
                cast<ast::function_literal>(let_stmt->value);

            // parameters
            REQUIRE(fun->parameters.size() == 2);
            test_identifier(fun->parameters[0], "x");
            test_identifier(fun->parameters[1], "y");

            // block
            REQUIRE(fun->block->statements.size() == 1);
            ast::return_stmt* ret =
                cast<ast::return_stmt>(fun->block->statements[0]);
            test_infix_expression(ret->value, "x", "+", "y");

            // full string
            CHECK(fun->str() == "fn (x, y){return (x + y);}");
        }
    }
}
