#include "utils.hpp"

#include "ast/expressions/boolean.hpp"
#include "ast/expressions/identifier.hpp"
#include "ast/expressions/infix.hpp"
#include "ast/expressions/integer.hpp"

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
    input.clear();
    input << source;
    lexer = std::make_unique<lexer::lexer>(input);
    parser = std::make_unique<parser::parser>(*lexer);
    program = parser->parse_program();
    check_parser_errors(parser->errors);

    CAPTURE(parser);
    CAPTURE(program);
    REQUIRE_MESSAGE(
        program != nullptr,
        "parse_program() returned a null pointer"
    );
}

void test_identifier(ast::expression* expr, std::string value) {
    ast::identifier* ident = cast<ast::identifier>(expr);

    REQUIRE(ident->value == value);
    REQUIRE(ident->token_literal() == value);
}

void test_integer_literal(ast::expression* expr, int value) {
    ast::integer_literal* int_lit = cast<ast::integer_literal>(expr);

    REQUIRE(int_lit->value == value);
    std::ostringstream oss;
    oss << value;
    REQUIRE(int_lit->token_literal() == oss.str());
}

void test_boolean_literal(ast::expression* expr, bool value) {
    ast::boolean_literal* bool_lit = cast<ast::boolean_literal>(expr);

    REQUIRE(bool_lit->value == value);
    std::ostringstream oss;
    oss << value;
    REQUIRE(bool_lit->token_literal() == oss.str());
}

void test_literal_expression(ast::expression* exp, std::any& expected) {
    if (expected.type() == typeid(int))
        return test_integer_literal(exp, std::any_cast<int>(expected));
    if (expected.type() == typeid(bool))
        return test_boolean_literal(exp, std::any_cast<bool>(expected));
    if (expected.type() == typeid(std::string))
        return test_identifier(exp, std::any_cast<std::string>(expected));
    if (expected.type() == typeid(const char*))
        return test_identifier(exp, std::any_cast<const char*>(expected));

    FAIL(
        "Type of exp not handled. Got: " * demangle(typeid(*exp).name())
        * " as expression and " * demangle(expected.type().name())
        * " as expected"
    );
}

void test_infix_expression(
    ast::expression* exp, std::any left, std::string op, std::any right
) {
    ast::infix_expr* op_exp = cast<ast::infix_expr>(exp);
    test_literal_expression(op_exp->left, left);
    CHECK(op_exp->op == op);
    test_literal_expression(op_exp->right, right);
}
