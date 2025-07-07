#include "parser/parser.hpp"

#include "ast/ast.hpp"
#include "ast/statements/let.hpp"
#include "lexer/lexer.hpp"

#include <doctest.h>
#include <iostream>
#include <sstream>

void test_let_statement(ast::statement* stmt, const std::string name) {
    REQUIRE(stmt->token_literal() == "let");
    ast::let* let_stmt;
    REQUIRE_NOTHROW(let_stmt = dynamic_cast<ast::let*>(stmt));
    REQUIRE_MESSAGE(
        let_stmt != nullptr,
        "Couldn't cast statement to a let statement"
    );

    REQUIRE(let_stmt->name->value == name);
    REQUIRE(let_stmt->name->token_literal() == name);
}

void checkParserErrors(const std::vector<std::string>& errors) {
    if (errors.empty())
        return;

    std::cerr << "parser has " << errors.size() << " errors:\n";
    for (const auto& msg : errors)
        std::cerr << "parser error: \"" << msg << "\"\n";

    // Use doctest's FAIL macro to immediately stop
    FAIL_CHECK("Parser had errors. See stderr for details.");
}

TEST_CASE("Malformed let statement (checking for memory leaks)") {
    SUBCASE("Second token not identifier") {
        std::stringstream input("\
let 5 = 5;\
");

        lexer::lexer l{input};
        parser::parser p{l};

        ast::program* program = p.parse_program();
        REQUIRE_MESSAGE(
            program != nullptr,
            "parse_program() returned a null pointer"
        );
        REQUIRE(program->statements.size() == 0);
        delete program;
    }

    SUBCASE("Third token not '='") {
        std::stringstream input("\
let five ! 5;\
");

        lexer::lexer l{input};
        parser::parser p{l};

        ast::program* program = p.parse_program();
        REQUIRE_MESSAGE(
            program != nullptr,
            "parse_program() returned a null pointer"
        );
        REQUIRE(program->statements.size() == 0);
        delete program;
    }
}

TEST_CASE("Parse let statement") {
    std::stringstream input("\
let x = 5;\
let y = 10;\
let foobar = 103213;\
");

    lexer::lexer l{input};
    parser::parser p{l};

    ast::program* program = p.parse_program();

    REQUIRE_MESSAGE(
        program != nullptr,
        "parse_program() returned a null pointer"
    );
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

    delete program;
}
