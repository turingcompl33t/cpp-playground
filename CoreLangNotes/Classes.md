## Classes in C++

Classes are at the heart of what makes C++ significantly more powerful than its predecessor, C. 

### Basic Class Structure

```C++
class Entity {
private:
	// declare private things here e.g. class data
public:
	// declare public things here e.g. methods

	// the default constructor, where no arguments are passed
	Entity();

	// another constructor, with member initializer list
	Entity(float x, float y)
		: m_x(x), m_y(y) {}

	// a copy constructor, very useful for e.g. code optimization 
	Entity(const Entity& other);

	// a copy assignment operator overload 
	Entity& operator=(const Entity& other);

	// a move constructor 
	Entity(const Entity&& other);

	// a move assignment operator
	Entity& operator=(const Entity&& other);

	// destructor
	~Entity();
};
```

This looks like a huge amount of code to write just to define a simple class. And it is. The upside here is that all of these methods act like _hooks_, giving us very fine-grained control over the lifecycle of the objects that we instantiate. 

Furthermore, it is not strictly necessary to define and implement all of these methods, or even any of them — the compiler can and will generate default implementations for us. It is, however, dangerous to rely on the compiler's automatically generated implementation — how can one be sure that the behavior of the compiler's default implementation will match the model of _correct_ behavior that we hold? 

### Classes vs Structs

Classes are defined using either the `class` or the `struct` keyword. The only distinction between the two is that with class declared using `struct`, the default visibility of all members of the class is _public_ whereas with a class declared using `class` the default visibility is _private_. 

A further distinction between the two is the necessity for providing a constructor when we want to initialize class members. This is best articulated via an example. 

This works:

```C++
struct Entity {
	float x, y;
};
/* ... */
Entity e{1, 2};
```

Whereas, this will not:

```C++
class Entity {
	float x, y;
};
/* ... */
Entity e{1, 2};
```

### The `static` Keyword

There are three (3) primary applications of the `static` keyword in C++, only one of which is inextricably linked to classes and class definitions, but we'll cover all three here just for the sake of completeness. 

The first application is _static methods_, which are just functions defined within a class definition that do not require a class _instance_ to be invoked. 

```C++
class Entity {
private:
	float x, y;
public:
	static void Test() 
	{
		std::cout << "I am a static method" << std::endl;
	}
}
/* ... */
Entity e;
e.Test();        // this works, but compiler may complain
Entity::Test();  // preferred, no instance required / desired
```

The second application of the `static` keyword is the declaration of static variables, which means that the variable is only linked internally within the translation unit in which it is declared. That is, during the linking process, the linker is not going to "find" a statically-defined variable if it is operating outside of that variable's translation unit. Statically-defined variables are useful, for instance, when defining global variables because they allow us to avoid linking errors (duplicate symbols). 

The third application of the `static` keyword is for the definition of _local static_ variables. These variables are essentially long-lived variables in the sense that they are able to "outlive" the scope in which they are defined. It is like lifting the local variable to a global, without exposing it outside of the local scope. 

```C++
void func() 
{
	static int i = 0;
	std::cout << i << std::endl;
	++i;
}
/* ... */
func(); // 0
func(); // 1
```

Personally I hate the idea of local statics. They introduce needless local state that adds to the complexity of our program and degrades our ability to reason about the code we have written. No thanks. 

### Inheritance

Inheritance allows one class to declare itself a subclass of another. A subclass inherets all members of its superclass that are not marked as private. 

```C++
class Super {
private:
	int m_priv;
public:
	int m_pub;
};

class Sub : Super {
	int m_x, m_y;
	// sub also has member m_pub, but NOT m_priv, inhereted from Super
};
```

It is important to note here that inheritance, or more formally _implementation inheritance_ is now considered a largely obsolete programming practice — one that should not be implemented in new projects. For instance, newer languages with support for object-oriented design patterns have no support for implementation inheritance. The primary issue is that member inheritance yields code that is often difficult to reason about. 

What, then, is the preferred method for combining the functionality of multiple classes? Before we get to that, we need to cover some of the constructs utilized in interface design and implementation. 

### Interfaces

We have already seen basic implementation inheritance above. In addition to this, we need several other constructs to completely define an _interface_. 

_Virtual methods_ are simply methods marked with the `virtual` keyword in a superclass in the event that we want to allow subclasses of this superclass to override these methods. Accordingly, methods in the subclass that override the virtual in the superclass are marked with the `override` keyword. 

```C++
class Super {
public:
    virtual void print() {};
};

class Sub : Super {
public:
    void print() override {};
};
```

Taking this one step further, we could make a method in the superclass a _pure virtual method_ by defining it with `=0` after the method header. This denotes that any subclass of this superclass must supply an override for this method. One cannot instantiate a class with any pure virtual methods. Such classes are called _abstract classes_ or _pure virtual classes_.

```C++
class Super {
public:
    virtual void print() = 0;
};

class Sub : Super {
public:
    void print() override {};
};
```

Note that it is also good practice to define a _virtual destructor_ in the superclass to ensure that the deriving class' destructor is called properly during deallocation. This is important in scenarios similar to the following snippet:

```C++
class Super {
public:
    Super(){}
    ~Super() {}
};

class Sub : public Super {
public:
    Sub() {}
    ~Sub() {}
};

// the subclass destructor will not be called on delete, 
// unless the superclass destructor is marked virtual
Super *super = new Sub;
``` 

With these constructs defined, the definition and implementation of an interface is straightforward: to define an interface, create a pure virtual superclass, to implement an interface, create a subclass that derives from this pure virtual superclass.

### Object Composition

A more robust method of combining the functionality encapsulated in multiple classes is through object composition.  
