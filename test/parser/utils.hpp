#include "ast/errors/error.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

#include <doctest.h>
#include <sstream>
#include <vector>

void check_parser_errors(const std::vector<ast::error::error*>& errors);

struct ParserFixture {
    std::stringstream input;
    lexer::lexer* l = nullptr;
    parser::parser* p = nullptr;

    ParserFixture() = default;

    void setup(std::string source) {
        input << source;
        l = new lexer::lexer{input};
        p = new parser::parser(*l);
    }

    ~ParserFixture() {
        delete l;
        delete p;
    }
};
