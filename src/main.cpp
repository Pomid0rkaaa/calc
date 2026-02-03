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
    size_t start = pos;
    while (pos < s.size() && (isdigit(s[pos]) || s[pos] == '.')) pos++;
    if (start == pos) throw runtime_error("Expected number");
    return stod(s.substr(start, pos - start));
  }
};

double eval(const string& expr);

int main(int argc, char* args[]) {
  string expr = "";
  for (int i = 1; i < argc; i++) {
    expr += args[i];
  }
  if (expr.empty()) return EXIT_FAILURE;
  cout << eval(expr) << endl;
  return EXIT_SUCCESS;
}

double eval(const string& expr) {
  Parser p(expr);
  return p.parse();
}

