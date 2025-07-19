#pragma once

#include "ast/ast.hpp"
#include "lexer/lexer.hpp"
#include "object/object.hpp"
#include "parser/parser.hpp"

#include <any>
#include <cxxabi.h>
#include <doctest.h>
#include <memory>
#include <sstream>

namespace test::utils {
    void check_parser_errors(const std::vector<ast::error::error*>&);

    struct ParserFixture {
        std::stringstream input;
        std::unique_ptr<lexer::lexer> lexer;
        std::unique_ptr<parser::parser> parser;
        std::unique_ptr<ast::program> program;

        ParserFixture() = default;

        virtual void setup(std::string);
    };

    struct EvalFixture : ParserFixture {
        std::unique_ptr<object::object> result;
        void setup(std::string);
    };

    // parser tests
    void test_identifier(ast::expression*, std::string);
    void test_integer_literal(ast::expression*, int);
    void test_boolean_literal(ast::expression*, bool);
    void test_literal_expression(ast::expression*, std::any&);
    void
    test_infix_expression(ast::expression*, std::any, std::string, std::any);
    void test_failing_parsing(std::string, std::vector<token::type>, int = 0);

    // eval tests
    void test_integer_object(object::object*, int);

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
                "Couldn't cast " * demangle(typeid(*base).name())
                    * " (given as " * demangle(typeid(Base).name()) * ")"
                    * " to a " * demangle(typeid(T).name())
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

    template <typename T>
    T* cast(object::object* err) {
        return cast_impl<T, object::object>(err);
    }

} // namespace test::utils
