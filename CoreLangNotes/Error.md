## Error Handling in C++

How do we handle error conditions?

Return codes and exceptions are complementary methods for handling errors — we do not have to choose to use one or the other when writing our program, but rather we should apply one or the other based on the particular situation in which an error may arise. 

### Return Codes

If the error is recoverable, and can be handled locally, use a return code to signify the error condition. 

What exactly does "locally" mean here? How "local" are we talking? A single level caller-callee functional relationship? What if the call stack is _n_ levels deep? Do we still want to propogate the error all the way up the stack to some function that can actually handle it? 

### Exceptions

Kurt Guntheroth in _Optimized C++_: 

"use of exception handling leads to programs that are faster when they execute normally, and better behaved when they fail."

We can throw an exception like so:

```C++
void error()
{
	throw std::runtime_error {"big bad error"};
}
```

An thrown exception that has yet to be caught by some handler is said to be _in flight_. 

Here, we use the `std::exception` class, defined for us in `<stdexcept>`. There are two main subclasses of the `std::except` class that we are concerned with:

- the `logic_error` subclass
- the `runtime_error` subclass

Each of these subclasses themselves possess (contain?) numerous subclasses that can help to make throwing and catching an exception more granular, thus making our error handling more informative (or hopelessly complex and verbose). 

_User-Defined Exceptions_

In addition to these exception types defined in `<stdexcept>`, we may create our own user-defined exceptions. Typically these execptions still inheret from `std::exception`, which is useful because they inheret methods like `get()`. 

_Non-throwing Functions_.

We can specify that functions cannot possibly throw an exception with the `noexcept` keyword by decorating the function declaration in much the same way we would to declare a constant method. 

```C++
int sum(int a, int b) noexcept 
{
	return a + b; 
}
```