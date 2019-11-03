## Namespaces in C++

Namespaces exist to avoid naming conflicts. 

### Namespace Basics

Namespaces allow us to define identical symbols yet retain the ability to differentiate between them (and thus not draw the ire of the compiler or linker) by doing so within differentaited enclosing context. 

```C++
namespace A {
    void print()
    {
        std::cout << "in namespace A" << std::endl;
    }
}

namespace B {
    void print()
    {
        std::cout << "in namespace B" << std::endl;
    }
}

A::print();
B::print();
```

Namespaces can be nested arbitrarily. 

```C++
namespace A {
    void print()
    {
        std::cout << "in namespace A" << std::endl;
    }

    namespace B {
        void print()
        {
            std::cout << "in namespace B" << std::endl;
        }

        namespace C {
            void print()
            {
                std::cout << "in namespace C" << std::endl;
            }
        }
    }
}

A::print();
A::B::print();
A::B::C::print();
```

This could also be written without all of the ugly explicit nesting:

```C++
namespace A {
    /* stuff */
}

namespace A::B {
    /* stuff */
}

namespace A::B::C {
    /* stuff */
}
```

### The `using` Directive

The `using` directive effectively "imports" a symbol into a block scope or namespace. 

### Should We `using namespace XXX`?

In the event that we specify that we are using multiple namespaces, should we be worried about potential ambiguity?

One specific instance in which we can definitively respond in the negative to this question is in the case of header files — never `using namespace` in a header file. 
