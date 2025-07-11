#include "ast/expressions/identifier.hpp"
#include "ast/expressions/infix.hpp"
#include "ast/expressions/integer.hpp"
#include "ast/expressions/prefix.hpp"
#include "utils.hpp"

#include <doctest.h>
#include <sstream>

void test_integer_literal(ast::expression* expr, int value) {
    ast::integer_literal* int_lit = cast<ast::integer_literal>(expr);

    REQUIRE(int_lit->value == value);
    std::ostringstream oss;
    oss << value;
    REQUIRE(int_lit->token_literal() == oss.str());
}

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
        ast::expression_stmt* expression_stmt =                                \
            cast<ast::expression_stmt>(program->statements[0]);                \
                                                                               \
        ast::infix_expr* infix_expr =                                          \
            cast<ast::infix_expr>(expression_stmt->expression);                \
                                                                               \
        test_integer_literal(infix_expr->left, _left);                         \
        REQUIRE(infix_expr->op == _op);                                        \
        test_integer_literal(infix_expr->right, _right);                       \
    }
        CASE("Infix: '+'", "5 + 5;", 5, "+", 5);
        CASE("Infix: '-'", "5- 5;", 5, "-", 5);
        CASE("Infix: '*'", "15 *5;", 15, "*", 5);
        CASE("Infix: '/'", "15 / 5;", 15, "/", 5);
        CASE("Infix: '<'", "15 < 15;", 15, "<", 15);
        CASE("Infix: '>'", "25 > 15;", 25, ">", 15);
        CASE("Infix: '=='", "5 == 5;", 5, "==", 5);
        CASE("Infix: '!='", "15 != 5;", 15, "!=", 5);
#undef CASE
    }
}
