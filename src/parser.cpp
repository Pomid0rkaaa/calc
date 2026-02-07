#include <cctype>
#include <cstdlib>
#include "parser.hpp"
#include "repl.hpp"

Parser::Parser(const std::string& str) : s(str) {}

double Parser::parse() {
  double result = parseExpression();
  if (pos != s.size())
    throw ParseError("Unexpected trailing characters", s, pos);
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
    throw ParseError("Unexpected end of input", s, pos);

  if (s[pos] == '(') {
    pos++;
    double left = parseExpression();
    skipSpaces();
    if (pos >= s.size() || s[pos] != ')')
      throw ParseError("Missing closing parenthesis", s, pos);
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
      throw ParseError("Undefined variable: " + name, s, pos);

    return it->second;
  }

  throw ParseError("Expected number or variable", s, pos);
}

