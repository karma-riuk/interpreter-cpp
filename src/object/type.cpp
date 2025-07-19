#include "type.hpp"

#include <array>

namespace object {

    // Array mapping enum values to their string representations
    constexpr std::
        array<std::string_view, static_cast<size_t>(type::BOOLEAN_OBJ) + 1>
            tokenTypeStrings = {
#define X(name, str) str,
                OBJECT_LIST
#undef X
    };

    // Stream insertion operator using the lookup array
    std::ostream& operator<<(std::ostream& os, type type) {
        auto idx = static_cast<size_t>(type);
        if (idx < tokenTypeStrings.size())
            return os << tokenTypeStrings[idx];
        return os << "Unknown";
    }
} // namespace object
