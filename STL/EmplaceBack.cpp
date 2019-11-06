// EmplaceBack.cpp
// Demo of the cost savings of emplace_back vs push_back.

#include <iostream>
#include <vector>

struct Tracer
{
    Tracer() 
    { 
        std::cout << "Tracer()" << std::endl; 
    }

    Tracer(const Tracer& t) 
    { 
        std::cout << "Tracer(const Tracer& t)" << std::endl; 
    }

    Tracer& operator=(const Tracer&)
    {
        std::cout << "operator=(const Tracer &t)" << std::endl;
        return *this;
    }

    Tracer(Tracer&& t)
    {
        std::cout << "Tracer(Tracer &&t)" << std::endl;
    }

    Tracer& operator=(Tracer&& other)
    {
        std::cout << "operator=(Tracer &&t)" << std::endl;
        return *this;
    }

    ~Tracer() 
    { 
        std::cout << "~Tracer()" << std::endl; 
    }
};

int main()
{
    std::cout << "Push Back:" << std::endl;
    std::vector<Tracer> v1{};
    v1.push_back(Tracer());

    std::cout << "Emplace Back:" << std::endl;
    std::vector<Tracer> v2{};
    v2.emplace_back();
}