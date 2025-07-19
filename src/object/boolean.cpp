#include "boolean.hpp"

#include <string>

namespace object {
    std::string boolean::inspect() {
        return std::to_string(value);
    }
} // namespace object
