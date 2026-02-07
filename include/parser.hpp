#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>

class Parser {
  const std::string& s;
  std::size_t pos = 0;

public:
  explicit Parser(const std::string& str);
  double parse();

private:
  void skipSpaces();
  double parseExpression();
  double parseTerm();
  double parseFactor();
};

#endif
