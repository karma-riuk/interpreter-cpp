#pragma once

#include "type.hpp"

#include <string>

struct token {
    TokenType type;
    std::string literal;
};
