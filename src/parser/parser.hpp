#pragma once

#include "ast/ast.hpp"
#include "ast/errors/error.hpp"
#include "ast/program.hpp"
#include "ast/statements/expression.hpp"
#include "ast/statements/let.hpp"
#include "ast/statements/return.hpp"
#include "lexer/lexer.hpp"
#include "precedence.hpp"
#include "token/token.hpp"

#include <functional>
#include <memory>
#include <vector>

namespace parser {

    using prefix_parse_fn = std::function<ast::expression*()>;
    using infix_parse_fn = std::function<ast::expression*(ast::expression*)>;

    struct parser {
        parser(lexer::lexer&);
        ~parser();
        std::vector<ast::error::error*> errors;

        std::unique_ptr<ast::program> parse_program();

      private:
        lexer::lexer& lexer;
        token::token current, next;

        std::unordered_map<token::type, prefix_parse_fn> prefix_parse_fns;
        std::unordered_map<token::type, infix_parse_fn> infix_parse_fns;

        void next_token();
        void skip_until_semicolon();
        ast::statement* parse_statement();
        ast::expression* parse_expression(precedence = precedence::LOWEST);
        ast::let_stmt* parse_let();
        ast::return_stmt* parse_return();
        ast::expression_stmt* parse_expression_stmt();
        bool expect_next(token::type);
        void next_error(token::type);
        void unkown_prefix_error(token::token);

        void register_prefix(token::type, prefix_parse_fn);
        void register_prefix(std::vector<token::type>, prefix_parse_fn);
        void register_infix(token::type, infix_parse_fn);
        void register_infix(std::vector<token::type>, infix_parse_fn);

        ast::expression* parse_identifier();
        ast::expression* parse_integer();
        ast::expression* parse_boolean();
        ast::expression* parse_prefix_expr();

        ast::expression* parse_infix_expr(ast::expression*);
    };
} // namespace parser
