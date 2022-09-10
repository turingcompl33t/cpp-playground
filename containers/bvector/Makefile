# Makefile

CXXFLAGS=-std=c++2a -ggdb -Wall -Werror -fsanitize=address

.PHONY: build
build:
	g++ ${CXXFLAGS} -o main main.cpp

.PHONY: clean
clean:
	rm -f *.o
	rm -f main

.PHONY: format
format:
	clang-format -i main.cpp
	clang-format -i BitVector.hpp