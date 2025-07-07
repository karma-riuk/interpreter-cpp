#include "ast/ast.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "utils.hpp"

#include <doctest.h>
#include <sstream>

TEST_CASE("Parse return statement") {
    std::stringstream input("\
return 5;\
return 10;\
return 103213;\
");

    lexer::lexer l{input};
    parser::parser p{l};

    ast::program* program = p.parse_program();
    check_parser_errors(p.errors);

    REQUIRE_MESSAGE(
        program != nullptr,
        "parse_program() returned a null pointer"
    );
    REQUIRE(program->statements.size() == 3);

    for (const auto stmt : program->statements) {
        REQUIRE(stmt->token_literal() == "return");
        ast::let* let_stmt;
        REQUIRE_NOTHROW(let_stmt = dynamic_cast<ast::let*>(stmt));
        REQUIRE_MESSAGE(
            let_stmt != nullptr,
            "Couldn't cast statement to a return statement"
        );
    }

    delete program;
}
