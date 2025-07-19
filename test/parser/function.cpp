#include "ast/expressions/function.hpp"

#include "ast/errors/error.hpp"
#include "ast/statements/return.hpp"
#include "token/type.hpp"
#include "utils.hpp"

#include <doctest.h>

TEST_SUITE("Parser: function literal") {
    TEST_CASE("Malformed function literal (checking for memory leaks)") {
        SUBCASE("Missing opening paren no param") {
            test::utils::test_failing_parsing(
                "fn ) { return 2; }",
                {token::type::LPAREN}
            );
        }
        SUBCASE("Missing opening paren one param") {
            test::utils::test_failing_parsing(
                "fn x) { return 2; }",
                {token::type::LPAREN}
            );
        }
        SUBCASE("Missing opening paren two param") {
            test::utils::test_failing_parsing(
                "fn x, y) { return 2; }",
                {token::type::LPAREN}
            );
        }

        SUBCASE("Missing identifier with no closing paren - no param") {
            test::utils::test_failing_parsing(
                "fn ( { return 2; }",
                {token::type::IDENTIFIER}
            );
        }

        SUBCASE("Missing identifier with no closing paren - one param") {
            test::utils::test_failing_parsing(
                "fn (x, { return 2; }",
                {token::type::IDENTIFIER}
            );
        }
        SUBCASE("Missing identifier with no closing paren - two params") {
            test::utils::test_failing_parsing(
                "fn (x, y, { return 2; }",
                {token::type::IDENTIFIER}
            );
        }

        SUBCASE("Missing identifier with closing paren - one param") {
            test::utils::test_failing_parsing(
                "fn (x,) { return 2; }",
                {token::type::IDENTIFIER}
            );
        }
        SUBCASE("Missing identifier with closing paren - two params") {
            test::utils::test_failing_parsing(
                "fn (x,y,) { return 2; }",
                {token::type::IDENTIFIER}
            );
        }

        SUBCASE("Missing closing paren one param") {
            test::utils::test_failing_parsing(
                "fn (x { return 2; }",
                {token::type::RPAREN}
            );
        }
        SUBCASE("Missing closing paren two params") {
            test::utils::test_failing_parsing(
                "fn (x, y { return 2; }",
                {token::type::RPAREN}
            );
        }

        SUBCASE("Missing opening brace") {
            test::utils::test_failing_parsing(
                "fn (x, y)  return x + y; }",
                {token::type::LBRACE}
            );
        }

        SUBCASE("Missing closing brace") {
            test::utils::test_failing_parsing(
                "fn (x, y) { return x + y; ",
                {token::type::RBRACE}
            );
        }
    }

    TEST_CASE_FIXTURE(
        test::utils::ParserFixture,
        "Parse well formed function literal"
    ) {
        SUBCASE("no param function") {
            setup("\
fn () {\
    return true;\
}\
");
            REQUIRE(program->statements.size() == 1);
            CHECK(program->statements[0]->token_literal() == "fn");

            ast::expression_stmt* expr_stmt =
                test::utils::cast<ast::expression_stmt>(program->statements[0]);

            ast::function_literal* fun =
                test::utils::cast<ast::function_literal>(expr_stmt->expression);

            // parameters
            CHECK(fun->parameters.size() == 0);

            // block
            REQUIRE(fun->body->statements.size() == 1);
            ast::return_stmt* ret =
                test::utils::cast<ast::return_stmt>(fun->body->statements[0]);
            test::utils::test_boolean_literal(ret->value, true);

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
                test::utils::cast<ast::expression_stmt>(program->statements[0]);

            ast::function_literal* fun =
                test::utils::cast<ast::function_literal>(expr_stmt->expression);

            // parameters
            REQUIRE(fun->parameters.size() == 1);
            test::utils::test_identifier(fun->parameters[0], "x");

            // block
            REQUIRE(fun->body->statements.size() == 1);
            ast::return_stmt* ret =
                test::utils::cast<ast::return_stmt>(fun->body->statements[0]);
            test::utils::test_infix_expression(ret->value, "x", "+", 1);

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
                test::utils::cast<ast::expression_stmt>(program->statements[0]);

            ast::function_literal* fun =
                test::utils::cast<ast::function_literal>(expr_stmt->expression);

            // parameters
            REQUIRE(fun->parameters.size() == 2);
            test::utils::test_identifier(fun->parameters[0], "x");
            test::utils::test_identifier(fun->parameters[1], "y");

            // block
            REQUIRE(fun->body->statements.size() == 1);
            ast::return_stmt* ret =
                test::utils::cast<ast::return_stmt>(fun->body->statements[0]);
            test::utils::test_infix_expression(ret->value, "x", "+", "y");

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
                test::utils::cast<ast::let_stmt>(program->statements[0]);

            // let lhs
            test::utils::test_identifier(let_stmt->name, "fun");

            // let rhs
            CHECK(let_stmt->value->token_literal() == "fn");
            ast::function_literal* fun =
                test::utils::cast<ast::function_literal>(let_stmt->value);

            // parameters
            REQUIRE(fun->parameters.size() == 2);
            test::utils::test_identifier(fun->parameters[0], "x");
            test::utils::test_identifier(fun->parameters[1], "y");

            // block
            REQUIRE(fun->body->statements.size() == 1);
            ast::return_stmt* ret =
                test::utils::cast<ast::return_stmt>(fun->body->statements[0]);
            test::utils::test_infix_expression(ret->value, "x", "+", "y");

            // full string
            CHECK(fun->str() == "fn (x, y){return (x + y);}");
        }
    }
}

TEST_SUITE("Parser: function call") {
    TEST_CASE("Malformed function call (checking for memory leaks)") {
        SUBCASE("missing closing no param function") {
            std::stringstream input("value(;");

            lexer::lexer l{input};
            parser::parser p{l};

            std::unique_ptr<ast::program> program = p.parse_program();
            INFO(*program);

            // Check for errors
            REQUIRE(p.errors.size() == 2);
            ast::error::unkown_prefix* up =
                test::utils::cast<ast::error::unkown_prefix>(p.errors[0]);
            REQUIRE(up->prefix.type == token::type::SEMICOLON);
            ast::error::expected_next* en =
                test::utils::cast<ast::error::expected_next>(p.errors[1]);
            REQUIRE(en->expected_type == token::type::RPAREN);


            // normal program check
            REQUIRE_MESSAGE(
                program != nullptr,
                "parse_program() returned a null pointer"
            );
        }
        SUBCASE("missing closing 1 param function") {
            test::utils::test_failing_parsing(
                "value(x;",
                {token::type::RPAREN}
            );
        }

        SUBCASE("missing closing 2 param function") {
            test::utils::test_failing_parsing(
                "value(x, y;",
                {token::type::RPAREN}
            );
        }

        SUBCASE("missing comma between 2 param function") {
            test::utils::test_failing_parsing(
                "value(x y);",
                {token::type::RPAREN}
            );
        }
    }

    TEST_CASE_FIXTURE(
        test::utils::ParserFixture,
        "Parse well formed function call"
    ) {
        SUBCASE("no param function") {
            setup("value();");
            REQUIRE(program->statements.size() == 1);

            ast::expression_stmt* expr_stmt =
                test::utils::cast<ast::expression_stmt>(program->statements[0]);

            ast::function_call* fun =
                test::utils::cast<ast::function_call>(expr_stmt->expression);

            // target
            test::utils::test_identifier(fun->target, "value");

            // parameters
            CHECK(fun->parameters.size() == 0);

            // full string
            CHECK(fun->str() == "value()");
        }

        SUBCASE("one param identifier function") {
            setup("is_odd(1);");
            REQUIRE(program->statements.size() == 1);

            ast::expression_stmt* expr_stmt =
                test::utils::cast<ast::expression_stmt>(program->statements[0]);

            ast::function_call* fun =
                test::utils::cast<ast::function_call>(expr_stmt->expression);

            // target
            test::utils::test_identifier(fun->target, "is_odd");

            // parameters
            CHECK(fun->parameters.size() == 1);
            test::utils::test_integer_literal(fun->parameters[0], 1);

            // full string
            CHECK(fun->str() == "is_odd(1)");
        }

        SUBCASE("two param function") {
            setup("is_gt(1, a + 10);");
            REQUIRE(program->statements.size() == 1);

            ast::expression_stmt* expr_stmt =
                test::utils::cast<ast::expression_stmt>(program->statements[0]);

            ast::function_call* fun =
                test::utils::cast<ast::function_call>(expr_stmt->expression);

            // target
            test::utils::test_identifier(fun->target, "is_gt");

            // parameters
            CHECK(fun->parameters.size() == 2);
            test::utils::test_integer_literal(fun->parameters[0], 1);
            test::utils::test_infix_expression(
                fun->parameters[1],
                "a",
                "+",
                10
            );

            // full string
            CHECK(fun->str() == "is_gt(1, (a + 10))");
        }

        SUBCASE("two param identifier function assigned to variable") {
            setup("let res = add(1, a + 10, 2 * 3);");
            REQUIRE(program->statements.size() == 1);

            ast::let_stmt* let_stmt =
                test::utils::cast<ast::let_stmt>(program->statements[0]);

            test::utils::test_identifier(let_stmt->name, "res");

            ast::function_call* fun =
                test::utils::cast<ast::function_call>(let_stmt->value);

            // target
            test::utils::test_identifier(fun->target, "add");

            // parameters
            CHECK(fun->parameters.size() == 3);
            test::utils::test_integer_literal(fun->parameters[0], 1);
            test::utils::test_infix_expression(
                fun->parameters[1],
                "a",
                "+",
                10
            );
            test::utils::test_infix_expression(fun->parameters[2], 2, "*", 3);

            // full string
            CHECK(fun->str() == "add(1, (a + 10), (2 * 3))");
            CHECK(let_stmt->str() == "let res = add(1, (a + 10), (2 * 3));");
        }
    }
}
