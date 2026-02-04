# Simple CLI Calculator

A tiny command-line calculator written in C++ that evaluates arithmetic expressions using a recursive descent parser.

Supports:
- Addition and subtraction: `+ -`
- Multiplication and division: `* /`
- Parentheses for grouping: `( ... )`
- Floating point numbers
- Whitespace inside expressions

## Build

Requires a C++17-compatible compiler (e.g. `g++`, `clang++`)
```bash
make
```

This builds the binary at:
```bash
build/calc
```

To clean build artifacts:
```bash
make clean
```

## Usage

```bash
./build/calc "<expression>"
```

Examples:
```bash
./build/calc "2+2"
./build/calc "3 * (4 + 5)"
./build/calc "10 / 4 + 1.5"
```

## Tests

The project includes a suite of tests to ensure the parser handles both standard arithmetic and edge cases (like operator precedence and nested parentheses) correctly.
To execute the test suite:
```bash
make test
```

## Error handling

The calculator reports errors for invalid input, such as:
- Unexpected trailing characters
- Missing closing parentheses
- Invalid or missing numbers

