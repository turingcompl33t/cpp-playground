// Tracer.cpp
// Object lifetime tracer.

#include <string>
#include <iostream>

#include "tracer.h"

Tracer::Tracer()
{
    std::cout << "Tracer::Tracer()" << std::endl;
}

Tracer::~Tracer()
{
    std::cout << "Tracer::~Tracer()" << std::endl;
}

Tracer::Tracer(const Tracer& rhs)
{
    std::cout << "Tracer::Tracer(const Tracer& rhs)" << std::endl;
}

Tracer& Tracer::operator=(const Tracer& rhs)
{
    std::cout << "Tracer::operator=(const Tracer& rhs)" << std::endl;
    
    return *this;
}

Tracer::Tracer(Tracer&& rhs)
{
    std::cout << "Tracer::Tracer(Tracer&& rhs)" << std::endl;
}

Tracer& Tracer::operator=(Tracer&& rhs)
{
    std::cout << "Tracer::operator=(Tracer&& rhs)" << std::endl;

    return *this;
}