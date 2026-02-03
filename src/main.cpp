#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;

class Parser {
  const string& s;
  size_t pos = 0;

public:
  Parser(const string& str) : s(str) {}
  
  double parse() {
    double result = parseExpression();
    if (pos != s.size()) throw runtime_error("Unexpected trailing characters");
    return result;
  }

  void skipSpaces() {
    while (pos < s.size() && isspace(s[pos])) pos++;
  }

  double parseExpression() {
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

  double parseTerm() {
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
  
  double parseFactor() {
    skipSpaces();
    if(s[pos] == '(') {
      pos++;
      double left = parseExpression();
      skipSpaces();
      if (pos >= s.size() || s[pos] != ')')
        throw runtime_error("Missing closing parenthesis");
      pos++;
      return left;
    }

    size_t start = pos;
    while (pos < s.size() && (isdigit(s[pos]) || s[pos] == '.')) pos++;
    if (start == pos) throw runtime_error("Expected number");
    return stod(s.substr(start, pos - start));
  }
};

int main(int argc, char* args[]) {
  string expr = "";
  for (int i = 1; i < argc; i++) {
    expr += args[i];
  }
  if (expr.empty()) return EXIT_FAILURE;
  Parser p(expr);
  cout << p.parse() << endl;
  return EXIT_SUCCESS;
}

