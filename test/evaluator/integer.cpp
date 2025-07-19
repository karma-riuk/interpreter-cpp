#include "doctest.h"
#include "utils.hpp"

TEST_SUITE("Eval: integers") {
    TEST_CASE_FIXTURE(
        test::utils::EvalFixture,
        "Simple integer expression statements"
    ) {
        struct test_struct {
            std::string input;
            int expected;
        };
        struct test_struct tests[]{{"5", 5}, {"10", 10}};

        for (auto& t : tests) {
            setup(t.input);
            test::utils::test_integer_object(result.get(), t.expected);
        }
    }
}
