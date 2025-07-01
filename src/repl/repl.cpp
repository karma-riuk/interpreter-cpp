#include "repl.hpp"

#include "lexer/lexer.hpp"

#include <sstream>
#include <string>

static const std::string PROMPT = ">> ";

namespace repl {

    void start(std::istream& in, std::ostream& out) {
        while (true) {
            out << PROMPT;
            std::string line;
            if (!std::getline(in, line))
                return;

            std::istringstream ss(line);

            lexer::lexer l{ss};
            for (token::token tok = l.next_token();
                 tok.type != token::type::END_OF_FILE;
                 tok = l.next_token())
                out << tok << " ";
            out << std::endl;
        }
    }

} // namespace repl
