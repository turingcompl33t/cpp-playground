// Tracer.h
// Object lifetime tracer.

#pragma once

#include <string>

class Tracer
{
public:
    Tracer();
    ~Tracer();

    // copy constructor
    Tracer(const Tracer& rhs);

    // copy assignment operator
    Tracer& operator=(const Tracer& rhs);

    // move constructor
    Tracer(Tracer&& rhs);

    // move assignment operator
    Tracer& operator=(Tracer &&rhs);

private:
    std::string name;
};