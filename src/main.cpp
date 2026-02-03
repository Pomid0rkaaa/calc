#include <iostream>
#include "parser.hpp"

int main(int argc, char* args[]) {
  std::string expr = "";
  for (int i = 1; i < argc; i++) {
    expr += args[i];
  }
  if (expr.empty()) return EXIT_FAILURE;
  Parser p(expr);
  std::cout << p.parse() << std::endl;
  return EXIT_SUCCESS;
}

