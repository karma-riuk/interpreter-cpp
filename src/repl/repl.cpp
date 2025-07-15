#include "repl.hpp"

#include "ast/program.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

#include <memory>
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
            parser::parser p{l};
            std::unique_ptr<ast::program> program = p.parse_program();
            if (!p.errors.empty()) {
                for (auto& e : p.errors)
                    out << e->what() << std::endl;
                continue;
            }
            out << program->str() << std::endl;
        }
    }

} // namespace repl
