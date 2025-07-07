#pragma once

#include "ast/ast.hpp"
#include "ast/errors/error.hpp"
#include "ast/statements/let.hpp"
#include "ast/statements/return.hpp"
#include "lexer/lexer.hpp"
#include "token/token.hpp"

namespace parser {
    struct parser {
        parser(lexer::lexer& lexer);
        ~parser();
        std::vector<ast::error::error*> errors;

        ast::program* parse_program();

      private:
        lexer::lexer& lexer;
        token::token current, next;

        void next_token();
        ast::statement* parse_statement();
        ast::let_stmt* parse_let();
        ast::return_stmt* parse_return();
        bool expect_next(token::type);
        void next_error(token::type);
    };
} // namespace parser
