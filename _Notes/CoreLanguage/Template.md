## Templates in C++

Coming from a background in C, encoutering C++ templates for the first time can be an unnerving or frustrating experience, depending on one's constitution and appetite for new challenges. Template syntax looks messy and foreboding and we were doing just fine without them, so why bother going to all this trouble? My answer to this query is twofold: templates are not all that complex and, at the same time, they enable us to write significantly more succinct and expressive code. 

So what is a C++ template? Templates are a mechanism for implementing polymorphism via metaprogramming. When we use templates, we are essentially providing a blueprint (or a template) from which the compiler will generate code for us at compile time. This is like a form of metaprogramming — we are writing code from which the compiler will generate the actual code that will be executed.  

### Templates with Functions

The simplest use case for templates is with functions and methods. 

```C++
template <typename T>
void print(T value)
{
    std::cout << value << std::endl;
}

int main() {
    print(5);
    print("hello world");
    print(5.0f);
    
    return 0;
}
```

Here we are lazy and don't actually explicitly specify the type to be injected into the template when we call the `print()` function because the compiler is able to do this for us by inferring the type from the actual parameters — a process called _template type deduction_. We may explicitly specify the injected type like so:

```C++
int main() {
    print<int>(5);
    print<std::string>("hello world");
    print<float>(5.0f);
    
    return 0;
}
```

Programming with templates allows us to implement our programs in a more generic, type-agnostic way. Obviously this is only applicable in certain situations, such as the above wherein the logic of the templated function is unchanged for a variety of supported types. The same functionality could be achieved via function overloading, but this would result in a large amount of duplicated code, and, furthermore, would significantly increase the complexity of refactoring. 

### Templates with Classes 

The following example illustrates the use of templates with classes, and also demonstrates how we may specify an arbitrary number of template arguments. 

```C++
template <typename T, int N>
class Array {
private:
	// our only class member is a raw array
	// with elements of arbitrary type, and arbitrary size
	// both of which are specified when array is instantiated
    T arr[N];
public:
    Array()
    {
        for (int i = 0; i < N; i++)
            arr[i] = 0;
    }

    int GetSize() const
    {
        return N;
    }
};

// instantiate an array like so
Array<int, 5> arr;
```

### Named Conversions

With a named conversion, we explicitly convert one type into another type, in contrast to doing so via the use of implicit coversions or constructors.

The `const_cast` named converstion can be used to remove the `const` modifier from some object such that it can be modified. This seems like a bad idea, in general. 

The `static_cast` named conversion reduces the process of an implicit cast, which is helpful because, typically, such implciit casts are nonreversible. A `static_cast` will fail if the attempted conversion is not well defined. 

The `reinterpret_cast` named conversion allows us to interpret arbitrary memory addresses as any type that we choose. Powerful, but dangerous.

### Templates and Type Safety

What happens if we specify a templated function with implicit invariants that must be satisfied in order for the function to be well-defined? Consider the following example:

```C++
template <typename T>
void mul(T a, T b)
{
    return a * b;
}
```

The function `mul` implicitly requires that the template type parameter `T` supports the binary operation `*`. This template function works fine for types like `int` and `float`, but what happens if we call the templated function with actual parameters that do not support the `*` operation?

```C++
mul("hello", "world");
```

In this case, the type `const char *` does not support multiplication, so the compiler complains and fails. This is ok because it saves us from a runtime error, but is there a way to make these implicit invariants explicit and avoid compile-time blowups? 

### Concepts

The language feature introduced to support template parameter validation is called _concepts_. Concepts are themselves templates that allow us to validate type parameters — they evaluate to a boolean `true` or `false`, denoting whether the type parameters meet all of the requirements specified by the concept predicate. 

How do we evaluate the characteristics of types in C++? We can defined some checks ourselves, or we can use the `<type_traits>` header that is part of the standard library. 

For more flexibility in limiting the set of valid template arguments that may be injected into a template, concepts may also contain _requirements_ which are simply ad hoc predicates that we specify the template arguments must satisfy. 

```C++
// define a concept
template <typename T>
concept bool my_concept() {
    std::is_integral<T>::value   // example: T must be integral type 
    && requires(T a, T b) {
        // body of requires expression, 
        // syntactic requirements on type T
        { a == b } -> bool       // example: == operator applied to a and b of type T must return bool
        { b == a } -> bool 
    }
}
```

Concepts are (at least somewhat) analogous to the concept of typeclasses in Haskell. The concept guarantees that any instantiation of the templated function that utilizes that concept will behave in certain, expected ways. 

To use a concept that we have defined, we simply substitute it for the `typename` specifier in the template parameters list. 

```C++
template <my_concept T>
void func()
{
    // rest assured that e.g. T is integral and T support == operator
}
```

What is the upside of this? After all, we still have to wait until compile time to discover if an error has been made in the use of some templated function. The benefit, however, is that now the error that is produced as a result of misuse of a templated function is far more comprehensible and instructive. 

I am convinced that concepts will prove to be an incredibly useful resource in C++ programming. The C++ standard library already defines a number of useful concepts that we can drop into our templated code. 

More information is available regarding the [technical specification](https://en.cppreference.com/w/cpp/experimental/constraints) of concepts as well as their presence in the [standard library](https://en.cppreference.com/w/cpp/concepts). 

### Lightweight Concepts: `static_assert`

Concepts are an awesome language feature. However, they are fairly heavyweight and moreover, only supported by a handful of compilers / versions. What can we use to validate templates in the interim? Enter `static_assert`. 

Use of `static_assert` proceeds exactly how one might expect: simply drop one or more `static_assert` expressions into the body of the templated function itself to enforce arbitrary constraints on the template parameters. 

```C++
template <typename T>
T mul(T a, T b)
{
    static_assert(std::is_arithmetic<T>(), "type must be arithmetic");
    return a * b;
}

auto a = mul(3, 5);              // succeeds
auto b = mul("hello", "world");  // fails!
```

### Where Should Templates be Defined?

If you look at the source code for any reputable project that utilizes templates, you are likely to see that the templated functions themselves are implemented entirely in header files. This goes against the typical grain of declaring functions in headers and then implementing them in the associated `.cpp` file, so what is the deal here? The reason this is done is because the compiler must have access to the complete template itself within the same translation unit in order to generate the code that results from use of that template. Thus, we cannot wait for the linker to resolve symbols for us in the case of programming with templates. 
