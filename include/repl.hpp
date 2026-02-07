#ifndef REPL_HPP
#define REPL_HPP

#include <string>
#include <unordered_map>
#include <ostream>

extern std::unordered_map<std::string, double> variables;

enum class ReplResult {
  Continue,
  Exit
};

ReplResult handle_line(
  const std::string& input,
  std::ostream& out,
  std::ostream& err
);

void repl();

#endif
