#include "ast/expressions/identifier.hpp"
#include "ast/expressions/infix.hpp"
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

        test_integer_literal(expression_stmt->expression, 5);
    };

    TEST_CASE_FIXTURE(
        ParserFixture,
        "Simple expression statement with prefix before integer"
    ) {
#define CASE(name, input, _op, _right)                                         \
    SUBCASE(name) {                                                            \
        setup(input);                                                          \
                                                                               \
        REQUIRE(program->statements.size() == 1);                              \
        ast::expression_stmt* expression_stmt =                                \
            cast<ast::expression_stmt>(program->statements[0]);                \
                                                                               \
        ast::prefix_expr* prefix_expr =                                        \
            cast<ast::prefix_expr>(expression_stmt->expression);               \
                                                                               \
        REQUIRE(prefix_expr->op == _op);                                       \
        test_integer_literal(prefix_expr->right, _right);                      \
    }

        CASE("Prefix: '!'", "!5;", "!", 5);
        CASE("Prefix: '-'", "-15;", "-", 15);
#undef CASE
    }

    TEST_CASE_FIXTURE(
        ParserFixture,
        "Simple expression statement with infix between integers"
    ) {
#define CASE(name, input, _left, _op, _right)                                  \
    SUBCASE(name) {                                                            \
        setup(input);                                                          \
        REQUIRE(program->statements.size() == 1);                              \
                                                                               \
        ast::expression_stmt* expression_stmt =                                \
            cast<ast::expression_stmt>(program->statements[0]);                \
                                                                               \
        test_infix_expression(                                                 \
            expression_stmt->expression,                                       \
            _left,                                                             \
            _op,                                                               \
            _right                                                             \
        );                                                                     \
    }
        CASE("Infix: '+'", "5 + 5;", 5, "+", 5);
        CASE("Infix: '-'", "5- 5;", 5, "-", 5);
        CASE("Infix: '*'", "15 *5;", 15, "*", 5);
        CASE("Infix: '/'", "15 / 5;", 15, "/", 5);
        CASE("Infix: '<'", "15 < 15;", 15, "<", 15);
        CASE("Infix: '>'", "25 > 15;", 25, ">", 15);
        CASE("Infix: '=='", "5 == 5;", 5, "==", 5);
        CASE("Infix: '!='", "15 != 5;", 15, "!=", 5);
        CASE("Infix: between identifiers", "alice * bob;", "alice", "*", "bob");
#undef CASE
    }


    TEST_CASE_FIXTURE(ParserFixture, "Slightly more complex infix expression") {
        setup("5 - -15;");

        REQUIRE(program->statements.size() == 1);
        ast::expression_stmt* expression_stmt =
            cast<ast::expression_stmt>(program->statements[0]);

        ast::infix_expr* infix_expr =
            cast<ast::infix_expr>(expression_stmt->expression);

        test_integer_literal(infix_expr->left, 5);
        CHECK(infix_expr->op == "-");

        ast::prefix_expr* prefix_expr =
            cast<ast::prefix_expr>(infix_expr->right);

        CHECK(prefix_expr->op == "-");
        test_integer_literal(prefix_expr->right, 15);
    }

    TEST_CASE_FIXTURE(
        ParserFixture,
        "Slightly even more complex infix expression"
    ) {
        setup("5 - -15 * 3;");

        REQUIRE(program->statements.size() == 1);
        ast::expression_stmt* expression_stmt =
            cast<ast::expression_stmt>(program->statements[0]);

        ast::infix_expr* infix_expr =
            cast<ast::infix_expr>(expression_stmt->expression);

        test_integer_literal(infix_expr->left, 5);
        CHECK(infix_expr->op == "-");

        ast::infix_expr* second_infix_expr =
            cast<ast::infix_expr>(infix_expr->right);
        CHECK(second_infix_expr->op == "*");

        ast::prefix_expr* prefix_expr =
            cast<ast::prefix_expr>(second_infix_expr->left);

        CHECK(prefix_expr->op == "-");
        test_integer_literal(prefix_expr->right, 15);

        test_integer_literal(second_infix_expr->right, 3);
    }

    TEST_CASE_FIXTURE(
        ParserFixture,
        "Checking operator precedence with simple example"
    ) {
        setup("5 * -15 - 3;");

        REQUIRE(program->statements.size() == 1);
        ast::expression_stmt* expression_stmt =
            cast<ast::expression_stmt>(program->statements[0]);

        ast::infix_expr* infix_expr =
            cast<ast::infix_expr>(expression_stmt->expression);


        ast::infix_expr* second_infix_expr =
            cast<ast::infix_expr>(infix_expr->left);
        CHECK(second_infix_expr->op == "*");
        test_integer_literal(second_infix_expr->left, 5);

        ast::prefix_expr* prefix_expr =
            cast<ast::prefix_expr>(second_infix_expr->right);

        CHECK(prefix_expr->op == "-");
        test_integer_literal(prefix_expr->right, 15);

        CHECK(infix_expr->op == "-");
        test_integer_literal(infix_expr->right, 3);
    }

    TEST_CASE_FIXTURE(ParserFixture, "Full Operator Precedence test") {
        struct test {
            std::string input;
            std::string expected;
        };

        struct test tests[]{
            {"-a * b", "((-a) * b)"},
            {"!-a", "(!(-a))"},
            {"a + b + c", "((a + b) + c)"},
            {"a + b - c", "((a + b) - c)"},
            {"a * b * c", "((a * b) * c)"},
            {"a * b / c", "((a * b) / c)"},
            {"a + b / c", "(a + (b / c))"},
            {"a + b * c + d / e - f", "(((a + (b * c)) + (d / e)) - f)"},
            {"3 + 4; -5 * 5", "(3 + 4)((-5) * 5)"},
            {"5 > 4 == 3 < 4", "((5 > 4) == (3 < 4))"},
            {"5 < 4 != 3 > 4", "((5 < 4) != (3 > 4))"},
            {"3 + 4 * 5 == 3 * 1 + 4 * 5",
             "((3 + (4 * 5)) == ((3 * 1) + (4 * 5)))"},
        };

        for (auto& t : tests) {
            setup(t.input);
            CHECK(program->str() == t.expected);
        }
    }

    TEST_CASE_FIXTURE(ParserFixture, "Test to see trace") {
        setup("-1 * 2 - 3");
        CHECK(program->str() == "(((-1) * 2) - 3)");
        setup("-1 - 2 * 3");
        CHECK(program->str() == "((-1) - (2 * 3))");
    }
}
