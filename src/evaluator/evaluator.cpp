
#include "evaluator.hpp"

#include "ast/ast.hpp"
#include "ast/expressions/boolean.hpp"
#include "ast/expressions/integer.hpp"
#include "ast/program.hpp"
#include "ast/statements/expression.hpp"
#include "object/boolean.hpp"
#include "object/integers.hpp"
#include "object/null.hpp"

#include <vector>

namespace eval {
    static object::null* null = new object::null;

    object::object* eval(std::vector<ast::statement*> statements) {
        object::object* ret;
        for (auto& stmt : statements)
            ret = eval(stmt);
        return ret;
    }

    object::object* eval(ast::node* node) {
        if (ast::integer_literal* integer =
                dynamic_cast<ast::integer_literal*>(node)) {
            return new object::integer(integer->value);
        } else if (ast::boolean_literal* boolean =
                       dynamic_cast<ast::boolean_literal*>(node)) {
            return new object::boolean(boolean->value);
        } else if (ast::program* program = dynamic_cast<ast::program*>(node)) {
            return eval(program->statements);
        } else if (ast::expression_stmt* expression_stmt =
                       dynamic_cast<ast::expression_stmt*>(node)) {
            return eval(expression_stmt->expression);
        }
        return null;
    }

} // namespace eval
