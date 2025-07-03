#pragma once

#include "ast/ast.hpp"
#include "ast/statements/let.hpp"
#include "lexer/lexer.hpp"
#include "token/token.hpp"

namespace parser {
    struct parser {
        parser(lexer::lexer& lexer);
        std::vector<std::string> errors;

        ast::program* parse_program();

      private:
        lexer::lexer& lexer;
        token::token current, next;

        void next_token();
        ast::statement* parse_statement();
        ast::let* parse_let();
        bool expect_next(token::type);
        void next_error(token::type);
    };
} // namespace parser
