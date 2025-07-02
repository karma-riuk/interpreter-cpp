#pragma once
#include "token/token.hpp"

#include <istream>

namespace lexer {
    struct lexer {
        std::istream& input;
        char c = 0;
        token::token next_token();

      private:
        bool is_letter(char);

        std::string read_string();
        std::string read_int();
    };
} // namespace lexer
