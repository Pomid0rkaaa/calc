CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

SRC_LIB = src/parser.cpp src/repl.cpp
SRC_APP = src/main.cpp

OBJ_LIB = $(SRC_LIB:src/%.cpp=build/%.o)
OBJ_APP = $(SRC_APP:src/%.cpp=build/%.o)

TARGET = build/calc

TEST_REPL_SRC = tests/repl_tests.cpp
TEST_REPL_OBJ = build/repl_tests.o
TEST_REPL_BIN = build/repl_tests

.PHONY: all build clean test

all: $(TARGET)

$(TARGET): $(OBJ_LIB) $(OBJ_APP) | build
	$(CXX) $(CXXFLAGS) $^ -o $@

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_REPL_OBJ): $(TEST_REPL_SRC) | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_REPL_BIN): $(OBJ_LIB) $(TEST_REPL_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

build:
	mkdir -p build

clean:
	rm -rf build

test: all $(TEST_REPL_BIN)
	./$(TEST_REPL_BIN)
	./tests/test.sh
