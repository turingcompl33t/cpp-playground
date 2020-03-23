// DynamicFail.cpp
// A case study of a common failure in dynamic casting.

#include <iostream>

class Base
{
public:
    virtual ~Base() {}
    virtual void Call()
    {
        std::cout << "Base::Call()" << std::endl;
    }
};

class Derived : public Base
{
public:
    void Call()
    {
        std::cout << "Derived::Call()" << std::endl;
    }
};

int main()
{
    Base* b = new Base();
    
    // do stuff here

    // obviously this is an error
    Derived* d = dynamic_cast<Derived*>(b);

    // in older versions of standard, this call would not fail
    // instead, because the Call() function may be invoked statically, 
    // the Derived::Call() function would be invoked (as expected?)
    d->Call();

    std::cout << "Base* b    = " << b << std::endl;
    std::cout << "Derived *d = " << d << std::endl;
}