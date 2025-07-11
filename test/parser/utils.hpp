#include "ast/ast.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

#include <cxxabi.h>
#include <doctest.h>
#include <memory>
#include <sstream>

void check_parser_errors(const std::vector<ast::error::error*>&);

namespace {

    std::string demangle(const char* name) {
        int status = 0;
        std::unique_ptr<char, decltype(&std::free)> demangled(
            abi::__cxa_demangle(name, nullptr, nullptr, &status),
            &std::free
        );
        return (status == 0 && demangled) ? demangled.get() : name;
    }

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
            "Couldn't cast " * demangle(typeid(*base).name()) * " (given as "
                * demangle(typeid(Base).name()) * ")" * " to a "
                * demangle(typeid(T).name())
        );
        return t;
    }
} // namespace

// Overloads for your known base types
template <typename T>
T* cast(ast::node* stmt) {
    return cast_impl<T, ast::node>(stmt);
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
