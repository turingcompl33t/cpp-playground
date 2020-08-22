// IILE.cpp
// Demo of immediately invoked lambda expression.

#include <string>
#include <iostream>

std::string naive(int i)
{
    std::string r;
    switch (i % 4)
    {
        case 0:
            r = "zero";
            break;
        case 1:
            r = "one";
            break;
        case 2:
            r = "two";
            break;
        case 3:
            r = "three";
            break;
    }

    return r;
}

std::string iile(int i)
{
    return [&]()
    {
        switch (i % 4)
        {
            case 0:
                return "zero";
            case 1:
                return "one";
            case 2:
                return "two";
            case 3:
                return "three";
        }
    }();
}

int main()
{
    const int i = std::rand();
    std::string s1 = naive(i);
    std::string s2 = iile(i);

    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
}