# calc - CLI Calculator with REPL

`calc` is a small but fully-featured command-line calculator written in C++17.
It evaluates arithmetic expressions using a recursive-descent parser and
includes an interactive REPL with variables and built-in commands.

The project is intentionally simple, dependency-free, and easy to extend.

## Features

### Expression evaluation
- Operators: `+  -  *  /`
- Standard operator precedence
- Parentheses for grouping
- Floating-point numbers
- Whitespace-insensitive input

### Interactive REPL
- Persistent variables
- Variable assignment and deletion
- Built-in commands (`help`, `vars`, `clear`, `exit`)
- Error reporting without crashing the session

### Testing
- Shell-based CLI tests (integration tests)
- C++ unit tests for REPL logic
- Single `make test` command runs everything

## Build

### Requirements
- C++17 compatible compiler (`g++`, `clang++`)
- `make`
- POSIX shell (for test script)

### Build the calculator

```bash
make
```

The binary will be created at:
```bash
build/calc
```

To remove build artifacts:
```bash
make clean
```

## Usage

### Inline (non-interactive) mode

Evaluate an expression directly from the command line:
```bash
./build/calc "2 + 3 * 4"
```

Examples:
```bash
./build/calc "2+2"
./build/calc "(1 + 2) * 3"
./build/calc "10 / 4 + 1.5"
```

### Help

```bash
./build/calc --help
```

### Interactive REPL

Start the REPL by running `calc` with no arguments:
```bash
./build/calc
```

You will see a prompt:
```
> 
```

#### REPL Commands

```
help              show REPL help
exit              quit the REPL
vars              list all variables
clear | reset     remove all variables
del <name>        delete a variable
```

#### Variables

```
var x = 10
var y = x * 2
x + y
```

Variable names may contain letters, digits, and underscores.

## Tests

### Run all tests

```bash
make test
```

This runs:
1. C++ unit tests for REPL logic
2. Shell-based CLI tests for inline expression evaluation

### Test layout

```
tests/
  repl_tests.cpp   # C++ unit tests (REPL behavior)
  test.sh          # CLI integration tests
```

## Project structure

```
include/
  parser.hpp
  repl.hpp

src/
  main.cpp         # CLI entry point
  parser.cpp       # Recursive descent parser
  repl.cpp         # REPL implementation

tests/
  repl_tests.cpp
  test.sh

build/
  calc
  repl_tests
```

## Error Handling

The calculator reports errors for invalid input, including:
- Unexpected end of input
- Unexpected trailing characters
- Missing closing parentheses
- Undefined variables
- Invalid variable declarations
Errors are printed to `stderr`.
In REPL mode, errors do not terminate the session.

## Development Notes

- No external libraries are used
- Parsing logic is fully deterministic
- REPL logic is unit-testable via stream injection
- Global state is limited to variable storage

