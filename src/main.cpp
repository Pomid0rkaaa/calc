#include <array>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include "parser.hpp"
#include "repl.hpp"

std::array<std::string, 19> help_message {
  "Usage:",
  "  calc [expression]",
  "",
  "Description:",
  "  A simple arithmetic calculator with variables.",
  "",
  "  If an expression is provided as arguments, it is evaluated and the",
  "  result is printed. If no arguments are given, an interactive REPL",
  "  session is started.",
  "",
  "Examples:",
  "  calc 1+2*3",
  "  calc \"(1 + 2) * 3\"",
  "",
  "Supported syntax:",
  "  - Numbers:          1, 2.5, .5",
  "  - Operators:        + - * /",
  "  - Parentheses:      ( )",
  "  - Variables (REPL): see `help` inside the REPL",
};

int main(int argc, char* args[]) {
  std::string expr = "";
  for (int i = 1; i < argc; i++) {
    expr += args[i];
  }
  if (expr.empty()) repl();
  else if (expr == "--help") {
    for (const std::string& s : help_message)
      std::cout << s << std::endl;
    return EXIT_SUCCESS;
  }
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

