#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

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
  return expr.size();
}

