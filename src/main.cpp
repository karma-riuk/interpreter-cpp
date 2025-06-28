#include "token/type.hpp"

#include <iostream>

int main() {
    auto eof = TokenType::ILLEGAL;
    std::cout << eof << std::endl;
    return 0;
}
