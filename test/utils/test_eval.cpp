#include "object/integers.hpp"
#include "object/object.hpp"
#include "utils.hpp"

namespace test::utils {
    void test_integer_object(object::object* obj, int expected) {
        object::integer* i = cast<object::integer>(obj);
        CHECK(i->value == expected);
    }
} // namespace test::utils
