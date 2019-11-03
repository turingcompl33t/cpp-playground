## Reference Types in C++

In this context, _reference types_ simply refer to those types that store the memory address of an object. From this very simple idea, many complex and powerful constructions emerge. 

### Pointers

Pointers are the foundational reference type. Anyone with a background in C will be completely comfortable with how pointers behave in C++. 

```C++
int val = 1;       // define an integer value 
int *ptr = &val;   // get a pointer to that value with "address of" operator, &
int val2 = *ptr;   // dereference ptr with * operator to get back original val, in new variable 
```

Notice that a pointer inherently specifies two pieces of information regarding the object to which they point:

- the memory address at which that object is located 
- the type of that object 

This type information allows us to perform pointer arithmetic wherein the compiler infers the value that the programmer intends to add to or subtract from a pointer based on the type of the object that is pointed to. For instance:

```C++
short short_arr[] = {1, 2};
long  long_arr[]  = {1, 2};

// arrays decay to pointers
short *short_ptr = short_arr;
long  *long_ptr  = long_arr;

short_ptr += 1  // adds 2 bytes to address
long_ptr  += 1  // adds 8 bytes to address
```

### References

Unlike pointers, references cannot be reseated (reassigned), and furthermore we cannot create a reference to a null value that is analogous to `nullptr` for pointers. For these reasons, references are, in some ways, a safer version of pointers. 

The following example demonstrate two equivalent ways of working with an `Entity` class using pointers and references. 

```C++
struct Entity {
    int m_x, m_y;
    
    Entity(int x, int y)
        : m_x(x), m_y(y) {}
    
    void Print()
    {
        std::cout << m_x << ", " << m_y << std::endl;
    }
};

void ComputePtr(Entity *e)
{
    e->Print();
    // or (*e).Print();
}

void ComputeRef(Entity &e)
{
    e.Print();
}

int main() {
    Entity e {1, 2};
    ComputePtr(&e);
    ComputeRef(e);
    return 0;
}
```

There are certainly times when references are not applicable to the problem that we are attempting to solve, and therefore a pointer must be used. In instances where this is not the case, we should prefer the use of references over pointers. 

### The `const` Keyword

I never thought much of `const` when programming in C. The only instances in which I used it were for declaring static, constant global variables that would be used (unsurprisingly) as constant values in some translation unit. However, since moving over to programming in C++, I have found that `const` is an extremely powerful tool for enforcing program correctness at compile-time.

_Constant Parameters_

```C++
void compute(const Entity& e)
{
	// entity e passed by constant reference 
	// we can no longer modify e within body of this function 
}
``` 

_Constant Methods_

```C++
class Entity {
private:
	int m_x, m_y;
public:
	void Print() const 
	{
		// a constant method 
		// we can no longer write class members in the body of this method 
	}
}
```

_Constants with Reference Types_

The semantic meaning of the `const` keyword when placed at different locations in the definition of a reference type variable often confuses me. Walking through an example like the following typically clears things up. 

```C++
int a = 10;
int z = 15;

// b is a pointer to an integer that is constant
const int *b = &a;

// OK: b = &z;
// NOT OK: *b = 20;

// c is a constant pointer to an integer
int* const c = &a;

// OK: *c = 20;
// NOT OK: c = &z;

// d is a constant pointer to an integer that is constant 
const int* const d = &a;

// NOT OK: d = &z;
// NOT OK: *d = 20;
```

_Aside: East vs West `const`_

There is ambiguity regarding the exact location of the `const` keyword relative to the variable that it modifies. The `const` keyword may actually appear either to the left or to the right of the modified variable. The former case is referred to as _left const_ while the latter case is referred to as _right const_. 

```C++
// these definitions are equivalent
const int a = 10;
int const b = 20;
```

Valid arguments exist on both sides of this debate. 

### References with _rvalues_

So far, we have implictly been restricting ourselves to passing arguments to functions by _lvalue_ reference, however, it is also possible to pass parameters in the _rvalue_ value category to functions by _rvalue_ reference. Furthermore, the compiler is adept at differentiating between the two. 

```C++
// lvalue reference
void print(const int& x)
{
    std::cout << "lvalue: " << x << std::endl;
}

// rvalue reference
void print(const int&& x)
{
    std::cout << "rvalue: " << x << std::endl;
}

auto x = 1;
print(x);
print(5);
```
