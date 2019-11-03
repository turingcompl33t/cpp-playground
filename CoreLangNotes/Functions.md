## Functions, Methods, and Macros in C++

Selected topics in the implementation and use of functions, methods, and macros. 

### Function Modifiers

Prefix modifiers include:

- `static` indicates this function will not be linked outside of the translation unit in which it is defined, or, if used with a class method, indicates the method is defined not for instances of the class but for the class itself
- `virtual` indicates a method may be overridden by deriving classes
- `inline` indicates the function will be inlined at compile time
- `constexpr` indicates the function may be evaluated at compile time
- `[[noreturn]]` indicates that this function does not return, helps compiler with optimization

Suffix modifiers include:

- `noexcept` indicates the function will never throw exception
- `const` indicates a method will not modify class members
- `final` indicates a method cannot be overridden by deriving classes
- `override` indicates a method is overriding a virtual method defining in the parent class
- `volatile` indicates a function may be invoked on `volatile` objects

### Function Pointers

I am never able to remember the syntax for declaring and later invoking a function pointer, but it really isn't that bad. 

```C++
int compute(int a, int b)
{
    return a + b;
}

int (*funcptr)(int, int) = compute;

auto res = funcptr(1, 2);  // 3
``` 

### Lambdas

The syntax for lambdas in C++ is as follows:

```C++
auto fn = [](int a, int b) -> int {return a + b; };
fn(1, 2);   // 3
```

We can use lambdas to implement a crude version of the classic `map` function. 

```C++
template <typename F>
void map(F fn, int *src, int *dst, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        dst[i] = fn(src[i]);
    }
}

int src[] = {1, 2, 3, 4, 5};
int dst[5];
map([](int n){return n+1;}, src, dst, 5);
```

More comprehensive information regarding lambdas is available [here](https://en.cppreference.com/w/cpp/language/lambda).

### Generic Callables: `std::function`

The `std::function` class gives us a generic wrapper around all callable types including functions, callable objects, and lambdas. 

When should we use raw C-style function pointers and when should we prefer the C++ library's `std::function`?

### Variadic Functions

Variadic functions accept an unspecified number of arguments. The API for interacting with variadic functions leaves much to be desired. 

Variadic templates are a more modern way of defining and using functions that accept a variable number of arguments. Such templated functions do not allow us to index the collection of arguments directly, but instead require us to recursively strip off each argument the variadic function in repeated recursive calls — reminiscent of pattern matching in Haskell. 

Fold expressions are related to variadic functions and variadic templates in that they can make it far easier to perform the computation we desire within a variadic function. 

```C++
template <typename... T>
int sum(T... args)
{
	// the fold expression
    return (... + args);
}

auto s = sum(1, 2, 3, 4, 5);
```

### Leading vs Trailing Return Types

I have also seen this referred to as _East End Functions_ vs _West End Functions_. The former naming convention follows the C++ standard, while I find the latter more compelling. 

```C++
// west end
int sum(int a, int b)
{
	return a + b;
}

// east end
auto sum(int a, int b) -> int
{
	return a + b;
}
```

The difference in functionality is nil, however I find the east end function declaration superior to its west end counterpart for a number of reasons. Most importantly, it standardizes the location of the function name as a source code file is scanned vertically, making it easier to identify (what I consider to be) the most important piece of information in the declaration. In the above example the difference is minimal because `int` is a simple type; the real benefit becomes clear when we are faced with more complex return types, which is common when dealing with container types (for instance). 

Furthermore, I am biased towards the east end syntax because it bears a greater similarity to the syntax used by functional languages like Haskell:

```Haskell
sum :: Int -> Int -> Int
sum a b = a + b
```

### Dealing with Multiple Return Types

We'll use a simple case study for this section. In a language like Python that is not statically typed, we can do things like this:

```Python
def compute():
	str1 = "hello"
	str2 = "world"
	return (str1, str2)
```

How can we achieve something similar in C++?

**Option 1:** Make the return type `void` and pass variables of arbitrary type (by reference) to the function, writing them within the body of the function once we have performed the desired computation. 

```C++
void compute(std::string &str1, std::string& str2)
{
	str1 = "hello";
	str2 = "world";
}

std::string s1, s2;
compute(s1, s2);
```

How does this work? In the outer scope where `s1` and `s2` are declared, their size is not specified. Thus, when we do the assignment within the body of the `compute()` function, there must be some dynamic memory allocation and copying that occurs. 

**Option 2:** Do the same thing with raw pointers instead. 

```C++
void compute(std::string *str1, std::string *str2)
{
	*str1 = "hello";
	*str2 = "world";
}

std::string s1, s2;
compute(&s1, &s2);
```

**Option 3:** Use an array. 

```C++
std::string *compute()
{	
	return new std::string[] { "hello", "world" };
}

auto res = compute();
```

We can easily generalize this solution to an arbitrary number of return values using `std::vector`, at the cost of additional memory allocation (and possibly performance).

**Option 4:** Using tuples. 

```C++
std::tuple<std::string, std::string> compute()
{
	return std::make_pair("hello", "world");
}

auto res = compute();
std::string s1 = std::get<0>(res);
std::string s2 = std::get<1>(res);
``` 

The syntax for tuples in C++ is honestly disgusting. 

**Option 5:** Using a Structure. 

```C++
struct Pair {
	std::string str1;
	std::string str2;
};

Pair compute()
{
	return { "hello", "world" };
}

auto res = compute();
std::string s1 = res.str1;
std::string s2 = res.str2; 
```

In contrast to the previous option with tuples, this solution using `struct` actually looks quite clean. Hell, the body of `compute()`  almost makes it appear we are in the wild west, writing JavaScript.

We can make this solution even more concise using _structured bindings_, a C++17 language feature. 

```C++

struct Pair {
    std::string str1;
    std::string str2;
};

Pair compute()
{
    return { "hello", "world" };
}

// decomposition declaration
auto [s1, s2] = compute();
```

### Preprocessor Macros

Preprocessor macros simply perform direct textual substitution prior to program compilation. 

Macros are useful for conditional code inclusion / exclusion based on preprocessor options that we can set at compile time. 
