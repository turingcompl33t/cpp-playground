// ClangTools.cpp
// Example program to demonstrate use of Clang tooling in VS.
//
// Invoking cppcheck.exe on this source file should identify the nullptr dereference;
// while MSVC with /W4 will compile it without any issues.

#include <iostream>

int main()
{
	std::cout << "Hello CppCheck" << std::endl;

	// extremely contrived example
	int* ptr = nullptr;
	(*ptr) = 1729;
}