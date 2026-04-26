CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
INCLUDE = -Iinclude

MAIN = main.cpp
TEST = tests.cpp

MAIN_OUT = main
TEST_OUT = test

all: main

main:
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(MAIN) -o $(MAIN_OUT)

test_build:
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(TEST) -o $(TEST_OUT)

run: main
	./main

test: test_build
	./test

clean:
	rm -f main test