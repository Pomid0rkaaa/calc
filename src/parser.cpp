#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include "parser.hpp"
#include "repl.hpp"

Parser::Parser(const std::string& str) : s(str) {}

double Parser::parse() {
  double result = parseExpression();
  if (pos != s.size())
    throw std::runtime_error("Unexpected trailing characters");
  return result;
}

void Parser::skipSpaces() {
  while (pos < s.size() && std::isspace(static_cast<unsigned char>(s[pos])))
    pos++;
}

double Parser::parseExpression() {
  double left = parseTerm();

  while (pos < s.size()) {
    skipSpaces();
    char op = s[pos];
    if (op != '+' && op != '-') break;
    pos++;

    double right = parseTerm();
    if (op == '+') left += right;
    else left -= right;
  }
  return left;
}

double Parser::parseTerm() {
  double left = parseFactor();

  while (pos < s.size()) {
    skipSpaces();
    char op = s[pos];
    if (op != '*' && op != '/') break;
    pos++;

    double right = parseFactor();
    if (op == '*') left *= right;
    else left /= right;
  }
  return left;
}

double Parser::parseFactor() {
  skipSpaces();

  if (pos >= s.size())
    throw std::runtime_error("Unexpected end of input");

  if (s[pos] == '(') {
    pos++;
    double left = parseExpression();
    skipSpaces();
    if (pos >= s.size() || s[pos] != ')')
      throw std::runtime_error("Missing closing parenthesis");
    pos++;
    return left;
  }

  std::size_t start = pos;
  while (pos < s.size() && (std::isdigit(s[pos]) || s[pos] == '.'))
    pos++;

  if (start != pos)
    return std::stod(s.substr(start, pos - start));

  start = pos;
  if (std::isalpha(s[pos]) || s[pos] == '_') {
    pos++;
    while (pos < s.size() &&
           (std::isalnum(s[pos]) || s[pos] == '_'))
      pos++;
    std::string name = s.substr(start, pos - start);
    auto it = variables.find(name);
    if (it == variables.end())
      throw std::runtime_error("Undefined variable: " + name);

    return it->second;
  }

  throw std::runtime_error("Expected number or variable");
}

