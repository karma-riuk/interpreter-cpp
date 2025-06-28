#pragma once

#include "type.hpp"

#include <string>

struct Token {
    TokenType type;
    std::string literal;
};
