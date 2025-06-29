#include "token/token.hpp"

#include <istream>

namespace lexer {
    struct lexer {
        std::istream& input;
        token::token next_token();

      private:
        bool is_letter(char);

        std::string read_string(char);
        std::string read_int(char);
    };
} // namespace lexer
