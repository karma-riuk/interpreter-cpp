#include "parser.hpp"

#include "ast/errors/error.hpp"
#include "ast/expressions/boolean.hpp"
#include "ast/expressions/function.hpp"
#include "ast/expressions/identifier.hpp"
#include "ast/expressions/if_then_else.hpp"
#include "ast/expressions/infix.hpp"
#include "ast/expressions/integer.hpp"
#include "ast/expressions/prefix.hpp"
#include "ast/statements/block.hpp"
#include "token/token.hpp"
#include "token/type.hpp"
#include "utils/tracer.hpp"

#include <sstream>

namespace parser {
    parser::parser(lexer::lexer& lexer)
        : lexer(lexer),
          current(token::type::ILLEGAL, ""),
          next(token::type::ILLEGAL, "") {
        next_token();
        next_token();

        register_prefix(
            token::type::IDENTIFIER,
            std::bind(&parser::parse_identifier, this)
        );

        register_prefix(
            token::type::INT,
            std::bind(&parser::parse_integer, this)
        );

        register_prefix(
            {
                token::type::BANG,
                token::type::MINUS,
            },
            std::bind(&parser::parse_prefix_expr, this)
        );

        register_prefix(
            {
                token::type::TRUE,
                token::type::FALSE,
            },
            std::bind(&parser::parse_boolean, this)
        );

        register_prefix(
            token::type::LPAREN,
            std::bind(&parser::parse_grouped_expr, this)
        );

        register_prefix(
            token::type::IF,
            std::bind(&parser::parse_if_then_else, this)
        );

        register_prefix(
            token::type::FUNCTION,
            std::bind(&parser::parse_function, this)
        );

        using namespace std::placeholders;
        register_infix(
            {token::type::PLUS,
             token::type::MINUS,
             token::type::ASTERISK,
             token::type::SLASH,
             token::type::EQ,
             token::type::NEQ,
             token::type::GT,
             token::type::LT},
            std::bind(&parser::parse_infix_expr, this, _1)
        );
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

    std::unique_ptr<ast::program> parser::parse_program() {
        std::unique_ptr<ast::program> p = std::make_unique<ast::program>();

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

    ast::expression* parser::parse_expression(precedence prec) {
        TRACE_FUNCTION;
        auto prefix_it = prefix_parse_fns.find(current.type);
        if (prefix_it == prefix_parse_fns.end()) {
            unkown_prefix_error(current);
            return nullptr;
        }

        prefix_parse_fn prefix = prefix_it->second;
        ast::expression* left = prefix();

        while (next.type != token::type::SEMICOLON
               && prec < precedence_for(next.type)) {
            auto infix_it = infix_parse_fns.find(next.type);
            if (infix_it == infix_parse_fns.end())
                return left;
            next_token();

            infix_parse_fn infix = infix_it->second;
            left = infix(left);
        }
        return left;
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
        TRACE_FUNCTION;
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

    void parser::unkown_prefix_error(token::token tok) {
        std::stringstream ss;
        ss << "No prefix parse function for token " << tok;
        errors.push_back(new ast::error::unkown_prefix(tok, ss.str()));
    }

    parser::~parser() {
        for (const auto& e : errors)
            delete e;
    }

    void parser::register_prefix(token::type type, prefix_parse_fn fn) {
        prefix_parse_fns[type] = fn;
    };

    void parser::register_prefix(
        std::vector<token::type> types, prefix_parse_fn fn
    ) {
        for (auto& type : types)
            register_prefix(type, fn);
    };

    void parser::register_infix(token::type type, infix_parse_fn fn) {
        infix_parse_fns[type] = fn;
    };

    void
    parser::register_infix(std::vector<token::type> types, infix_parse_fn fn) {
        for (auto& type : types)
            register_infix(type, fn);
    };

    ast::identifier* parser::parse_identifier() {
        return new ast::identifier(current, current.literal);
    };

    ast::integer_literal* parser::parse_integer() {
        TRACE_FUNCTION;
        return new ast::integer_literal(current, std::stoi(current.literal));
    };

    ast::boolean_literal* parser::parse_boolean() {
        TRACE_FUNCTION;
        return new ast::boolean_literal(
            current,
            current.type == token::type::TRUE
        );
    };

    ast::function_literal* parser::parse_function() {
        TRACE_FUNCTION;
        ast::function_literal* ret = new ast::function_literal(current);
        if (!expect_next(token::type::LPAREN)) {
            delete ret;
            return nullptr;
        }

        while (next.type != token::type::RPAREN
               && expect_next(token::type::IDENTIFIER)) {
            ret->parameters.push_back(parse_identifier());
            if (next.type == token::type::RPAREN)
                break;
            if (!expect_next(token::type::COMMA)) {
                delete ret;
                return nullptr;
            }
        }
        if (current.type == token::type::COMMA
            && next.type == token::type::RPAREN) {
            next_error(token::type::IDENTIFIER);
            delete ret;
            return nullptr;
        }

        if (!expect_next(token::type::RPAREN)) {
            delete ret;
            return nullptr;
        }

        if (!expect_next(token::type::LBRACE)) {
            delete ret;
            return nullptr;
        }
        ret->block = parse_block();

        return ret;
    };

    ast::prefix_expr* parser::parse_prefix_expr() {
        TRACE_FUNCTION;
        ast::prefix_expr* ret = new ast::prefix_expr(current, current.literal);
        next_token();
        ret->right = parse_expression(precedence::PREFIX);
        return ret;
    };

    ast::expression* parser::parse_grouped_expr() {
        TRACE_FUNCTION;
        next_token();
        ast::expression* ret = parse_expression(precedence::LOWEST);

        if (!expect_next(token::type::RPAREN)) {
            delete ret;
            return nullptr;
        }

        return ret;
    };

    ast::if_then_else* parser::parse_if_then_else() {
        TRACE_FUNCTION;
        ast::if_then_else* ret = new ast::if_then_else(current);
        if (!expect_next(token::type::LPAREN)) {
            delete ret;
            return nullptr;
        }

        next_token();
        ret->condition = parse_expression();

        if (!expect_next(token::type::RPAREN)) {
            delete ret;
            return nullptr;
        }

        if (!expect_next(token::type::LBRACE)) {
            delete ret;
            return nullptr;
        }

        ret->consequence = parse_block();
        if (next.type != token::type::ELSE)
            return ret;
        next_token();

        if (!expect_next(token::type::LBRACE)) {
            delete ret;
            return nullptr;
        }

        ret->alternative = parse_block();
        return ret;
    };

    ast::block_stmt* parser::parse_block() {
        TRACE_FUNCTION;
        ast::block_stmt* ret = new ast::block_stmt(current);

        for (next_token(); current.type != token::type::RBRACE
                           && current.type != token::type::END_OF_FILE;
             next_token()) {
            ast::statement* stmt = parse_statement();
            if (stmt != nullptr)
                ret->statements.push_back(stmt);
        }

        if (current.type != token::type::RBRACE) {
            next_error(token::type::RBRACE);
            delete ret;
            return nullptr;
        }


        return ret;
    }

    ast::infix_expr* parser::parse_infix_expr(ast::expression* left) {
        TRACE_FUNCTION;
        ast::infix_expr* ret =
            new ast::infix_expr(current, current.literal, left);
        precedence prec = precedence_for(current.type);
        next_token();
        ret->right = parse_expression(prec);
        return ret;
    };
} // namespace parser
