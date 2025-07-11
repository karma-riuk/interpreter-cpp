#include "token/type.hpp"

#include <ostream>

namespace parser {
    enum class precedence {
        LOWEST,
        EQUALS,
        LESS_GREATER,
        SUM,
        PRODUCT,
        PREFIX,
        CALL
    };

    precedence precedence_for(token::type);

    inline std::ostream& operator<<(std::ostream& os, precedence& p) {
        return os << static_cast<int>(p);
    }
} // namespace parser
