#include "utils.hpp"

#include <doctest.h>

namespace test::utils {
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
        input.clear();
        input << source;
        lexer = std::make_unique<lexer::lexer>(input);
        parser = std::make_unique<parser::parser>(*lexer);
        program = parser->parse_program();
        check_parser_errors(parser->errors);

        REQUIRE_MESSAGE(
            program != nullptr,
            "parse_program() returned a null pointer"
        );
    }
} // namespace test::utils
