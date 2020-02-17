// FmtHelloWorld.cpp
// Demo of basic usage of fmtlib.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\FmtLib\include FmtHelloWorld.cpp 

#define FMT_HEADER_ONLY
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/format-inl.h>

int main()
{
    fmt::print("Hello {}!\n", "World");
}