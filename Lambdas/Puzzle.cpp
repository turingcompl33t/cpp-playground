// Puzzle.cpp
// Puzzle from Arthur O'Dwyer's CppCon 2019 talk.

#include <iostream>

static int g = 10;

auto f1 = [=]() { return g + 1; };
auto f2 = [g=g](){ return g + 1; };

int main()
{
    g = 20;

    // naturally, these print different values; what happened?
    std::cout << "f1() = " << f1() << std::endl;  // 21
    std::cout << "f2() = " << f2() << std::endl;  // 11

    // with f1, we specify that we want to capture everything
    // that we need by value; this does not "capture" the value
    // of g at the time we declare it because g is globally availabe,
    // there is only one copy 

    // with f2, we explicitly say that we want to capture g
    // by value at the point the lambda is delcared, so the 
    // value of g at the time of the declaration is what is
    // captured by the lambda, and it does not reflect the 
    // value after it is updated in the body of main()
}