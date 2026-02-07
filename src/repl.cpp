#include <string>
#include <unordered_map>
#include <iostream>
#include "repl.hpp"
#include "parser.hpp"

std::unordered_map<std::string, double> variables;

std::string trim (std::string& str) {
  std::string trimmed;
  for (auto& c : str.substr(4)) {
    if (c == ' ') continue;
    trimmed += c;
  }
  return trimmed;
}

void repl() {
  std::string input = "";
  while (1) {
    std::cout << std::endl << "> ";
    std::getline(std::cin, input);
    if (input.empty()) continue;
    else if (input == "exit") exit(0);
    else if (input == "clear" || input == "reset") {
      variables.clear();
      std::cout << "Variables cleared" << std::endl;
    }
    else if (input.rfind("del ", 0) == 0) {
      std::string name = input.substr(4);
      name.erase(0, name.find_first_not_of(" \t"));
      name.erase(name.find_last_not_of(" \t") + 1);
      if (name.empty()) {
        std::cerr << "Error: variable name required" << std::endl;
        continue;
      }
      if (variables.erase(name))
        std::cout << "Deleted " << name << std::endl;
      else
        std::cerr << "Error: variable not found: " << name << std::endl;
    }
    else if (input.rfind("var ", 0) == 0) {
      std::string trimmed = trim(input);
      auto eq = trimmed.find('=');
      if (eq == std::string::npos) {
        std::cerr << "Error: invalid variable declaration" << std::endl;
        continue;
      }
      std::string name = trimmed.substr(0, eq);
      std::string valuestr = trimmed.substr(eq + 1);
      double value = 0;
      Parser p(valuestr);
      try {
        value = p.parse();
      } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        continue;
      }
      variables.insert_or_assign(name, value);
      std::cout << name << " = " << value << std::endl;
    }
    else if (input == "vars") {
      if (variables.empty())
        std::cout << "No variables" << std::endl;
      else for (const auto& [name, value] : variables)
      std::cout << name << " = " << value << std::endl;
    }
    else if (
      input.find("var", 0) == 0
      && input.size() > 3
      && input[3] != ' '
    )
      std::cerr << "Error: did you mean `var x = ...` ?" << std::endl;

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
