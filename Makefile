CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

SRC = src/main.cpp src/parser.cpp
OBJ = $(SRC:src/%.cpp=build/%.o)
TARGET = build/calc

all: $(TARGET)

$(TARGET): $(OBJ) | build
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build

