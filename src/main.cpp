#include "repl/repl.hpp"

#include <iostream>

int main() {
    repl::start(std::cin, std::cout);
    return 0;
}
