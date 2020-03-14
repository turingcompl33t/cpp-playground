// tracer.cpp
// Simple object lifetime tracer.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++17 tracer.cpp

#include <string>
#include <random>
#include <iostream>

std::mt19937 g_gen{};
std::uniform_int_distribution<> g_dist{0, 1000};

class Tracer
{
    std::uniform_int<int>::result_type id;

public:
    explicit Tracer() : id{g_dist(g_gen)}
    {
        std::cout << '[' << id << ']'; 
        std::cout << " Tracer()\n";
    }

    ~Tracer()
    {
        std::cout << '[' << id << ']'; 
        std::cout << " ~Tracer()\n";
    }

    // copy constructor
    Tracer(Tracer const&) : id{g_dist(g_gen)}
    {
        std::cout << '[' << id << ']'; 
        std::cout << " Tracer(Tracer const&)\n";
    }

    // copy assignment operator
    Tracer& operator=(const Tracer&)
    {
        id = g_dist(g_gen);
        std::cout << '[' << id << ']'; 
        std::cout << " operator=(Tracer const&)\n";
    }

    // move constructor
    Tracer(Tracer&&) : id{g_dist(g_gen)}
    {
        std::cout << '[' << id << ']'; 
        std::cout << " Tracer(Tracer&&)\n"; 
    }

    // move assignment operator
    Tracer& operator=(Tracer &&)
    {
        id = g_dist(g_gen);
        std::cout << '[' << id << ']'; 
        std::cout << " operator=(Tracer&&)\n";
    }
};

int main()
{
    auto t1 = Tracer{};
    auto t2 = Tracer{t1};
    auto t3 = Tracer{std::move(t1)};

    return 0;
}