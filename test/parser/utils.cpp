#include "utils.hpp"

#include <doctest.h>

void check_parser_errors(const std::vector<ast::error::error*>& errors) {
    if (errors.empty())
        return;

    INFO("parser has " << errors.size() << " errors:");
    std::ostringstream combined;
    for (auto& err : errors)
        combined << "  > " << err->what() << '\n';

    INFO(combined.str());

    FAIL("Parser had errors.");
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
