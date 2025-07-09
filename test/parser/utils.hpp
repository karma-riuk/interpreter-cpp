#include "ast/ast.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

#include <doctest.h>
#include <sstream>

void check_parser_errors(const std::vector<ast::error::error*>&);

namespace {
    template <typename T, typename Base>
    T* cast_impl(Base* base) {
        static_assert(
            std::is_base_of_v<Base, T>,
            "T must be derived from Base"
        );

        T* t;
        REQUIRE_NOTHROW(t = dynamic_cast<T*>(base));
        REQUIRE_MESSAGE(
            t != nullptr,
            "Couldn't cast expression to a " * std::string(typeid(T).name())
        );
        return t;
    }
} // namespace

// Overloads for your known base types
template <typename T>
T* cast(ast::expression* expr) {
    return cast_impl<T, ast::expression>(expr);
}

template <typename T>
T* cast(ast::statement* stmt) {
    return cast_impl<T, ast::statement>(stmt);
}

template <typename T>
T* cast(ast::error::error* err) {
    return cast_impl<T, ast::error::error>(err);
}

struct ParserFixture {
    std::stringstream input;
    lexer::lexer* lexer = nullptr;
    parser::parser* parser = nullptr;
    ast::program* program = nullptr;

    ParserFixture() = default;

    void setup(std::string);

    ~ParserFixture();
};
