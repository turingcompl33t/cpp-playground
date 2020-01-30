// Client.cpp
// Client application for object lifetime tracer.

#include "tracer.h"

int main()
{
    // ctor + dtor
    {
        Tracer t0{};
    }

    Tracer t1{};
    Tracer t2{t1};            // copy ctor
    Tracer t3{std::move(t1)}; // move ctor 

    t2 = t3;              // copy assigment operator
    t3 = std::move(t2);   // move assignment operator

    // interesting to note that, even though t1 becomes
    // moved-from way up there, its dtor is only called 
    // at the exit from main(), like the other two 

    return 0;
}