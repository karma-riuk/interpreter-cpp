#include "parser.hpp"

#include "ast/errors/error.hpp"
#include "token/type.hpp"

#include <sstream>

namespace parser {
    parser::parser(lexer::lexer& lexer)
        : lexer(lexer),
          current(token::type::ILLEGAL, ""),
          next(token::type::ILLEGAL, "") {
        next_token();
        next_token();
    }

    void parser::next_token() {
        current = next;
        next = lexer.next_token();
    }

    ast::program* parser::parse_program() {
        ast::program* p = new ast::program();

        for (; current.type != token::type::END_OF_FILE; next_token()) {
            ast::statement* stmt = parse_statement();
            if (stmt != nullptr)
                p->statements.push_back(stmt);
        }

        return p;
    }

    ast::statement* parser::parse_statement() {
        switch (current.type) {
        case token::type::LET:
            return parse_let();
        default:
            return nullptr;
        }
    }

    bool parser::expect_next(token::type t) {
        if (next.type == t) {
            next_token();
            return true;
        }
        next_error(t);
        return false;
    }

    ast::let* parser::parse_let() {
        ast::let* stmt = new ast::let(current);

        if (!expect_next(token::type::IDENTIFIER)) {
            delete stmt;
            return nullptr;
        }

        stmt->name = new ast::identifier{current, current.literal};

        if (!expect_next(token::type::ASSIGN)) {
            delete stmt;
            return nullptr;
        }

        // TODO: we are currently skipping expressions until we encounter a
        // semicolon
        for (; current.type != token::type::SEMICOLON; next_token()) {}
        return stmt;
    }

    void parser::next_error(token::type t) {
        std::stringstream ss;
        ss << "Expected next token to be " << t << " but instead got "
           << next.type;
        errors.push_back(new ast::error::expected_next(t, ss.str()));
    }

    parser::~parser() {
        for (const auto& e : errors)
            delete e;
    }
} // namespace parser
