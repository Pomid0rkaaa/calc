#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include "parser.hpp"

void repl();

int main(int argc, char* args[]) {
  std::string expr = "";
  for (int i = 1; i < argc; i++) {
    expr += args[i];
  }
  if (expr.empty()) repl();
  else {
    Parser p(expr);
    try {
      std::cout << p.parse() << std::endl;
    } catch (const std::exception& e) {
      std::cerr << "Error: " << e.what() << std::endl;
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }
}

void repl() {
  std::string input = "";
  while (1) {
    std::cout << std::endl << "> ";
    std::getline(std::cin, input);
    if (input.empty()) continue;
    else if (input == "exit") exit(0);
    else {
      Parser p(input);
      try {
        std::cout << p.parse() << std::endl;
      } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
      }
    }
  }
}
