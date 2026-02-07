CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

SRC_LIB = src/parser.cpp src/repl.cpp
SRC_APP = src/main.cpp

OBJ_LIB = $(SRC_LIB:src/%.cpp=build/%.o)
OBJ_APP = $(SRC_APP:src/%.cpp=build/%.o)

TARGET = build/calc

.PHONY: all build clean test

all: $(TARGET)

$(TARGET): $(OBJ_LIB) $(OBJ_APP) | build
	$(CXX) $(CXXFLAGS) $^ -o $@

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build

test: all
	./tests/test.sh
