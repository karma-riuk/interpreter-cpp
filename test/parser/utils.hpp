#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

#include <sstream>

void check_parser_errors(const std::vector<ast::error::error*>& errors);

struct ParserFixture {
    std::stringstream input;
    lexer::lexer* lexer = nullptr;
    parser::parser* parser = nullptr;
    ast::program* program = nullptr;

    ParserFixture() = default;

    void setup(std::string);

    ~ParserFixture();
};
