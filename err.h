#include <iostream>
#include "token.h"

void err(std::string name, Token token) {
    std::cout << "\nfuckie wuckie on line " << token.line << ":\n";
    std::cout << "\033[1;31m" << name << "\033[0m\n";
}