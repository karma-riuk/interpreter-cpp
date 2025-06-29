#include "token/token.hpp"

#include <istream>

namespace lexer {
    struct lexer {
        std::istream& input;
        token::token next_token();
    };
} // namespace lexer
