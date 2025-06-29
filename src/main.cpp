#include "token/type.hpp"

#include <iostream>

int main() {
    token::type eof = token::type::ILLEGAL;
    std::cout << eof << std::endl;
    return 0;
}
