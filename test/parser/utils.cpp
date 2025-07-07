#include "utils.hpp"

#include <iostream>

void check_parser_errors(const std::vector<ast::error::error*>& errors) {
    if (errors.empty())
        return;

    std::cerr << "parser has " << errors.size() << " errors:\n";
    for (const auto& error : errors)
        std::cerr << '\t' << error->what() << "\n";

    // Use doctest's FAIL macro to immediately stop
    FAIL_CHECK("Parser had errors. See stderr for details.");
}
