CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

SRC = src/main.cpp src/parser.cpp
OBJ = $(SRC:src/%.cpp=build/%.o)
TARGET = build/calc

.PHONY: all build clean test

all: $(TARGET)

$(TARGET): $(OBJ) | build
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build

test: all
	./tests/test.sh
