#include "utils.hpp"

#include <doctest.h>

TEST_SUITE("Parser: return") {
    TEST_CASE_FIXTURE(ParserFixture, "Parse return statement") {
        setup("\
return 5;\
return 10;\
return 103213;\
return 12 + 34;\
");

        REQUIRE(program->statements.size() == 4);

        for (const auto stmt : program->statements) {
            CHECK(stmt->token_literal() == "return");
            cast<ast::return_stmt>(stmt);
        }
    }
}
