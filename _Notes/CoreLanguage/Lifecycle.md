## Object Lifecycle in C++

Often when we hear the word _object_ in the context of programming, we think of a particular instantiation of a class — when we declare a variable whose type is user-defined (via the `struct` or `class` keyword) we are creating a new instance of the class in question. However, _objects_ refer more generally to any region of memory that has both a type and a value. 

### Scope, Linkage, and Storage Duration

### Static Storage Duration vs Dynamic Storage Duration

### Constructors and Destructors

All of the constructors for class members are invoked before the owning class' constructor is invoked. The destructor for the owning class is invoked prior to the destructors for constituent members being invoked. 

The snippet below provides an illustrative example of simple object lifecycle properties.

```C++
class Trace {
private:
    const char* const id;
public:
    explicit Trace(const char *id)
        : id{id}
    {
        std::cout << id << " constructed" << std::endl;
    }

    ~Trace()
    {
        std::cout << id << " destructed" << std::endl;
    }
};

void func()
{
    Trace c{"C"};
}

int main() {
    Trace a{"A"};

    {
        Trace b {"B"};
    }

    func();

    return 0;
}
```

When invoked, this program produces the following output:

```
A constructed
B constructed
B destructed
C constructed
C destructed
A destructed
```

### Copy Semantics

When we copy an object, we want to be sure that the copy operation behaves in a certain, predictable way; this is what we mean by _copy semantics_ — what does it mean to copy an instance of the class in question? In his book _C++ Crash Course_, Josh Lospinoso recommends framing the answer to this question in terms of the following three (3) criteria:

- Correctness: are class invariants maintained?
- Equivalence: is the copied object equivalent to the original in all of the desired ways?
- Independence: is the copied object independent of the original object? Or do they remained "linked" somehow?

There are two fundamental ways that we can copy an object:

- explicitly or implictly calling the _copy constructor_ defined for that object 
- explictly using the _copy assignment operator_ defined for that object 

We should always explicitly define the copy semantics for any class that we define. 

```C++
// here we specify that the default copy constructor is fine
class Entity {
public:
	Entity(const Entity& other) = default;
	Entity& operator=(const Entity& other) = default;
}

// here we specify that instances of this class are not to be copied
class Entity {
public:
	Entity(const Entity& other) = delete;
	Entity& operator=(const Entity& other) = delete;
}
```

### Move Semantics 

The movement analog to copy semantics. Why would we care about movement when we can already perform copies? The primary reason is performance: copies can be wasteful in certain circumstances where we don't care about the object that is copied from. 

With a move operation we don't care about the object that is moved from, and thus we leave it in a _moved from_ state after the move operation is complete — we cannibalize it within our move operation. Following this, we can either reassing the moved-from object or simply destroy it. 

Move semantics are heavily dependent upon the value category distinction — _lvalues_ vs _rvalues_. With _lvalues_, movement is suppressed whereas it is allowed for _rvalues_. Thus, the _move constructor_ for a class appears identical to the copy constructor apart from the fact that it takes an _rvalue_ reference instead of an _lvalue_ reference. The _move assignment operator_ is analogous. 

The same rule stated above regarding explictly defining the copy constructor and the copy assignment operator applies here to the move constructor and move assignment operator as well. 


