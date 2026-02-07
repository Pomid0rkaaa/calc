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

run_error_test() {
  expr="$1"

  output="$($BIN "$expr" 2>&1)"
  status=$?

  error_line=$(echo "$output" | grep "Error")

  if [[ $status -ne 0 && -n "$error_line" ]]; then
    echo -e "${CPASS}PASS${CEND} (error): $expr -> $error_line"
  else
    echo -e "${CFAIL}FAIL${CEND} (expected error): $expr"
    echo "Exit code: $status"
    echo "Output:"
    echo "$output"
    FAIL=1
  fi
}

echo "Running calc tests..."

run_test "2+2" "4"
run_test "2+3*4" "14"
run_test "(2+3)*4" "20"
run_test "10/4" "2.5"
run_test "3 + 4 * (2 - 1)" "7"
run_test "1/0" "inf"
run_test "0-1/0" "-inf"
run_test '((((10))))' "10"
run_test "  3.5  +  1.5  " "5"
run_test "10 - 2 - 2 - 2" "4"

echo
echo "Running error tests..."

run_error_test "2+"
run_error_test "(3+4"
run_error_test "abc"
run_error_test "3 + 4 * (2 - 1))"
run_error_test "5 * / 2"

echo
if [ $FAIL -eq 0 ]; then
  echo -e "${CPASS}All tests passed${CEND}"
else
  echo -e "${CFAIL}Some tests failed${CEND}"
fi

exit $FAIL
