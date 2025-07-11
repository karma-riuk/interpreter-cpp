#include "ast/statements/let.hpp"

#include "ast/ast.hpp"
#include "ast/errors/error.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "utils.hpp"

#include <doctest.h>
#include <memory>
#include <sstream>

void test_let_statement(ast::statement* stmt, const std::string name) {
    REQUIRE(stmt->token_literal() == "let");
    ast::let_stmt* let_stmt = cast<ast::let_stmt>(stmt);

    REQUIRE(let_stmt->name->value == name);
    REQUIRE(let_stmt->name->token_literal() == name);
}

void test_failing_let_parsing(
    std::string input_s,
    std::vector<token::type> expected_types,
    int n_good_statements = 0
) {
    std::stringstream input(input_s);

    lexer::lexer l{input};
    parser::parser p{l};

    std::unique_ptr<ast::program> program = p.parse_program();

    // Check for errors
    REQUIRE(p.errors.size() == expected_types.size());

    int i = 0;
    for (auto& e : p.errors) {
        ast::error::expected_next* en = cast<ast::error::expected_next>(e);

        REQUIRE(en->expected_type == expected_types[i++]);
    }

    // normal program check
    REQUIRE_MESSAGE(
        program != nullptr,
        "parse_program() returned a null pointer"
    );
    REQUIRE(program->statements.size() == n_good_statements);
}

TEST_SUITE("Parser: let") {
    TEST_CASE("Malformed let statement (checking for memory leaks)") {
        SUBCASE("Second token not identifier") {
            test_failing_let_parsing("let 5 = 5;", {token::type::IDENTIFIER});
        }

        SUBCASE("Third token not '='") {
            test_failing_let_parsing("let five ! 5;", {token::type::ASSIGN});
        }

        SUBCASE("Missing both identifier and '='") {
            test_failing_let_parsing("let 5;", {token::type::IDENTIFIER});
        }

        SUBCASE("Multiple parsing errors") {
            test_failing_let_parsing(
                "let 5; let ! = 5; let five = 5; let five 5; let;",
                {token::type::IDENTIFIER,
                 token::type::IDENTIFIER,
                 token::type::ASSIGN,
                 token::type::IDENTIFIER},
                1
            );
        }
    }

    TEST_CASE_FIXTURE(ParserFixture, "Parse well formed let statements") {
        setup("\
let x = 5;\
let y = 10;\
let foobar = 103213;\
");

        REQUIRE(program->statements.size() == 3);

        struct test {
            std::string expected_identifier;
        };

        test tests[]{
            "x",
            "y",
            "foobar",
        };

        int i = 0;
        for (const auto& t : tests) {
            ast::statement* stmt = program->statements[i++];

            test_let_statement(stmt, t.expected_identifier);
        }
    }
}
