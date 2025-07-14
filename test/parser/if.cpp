#include "ast/expressions/if_then_else.hpp"
#include "ast/expressions/infix.hpp"
#include "ast/statements/block.hpp"
#include "ast/statements/expression.hpp"
#include "utils.hpp"

#include <doctest.h>

TEST_SUITE("Parser: if") {
    TEST_CASE("Malformed if then else (checking for memory leaks)") {
        SUBCASE("Missing open paren") {
            test_failing_parsing(
                "if x > 15) {\
                    return x;\
                }",
                {token::type::LPAREN}
            );
        }

        SUBCASE("Missing closing paren") {
            test_failing_parsing(
                "if (x > 15 {\
                    return x;\
                }",
                {token::type::RPAREN}
            );
        }

        SUBCASE("Missing opening brace") {
            test_failing_parsing(
                "if (x > 15) \
                    return x;\
                }",
                {token::type::LBRACE}
            );
        }

        SUBCASE("Missing closing brace") {
            test_failing_parsing(
                "if (x > 15) { \
                    return x;\
                ",
                {token::type::RBRACE}
            );
        }
    }

    TEST_CASE_FIXTURE(ParserFixture, "Parse well formed simple if ") {
        setup("\
if (x > 15) {\
    return x;\
}\
");
        REQUIRE(program->statements.size() == 1);
        CHECK(program->statements[0]->token_literal() == "if");

        ast::expression_stmt* expr_stmt =
            cast<ast::expression_stmt>(program->statements[0]);

        ast::if_then_else* if_stmt =
            cast<ast::if_then_else>(expr_stmt->expression);

        // condition
        ast::infix_expr* cond = cast<ast::infix_expr>(if_stmt->condition);
        test_infix_expression(cond, "x", ">", 15);
        CHECK(if_stmt->condition->str() == "(x > 15)");

        // consequence
        REQUIRE(if_stmt->consequence->statements.size() == 1);
        ast::return_stmt* ret_stmt =
            cast<ast::return_stmt>(if_stmt->consequence->statements[0]);
        test_identifier(ret_stmt->value, "x");
        CHECK(if_stmt->consequence->str() == "{return x;}");

        // alternative
        CHECK(if_stmt->alternative == nullptr);

        // full string
        CHECK(if_stmt->str() == "if (x > 15){return x;}");
    }

    TEST_CASE_FIXTURE(ParserFixture, "Parse well formed if then else") {
        setup("\
if (x < 5) {\
    return 15;\
} else {\
    let b = 1;\
    return x;\
}\
");
        REQUIRE(program->statements.size() == 1);
        CHECK(program->statements[0]->token_literal() == "if");

        ast::expression_stmt* expr_stmt =
            cast<ast::expression_stmt>(program->statements[0]);

        ast::if_then_else* if_stmt =
            cast<ast::if_then_else>(expr_stmt->expression);

        // condition
        ast::infix_expr* cond = cast<ast::infix_expr>(if_stmt->condition);
        test_infix_expression(cond, "x", "<", 5);
        CHECK(if_stmt->condition->str() == "(x < 5)");

        // consequence
        REQUIRE(if_stmt->consequence->statements.size() == 1);
        ast::return_stmt* ret_stmt =
            cast<ast::return_stmt>(if_stmt->consequence->statements[0]);
        test_integer_literal(ret_stmt->value, 15);
        CHECK(if_stmt->consequence->str() == "{return 15;}");

        // alternative
        REQUIRE(if_stmt->alternative != nullptr);
        REQUIRE(if_stmt->alternative->statements.size() == 2);
        ast::let_stmt* let_stmt =
            cast<ast::let_stmt>(if_stmt->alternative->statements[0]);
        test_identifier(let_stmt->name, "b");
        test_integer_literal(let_stmt->value, 1);

        ast::return_stmt* ret_stmt2 =
            cast<ast::return_stmt>(if_stmt->alternative->statements[1]);
        test_identifier(ret_stmt2->value, "x");
        CHECK(if_stmt->alternative->str() == "{let b = 1;return x;}");

        // full string
        CHECK(
            if_stmt->str() == "if (x < 5){return 15;}else{let b = 1;return x;}"
        );
    }
}
