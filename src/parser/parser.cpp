#include "parser.hpp"

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

    void parser::skip_until_semicolon() {
        for (; current.type != token::type::SEMICOLON
               && current.type != token::type::END_OF_FILE;
             next_token()) {};
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
        case token::type::RETURN:
            return parse_return();
        default:
            return parse_expression_stmt();
        }
    }

    ast::expression* parser::parse_expression() {
        // TODO: we are currently skipping expressions until we encounter a
        // semicolon
        for (; current.type != token::type::SEMICOLON; next_token()) {}
        return nullptr;
    };

    ast::return_stmt* parser::parse_return() {
        ast::return_stmt* stmt = new ast::return_stmt(current);
        next_token();

        stmt->value = parse_expression();
        if (next.type == token::type::SEMICOLON)
            next_token();

        return stmt;
    }

    ast::let_stmt* parser::parse_let() {
        ast::let_stmt* stmt = new ast::let_stmt(current);

        if (!expect_next(token::type::IDENTIFIER)) {
            delete stmt;
            skip_until_semicolon();
            return nullptr;
        }

        stmt->name = new ast::identifier{current, current.literal};

        if (!expect_next(token::type::ASSIGN)) {
            delete stmt;
            skip_until_semicolon();
            return nullptr;
        }
        next_token();

        stmt->value = parse_expression();
        if (next.type == token::type::SEMICOLON)
            next_token();
        return stmt;
    }

    ast::expression_stmt* parser::parse_expression_stmt() {
        ast::expression_stmt* stmt = new ast::expression_stmt(current);

        stmt->expression = parse_expression();

        if (next.type == token::type::SEMICOLON)
            next_token();

        return stmt;
    };

    bool parser::expect_next(token::type t) {
        if (next.type == t) {
            next_token();
            return true;
        }
        next_error(t);
        return false;
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

    void parser::register_prefix(token::type type, prefix_parse_fn fn) {
        prefix_parse_fns[type] = fn;
    };

    void parser::register_infix(token::type type, infix_parse_fn fn) {
        infix_parse_fns[type] = fn;
    };
} // namespace parser
