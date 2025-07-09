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
            ast::return_stmt* return_stmt = cast<ast::return_stmt>(stmt);
        }
    }
}
