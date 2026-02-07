#include <array>
#include <string>
#include <unordered_map>
#include <iostream>
#include "repl.hpp"
#include "parser.hpp"

std::unordered_map<std::string, double> variables;

std::array<std::string, 21> help_message_repl {
  "Calculator REPL help",
  "",
  "Expressions:",
  "  - Supports +, -, *, / with standart precedence",
  "  - Parentheses can be used to group expressions",
  "  - Example: (1 + 2) * 3",
  "",
  "Variables:",
  "  var x = 10        define or update variable",
  "  var y = x * 2",
  "  vars              list all variables",
  "  del x             delete a variable",
  "  clear | reset     remove all variables",
  "",
  "Commands:",
  "  help              shows this help message",
  "  exit              quit the REPL",
  "",
  "Notes:",
  "  - Variables names may contain letters, digits, and underscores",
  "  - Whitespaces is ignored in expressions",
};

std::string trim (const std::string& str) {
  std::string trimmed;
  for (auto& c : str.substr(4)) {
    if (c == ' ') continue;
    trimmed += c;
  }
  return trimmed;
}

ReplResult handle_line(const std::string &input, std::ostream &out, std::ostream &err) {
  if (input.empty())
    return ReplResult::Continue;

  if (input == "exit")
    return ReplResult::Exit;

  if (input == "clear" || input == "reset") {
    variables.clear();
    out << "Variables cleared" << std::endl;
    return ReplResult::Continue;
  }

  if (input == "help") {
    for (const std::string& s : help_message_repl)
      out << s << std::endl;
    return ReplResult::Continue;
  }

  if (input.rfind("del ", 0) == 0) {
    std::string name = input.substr(4);
    name.erase(0, name.find_first_not_of(" \t"));
    name.erase(name.find_last_not_of(" \t") + 1);

    if (name.empty()) {
      err << "Error: variable name required" << std::endl;
      return ReplResult::Continue;
    }

    if (variables.erase(name))
      out << "Deleted " << name << std::endl;
    else
      err << "Error: variable not found: " << name << std::endl;

    return ReplResult::Continue;
  }

  if (input.rfind("var ", 0) == 0) {
    std::string trimmed = trim(input);
    auto eq = trimmed.find('=');

    if (eq == std::string::npos) {
      err << "Error: invalid variable declaration" << std::endl;
      return ReplResult::Continue;
    }

    std::string name = trimmed.substr(0, eq);
    std::string valuestr = trimmed.substr(eq + 1);

    try {
      Parser p(valuestr);
      double value = p.parse();
      variables.insert_or_assign(name, value);
      out << name << " = " << value << std::endl;
    } catch (const ParseError& e) {
      int ePos = e.pos + 4 + name.size() + 1;
      err << "var " << trimmed << std::endl;
      err << std::string(ePos, ' ') << "^" << std::endl;
      err << "Error: " << e.message << " at position " << ePos << std::endl;
    }

    return ReplResult::Continue;
  }

  if (input == "vars") {
    if (variables.empty())
      out << "No variables" << std::endl;
    else
      for (const auto& [name, value] : variables)
        out << name << " = " << value << std::endl;

    return ReplResult::Continue;
  }

  if (
    input.find("var", 0) == 0
    && input.size() > 3
    && input[3] != ' '
  ) {
    err << "Error: did you mean `var x = ...` ?" << std::endl;
    return ReplResult::Continue;
  }

  try {
    Parser p(input);
    out << p.parse() << std::endl;
  } catch (const ParseError& e) {
    err << e.input << std::endl;
    err << std::string(e.pos, ' ') << "^" << std::endl;
    err << "Error: " << e.message
      << " at position " << e.pos+1 << std::endl;
  }

  return ReplResult::Continue;
}

void repl() {
  std::string input = "";
  while (true) {
    std::cout << std::endl << "calc> ";
    std::getline(std::cin, input);

    if (handle_line(input, std::cout, std::cerr) == ReplResult::Exit)
      break;
  }
}
