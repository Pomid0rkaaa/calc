#!/usr/bin/env bash

BIN="./build/calc"
FAIL=0
CFAIL="\033[31m"
CPASS="\033[32m"
CEND="\033[0m"

run_test() {
  expr="$1"
  expected="$2"

  output=$($BIN "$expr" 2>&1)

  if [[ "$output" == "$expected" ]]; then
    echo -e "${CPASS}PASS${CEND}: $expr = $output"
  else
    echo -e "${CFAIL}FAIL${CEND}: $expr -> got '$output', expected '$expected'"
    FAIL=1
  fi
}

echo "Running calc tests..."

run_test "2+2" "4"
run_test "2+3*4" "14"
run_test "(2+3)*4" "20"
run_test "10/4" "2.5"
run_test "3 + 4 * (2 - 1)" "7"

echo
if [ $FAIL -eq 0 ]; then
  echo -e "${CPASS}All tests passed${CEND}"
else
  echo -e "${CFAIL}Some tests failed${CEND}"
fi

exit $FAIL
