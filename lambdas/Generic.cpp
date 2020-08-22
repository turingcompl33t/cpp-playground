// Generic.cpp
// Basic generic lambdas.

#include <iostream>

int main()
{
   auto f = [value=1](auto x){ return x + value; }; 

   std::cout << f(42) << std::endl;
   std::cout << f(3.14) << std::endl;
}