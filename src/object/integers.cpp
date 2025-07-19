#include "integers.hpp"

#include <string>

namespace object {
    std::string integer::inspect() {
        return std::to_string(value);
    }
} // namespace object
