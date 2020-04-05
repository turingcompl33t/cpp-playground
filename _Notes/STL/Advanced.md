## Standard Template Library: Advanced

Notes from Stephan T. Lavavej's Channel9 Advanced STL series.

### Type Erasure and std::shared_ptr

"The standard template library is implemented by way of equal parts magic and weirdness"
- why?
- because of the need to support anything that standard template library users can think up 

shared_ptr -> internal implementation 
- at the first level it is just a raw pointer to the owned object and another pointer to the reference counting machinery 
- ASIDE: we can also give a shared pointer a custom deleter 
- ASIDE: similarly we can give a shared pointer a custom allocator that controls how the reference counting block is allocated 
    - the shared pointer is only templated on the object type that is owned not the deleter or allocator 
- this is the difference from e.g. vector where in it is templated on a type and the allocator 
- how does a shared pointer remember all the context in which it was created without baking it into the type?
    - this is "type erasure"

How does shared pointer perform type erasure?
- virtual function calls 
- a pointer to a base class for reference counting block that is itself templated on a custom deleter and or custom allocator 

ASIDE: how is make_shared implemented without access to variadic templates 
disgusting preprocessor macros 

### Algorithm Optimizations

CASE STUDY: STL partitions
- std::partition
- std::is_partitioned 
- Introduction of a new interface for std::partition
    - i.e. ForwardIterators, BidirectionalIterators
- CONCEPT: Using a more flexible iterate are to optimize the underlying algorithm 

CASE STUDY: std::advance
- described in the concept above 

CONCEPT: using types as tags to select function overloads at compile time 
- very powerful 

CASE STUDY: std::equal
- algorithm optimization when comparing certain types 
- for example vector ranges of char, unsigned char, signed char
- this type of optimization works for any type for which value equality is equivalent to representation equality 

ASIDE: for types like doubles value equality is not equivalent to representation equality 
- e.g. +0 and -0 are considered the same value but have different representations 

CASE STUDY: std::copy

CONCEPT: these types of optimizations are a classic use case of template metaprogramming 

### MSVC and Iterator Debug Level

"Iterator Debug Level" (IDL)
- Previously referred to as 
    - SCL = Secure C++ Library
    - HID = Has Iterator Debugging

HID => Only for debug mode builds 
- debug mode correctness checks on standard template library usage 

SCL => for release mode builds 
- can also be used in debug mode 
- release mode security checks 

new releases of MSVC unify HID and SCL into the new iterator debug level options 
- IDL 0 -> nothing, "super speed mode"
- IDL 1 -> SCL
- IDL 2 -> HID

SCL Does runtime checks for things like index out of bounds violations 
- poses something like a 2X performance penalty 

CASE STUDY: catching iterator invalidation via reallocation in std::vector
- easy to see where performance hit comes from 
- for example we must maintain a linked list of all iterators into the vector 
- and we now have to acquire and release a lock to get a new iterator, destroy one, etc. 

Pragma detect mismatch and One Definition Rule (ODR) 
- The compiler and linker are enhanced to detect mismatched data structure definitions that arise as a result of using iterator debug level 

### Rvalue References and Associative Containers

RECALL: rvalue References enabled both move semantics and perfect forwarding 
- these are distinct concepts but they can interact nicely 

CASE STUDY: std::vector and push_back
- added in rvalue reference overloads to handle move semantics 

In newer updates to MSVC, lvalues will fail to bind to rvalue reference parameters with a compiler error 
- this used to not be the case 

CASE STUDY:
- std::vector v{};
- v.push_back("hello");
- which overload is called?
    - push_back(const string&);
    - push_back(string&&); 
- the first one is called, but why??
- For the mentally this overload is chosen because const char[n] type is considered an lvalue 
    - thus the rvalue reference overload is removed from the overload set 
- this issue is fixed in newer editions of the standard by not considering the "lvalue vs rvalue-ness" the source but rather the temporary that is created from it 

ASIDE: std::set, std::multiset, std::map, std::multimap Are all implemented via the same underlying data structure 
- a tree data structure that is tuned via certain parameters for each use case 
- a red-black tree

CASE STUDY: std::set
- insert std::string vs const std::string
- the insert of the constant version of the string is more efficient 
- this is fixed in newer versions of MSVC 

### Introduction to Boost

The history of the boost C library 
- it was originally written by members from the original library working group because they did not have time to work some features of the standard library into the standard itself 
- remember the standard defines the behavior of the core language and the standard library 

boost follows the same philosophy as the standard template library 
- e.g. iterators as the interface, etc.

using boost 
- most of boost is header only 
- but not all of it -> separate compiled components 

CASE STUDY: boost bimap container
- not a data structure implemented by the standard template library 

CASE STUDY: boost filesystem
- provides an STL-like iterator over a recursive directory structure 

CASE STUDY: boost scope exit
- resource management via RAII, made easy

### Generic Code Case Study: Pretty Printing

CASE STUDY: pretty printing facility for STL containers
- generic 
- extensible

CASE STUDY: using a type traits helper to determine if a given object is a container type
- using the fact that the object does or does not have a "const iterator" member as a proxy for "is a container type"

CASE STUDY: templating a container on an allocator
- rebinding machinery