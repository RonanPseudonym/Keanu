#include <iostream>
#include <fstream>
#include <string>
#include "parse.h"

Parser parser = Parser();

void exec(std::string data) {
    parser.run(data);
}

void exec_from_file(std::string name) {
	std::ifstream stream (name, std::ios::in);
	std::istreambuf_iterator<char> eos;
	std::string data(std::istreambuf_iterator<char>(stream), eos);

    exec(data);
}

void shell() {
    // std::string inp;

    // for (;;) {
    //     std::cout << "$ ";
    //     std::cin >> inp;

    //     exec(inp);
    // }

    err("i got rid of the REPL now you can only run files\n(bitch)", Token(TType::INCREMENT, 1));
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        shell();
    } else {
        exec_from_file(argv[1]);
    }

    return 0;
}