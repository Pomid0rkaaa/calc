#include <cassert>
#include <sstream>
#include <iostream>
#include "repl.hpp"

void reset() {
  variables.clear();
}

void test_expression() {
  reset();
  std::ostringstream out, err;

  handle_line("1 + 2 * 3", out, err);

  assert(out.str() == "7\n");
  assert(err.str().empty());
}

void test_variables() {
  reset();
  std::ostringstream out, err;

  handle_line("var x = 5", out, err);
  handle_line("x * 2", out, err);

  assert(out.str().find("x = 5") != std::string::npos);
  assert(out.str().find("10") != std::string::npos);
}

void test_exit() {
  reset();
  std::ostringstream out, err;

  auto r = handle_line("exit", out, err);
  assert(r == ReplResult::Exit);
}

int main() {
  test_expression();
  test_variables();
  test_exit();

  std::cout << "\033[32mREPL tests passed\033[0m\n";
}
