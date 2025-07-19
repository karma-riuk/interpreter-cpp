#include "utils.hpp"

namespace test::utils {

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
        oss << (value ? "true" : "false");
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

    void test_failing_parsing(
        std::string input_s,
        std::vector<token::type> expected_types,
        int n_good_statements
    ) {
        std::stringstream input(input_s);

        lexer::lexer l{input};
        parser::parser p{l};

        std::unique_ptr<ast::program> program = p.parse_program();
        INFO(*program);

        // Check for errors
        REQUIRE(p.errors.size() >= expected_types.size());
        //                      ^^ because even though you were thinking
        // about a specific token to be there, other `expect_next -> false`
        // might be triggered for subexpressions due to the first one

        int i = 0;
        for (auto& t : expected_types) {
            ast::error::expected_next* en =
                cast<ast::error::expected_next>(p.errors[i++]);

            REQUIRE(en->expected_type == t);
        }

        // normal program check
        REQUIRE_MESSAGE(
            program != nullptr,
            "parse_program() returned a null pointer"
        );
        REQUIRE(program->statements.size() >= n_good_statements);
        //                                 ^^ because even though you were
        // thinking about a specific number of statements to be there, it
        // failing for `expect_next` might trigger a sub-expression to be
        // triggered correctly and be parsed as the expression_stmt
    }
} // namespace test::utils
