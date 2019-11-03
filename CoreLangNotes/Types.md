## Types in C++

The C++ type system is one of the primary features that makes the language powerful and expressive. 

### Integral Types

There are four (4) standard sizes of integral types:

- `short int` or `short`
- `int` 
- `long int` or `long`
- `long long int` or `long long`

Each of these distinct sizes may be `signed` (default) or `unsigned`. 

We can achieve integral types of a known, specific size using the `<cstdint>` library:

- `int8_t` and `uint8_t`
- `int16_t` and `uint16_t`
- `int32_t` and `uint32_t`
- `int64_t` and `uint64_t`

When we specify an integer literal such as `10` (decimal), `0b1011` (binary), `0123` (octal), or `0x45` (hexadecimal), the type of the resulting value is one of `int`, `long`, or `long long` by default. However, we may also directly specify the type (and thus the size of the result) using suffixes on the integer literal:

- `l` or `ul` for signed and unsigned longs
- `ll` or `ull` for signed and unsigned long longs

### Floating Point Types

Floating point numbers in C++ offer three (3) levels of precision:

- `float` for single precision
- `double` for double precision
- `long double` for extended precision

As with integral types, floating point types also support suffixes that allow us to directly specify the type of the resulting value when working with floating point literals (type `double` by default):

- `f` for float
- `l` for long double

### Character Types

There are six (6) distinct character types supported by C++:

- `char` default, may be signed or unsigned 
- `char16_t` fixed width, 16 bits
- `char32_t` fixed width, 32 bits
- `signed char` like `char` but always signed
- `unsigned char` like `char` but always unsigned
- `wchar_t` wide character, always able to handle the largest character set

### Enumeration Types

C++ supports both _scoped_ and _unscoped_ enumeration types. If you are coming from a background in C, then _unscoped_ enumerations are already familiar:

```C
enum Color {
	Red, 
	Green, 
	Blue
};
...
Color c = Red;
```

C++ maintains the ability to use _unscoped_ enumerations for backwords compatibility, but we should prefer to use the safer _scoped_ enumeration whenever possible:

```C++
enum class Color {
	Red, 
	Green, 
	Blue
};
...
Color c = Color::Red;
```

All enumeration types are backed by integral types, under the hood. We can specify the size of the integral type we want to use to back our enumeration. For example, instead of using the default size (e.g. 4 bytes for `int` on 64-bit machine) we can use a single-byte integral type to back our enumeration:

```C++
enum class Color : unsigned short {
	Red,
	Green, 
	Blue
}
```

### Class Types

Classes, defined using either the `struct` or `class` keywords, are obviously a major part of C++. As such, they are given their own subsection. 

### Union Types

Union types still exist in C++, again likely for backwards-compatibility with C. Avoid at all costs. 

### User Defined Literals

The `<chrono>` header provides a number of good examples of user defined literals. For instance, we can specify a duration as `1s` to denote "1 second". 

### Value Categories

This subsection is nominally about types, but there is a second characteristic of expressions in C++ that is of significant importance: the _value category_ of the expression. 

Value categories in C++ have evolved over time, making them more expressive but also more complex. 

In simple terms:

- an _lvalue_ is any expression that has a name 
- an _rvalue_ is any expression that is not an _lvalue_

### The `auto` Keyword

The `auto` keyword allows us to specify that we want the compiler to automatically deduce the type of some variable, rather than requiring that we as the programmer explicitly specify the variable's type. 

Does this mean that we can just use `auto` everywhere and never worry about explicit type annotation? Obviously this is a bad general policy. However, `auto` can make our code easier to read and understand in several scenarios. 

### Type Casting and Type Punning

What tools do we have at our disposal to circumvent the C++ type system? At a high level, we have two distinct methods of casting types in C++: manual, C-style casts and C++ casts. 

The casting methods added by C++ do not actually add any functionality over C-style casts, but they do ensure that our casts more explicit which may make us think harder about whether or not we actually need to perform this cast while at the same time making it easier to grep our code for casting operations. The syntax of C++ explicit casts is relatively ugly, and perhaps this was done on purpose to discourage such deliberate circumvention of the type system. 

We can do some pretty nasty things with manual conversion. 

```C++
int   a = 10;
// reinterpret the raw byte representation of integer '10' as a floating point value
float b = *((float*)&a);
```

We can also use unions to achieve the same result. 

```C++
struct Union {
    union
    {
        int   a;
        float b;
    };
};

Union val{4};
```

We can also use C++ casts, such as `reinterpret_cast`. 

As a general rule, using braced initialization is a safer way to perform conversions between types because the compiler will warn us about narrowing conversions, whereas such warnings would be suppressed in the case of implicit conversions (braced initialization is a type of explicit conversion). For instance:

```C++
uint32_t a = 100;
uint64_t b { a };

uint32_t c { b };  // does not compile
uint32_t d = b;    // compiles!
```

### Constant Expressions: `constexpr`

As the name implies, constant expressions are expressions with a constant value, implying that they can be evaluated at compile time. We denote constant expressions with the `constexpr` modifier. 

Marking a function with `constexpr` denotes that the function can be evaluated at compile time. An important point here is that functions marked `constexpr` can only be constructed from expressions and other functions that are themselves constant expressions. 

`constexpr` may be used in other contexts as well, such as in conditional statements. 

```C++
if constexpr (/* predicate */) {
	// evaluated at compile time
} 
```

### Volatile Expressions: `volatile`

The `volatile` modifier serves as an instruction to the compiler to not optimize out any operations related to some expression.

### Type Aliases

The `using` directive can be used to define a type alias. 

```C++
using MyType = int;
``` 

On its own this is not very interesting. However, type aliasing can be applied to templated classes to provide some powerful functionality. For instance, we may fully specify all of the template arguments when defining the type alias, or we may partially apply the template in the type alias to create a new template that takes fewer template arguments. 

```C++
template <typename src, typename dst>
class SrctoDst {
    /* convert src type to dst type */
};

template <typename dst>
using InttoDst = SrctoDst<int, dst>;
```
