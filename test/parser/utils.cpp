#include "utils.hpp"

#include <doctest.h>
#include <iostream>

void check_parser_errors(const std::vector<ast::error::error*>& errors) {
    if (errors.empty())
        return;

    std::cerr << "parser has " << errors.size() << " errors:\n";
    for (const auto& error : errors)
        std::cerr << '\t' << error->what() << "\n";

    FAIL_CHECK("Parser had errors. See stderr for details.");
}

void ParserFixture::setup(std::string source) {
    input << source;
    lexer = new lexer::lexer{input};
    parser = new parser::parser(*lexer);
    program = parser->parse_program();
    check_parser_errors(parser->errors);

    CAPTURE(parser);
    CAPTURE(program);
    REQUIRE_MESSAGE(
        program != nullptr,
        "parse_program() returned a null pointer"
    );
}

ParserFixture::~ParserFixture() {
    delete lexer;
    delete parser;
    delete program;
}
