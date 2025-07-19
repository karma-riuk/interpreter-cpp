#pragma once

#include <ostream>

namespace object {

// X-macro list of token types and their string representations
#define OBJECT_LIST                                                            \
    X(NULL_OBJ, "NULL")                                                        \
    X(INTEGER_OBJ, "INTEGER")                                                  \
    X(BOOLEAN_OBJ, "BOOLEAN")

    // Define the TokenType enum using the X-macro
    enum class type {
#define X(name, str) name,
        OBJECT_LIST
#undef X
    };

    std::ostream& operator<<(std::ostream&, type);
} // namespace object
