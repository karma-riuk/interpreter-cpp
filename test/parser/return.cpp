#include "utils.hpp"

#include <doctest.h>

TEST_SUITE("Parser: return") {
    TEST_CASE_FIXTURE(ParserFixture, "Parse return statement") {
        setup("\
return 5;\
return 10;\
return 103213;\
");

        REQUIRE(program->statements.size() == 3);

        for (const auto stmt : program->statements) {
            REQUIRE(stmt->token_literal() == "return");
            ast::return_stmt* let_stmt;
            REQUIRE_NOTHROW(let_stmt = dynamic_cast<ast::return_stmt*>(stmt));
            REQUIRE_MESSAGE(
                let_stmt != nullptr,
                "Couldn't cast statement to a return statement"
            );
        }
    }
}
