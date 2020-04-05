## Standard Template Library: Basics

Notes from Stephan T. Lavavej's Channel9 STL series.

### Introduction and Sequence Containers

What is a standard library?
	- the library of code that comes with every copy of the compiler

Many of the advanced features in the Core C++ Language are there primarily to support implementation of the standard library 
	- and specifically the STL

The STL is incredibly powerful
    - but it requires extensive knowledge in order to effectively navigate it

ASIDE: The STL is a library, NOT a framework
	- small bits of reusable code
	- relatively unopinionated
	- a library for "general computation"
	- has things that every program / programmer can benefit from

High level STL structure
	- containers
	- iterators
	- algorithms
	- iterators serve as a bridge, an interface between containers and algorithms

Why is the STL structured this way?
	- modularity avoids "implementation explosion"
	- iterators abstract away the idea of individual elements of a container, so algorithms can be easily templated on iterators and work across all containers

std::vector
	- the workhorse of STL containers
	- vector is a "sequence container"
		○ sequence containers care about the order of the elements they contain
	- std::vector uses a geometric reallocation strategy under the hood
		○ amortized constant time for insertions (push_back)
	- to a certain extent, containers like std::vector will try to imitate raw, C-style containers
		○ e.g. overload operator[] to allow subscripting and assignment (std::map)
	
STL iterators
	- an abstraction over "pointers to individual container elements"
	- the end() iterator points to one element past the end of the container
	    - inclusive / exclusive ranges i.e. [x, y)
	    - why?
	    - makes empty ranges natural, imitates the way raw C-style arrays work
	    - IMPORTANT TO REMEMBER THIS
	- "iterators are an imitation of pointers"
	    - "they are a generalization of pointers"
	    - can be incremented, decremented, dereferenced, etc.
	    - accomplish this via operator overloading
	- this is enormously powerful
	    - allows us to ignore implementation, focus on the important logic of the program

STL algorithms
	- 105 algorithms available in STL
	- customizable through functors
	    - functions
        - function objects 

### Associative Containers

In part 1: sequence containers
	- std::vector
	- std::list
	- std::deque
	- std::forwardlist

STL associative containers -> map a key to a value
	- std::map
	- std::multimap
	- std::set
	- std::multiset

And in newer versions of STL, we got:
	- std::unordered_map
	- std::unordered_multimap
	- std::unordered_set
	- std::unordered_multiset

In addition to sequence and associative containers, STL also includes several "container adapters"
	- std::stack
	- std::queue
	- std::priority_queue
	- "like a layer of abstraction over the other containers"

std::map
	- the basic, goto data structure to associate keys with values
	- std::map, by default, is ordered
	    - it automatically keeps its keys sorted
	- iterate over a map the same way we iterate over a sequence container like std::vector
	    - the POWER of the STL
	- when we iterate over a std::map, the elements we get back are a pair<const key, value>
	    - notice that the key is const because we cannot modify a key while iterating
	    - this would lead to catastrophe

How is std::map implemented?
	- a balanced binary tree -> red-black tree
	- each node in tree is pair<key, value>

ASIDE: notice that operator[] functions very differently for std::map than it does for e.g. std::vector
	- operator[] is not const because it can modify the map
	- thus if we want to READ ONLY from a map passed by const reference, need to use the find() method, using operator[] will fail to compile
	- among associative containers, std::map is special because it is the only one that overloads operator[]

std::set
	- an automatically sorted container that enforces uniqueness 
	- but does not actually associate a key to a value
	    - why is it considered "associative"..?
		
std::unordered_map
	- same interface as std::map
	- very different underlying implementation
	    - a hashtable under the hood
	- very different performance guarantees than std::map
	- we need to know these guarantees when selecting a data structure!

ASIDE: sequence containers and the erase-remove idiom
	- motivation: removing some subset of vector elements, based on some predicate
	- the algorithm:
	    1. remove -> std::remove algorithm (remove_if)
	    2. erase -> vector::erase() member function
    - if we do this incorrectly, we get quadratic time for the operation, rather than linear!

### Smart Pointers

ASIDE: homework assignment from Part 2
	- writing a template wrapper to remove elements via standard interface from all STL containers
	    - never have to think about it again!
	- why is this complex?
	    - different classes of containers have different effective idioms for removing elements
	    - 3 families:
		    - "vectorlike"
		    - "listlike"
		    - "associative"
	- ASIDE: use "detail" namespace to denote "library internal"
	- gentle use of template metaprogramming

The high level lesson from parts 1 + 2: use STL containers to manage state
	- don't use operator new[] and operator delete[]
	- because STL containers handle state management for us

Analogously: use std::shared_ptr and std::unique_ptr rather than operator new and operator delete

std::unique_ptr
	- the unique owner of some dynamically allocated object 
	- imitates a raw pointer via operator overloads
	- unique_ptr is powered by rvalue references
	    - not copyable, but is movable

std::shared_ptr
	- combine with helper function std::make_shared()
	    - never call operator new
	    - std::make_shared() is both convenient and more efficient because of underlying allocation strategy
	- a "reference counted pointer"

std::weak_ptr
	- an advanced version of std::shared_ptr
    - weak references 

### Algorithms and Functors

Why STL algorithms?
	- performant
	- convenient
	- self-documenting -> wetware optimized!

2 large classes of algorithms on sequences:
	- non-modifying
	- mutating

STL algorithms and modularity
	- templated on iterators

CONCEPT: STL and straight through code
	- code without any explicit control flow constructs
	    - e.g. no if, while, for, etc.
	- very easy to reason about
	- STL enables this and we should strive for it
	- Sean Parent -> "no raw loops"

At the highest level, the STL talks about functors
	- functions -> the typical free functions we know and love
	- function objects a class overriding operator()
	    - handwritten classes
	    - lambdas

The big distinction: functions should not store any state between calls while function objects have some internal state associated with them
	- functions that have internal state are evil
	    - e.g. globals, local statics

Why are lambdas more efficient?
	- candidates for inlining by compiler
	- much more commonly inlined by compiler than a call through a function pointer
	    - because this is much harder for the compiler to reason about 

ASIDE: the back_inserter "insert iterator" for std::vector
	- back_inserter returns an iterator
	- allows us to do safe copies from one container to another
	    - e.g. from raw array to std::vector

UPSIDE: there are multiple, valid idioms available for copying some source container to some other destination container contents

STL uses "strict weak ordering" for comparator functors 
	- if you write a custom comparator, it must behave like operator<
	- it CANNOT behave like e.g. operator<=
	- intuition: for values x, y
	    - if x == y then x comparator y must evaluate to false

ASIDE: most STL algorithms live in the <algorithm> header
	- but a couple live in <numeric>

std::transform
    - the swiss army knife of mutating algorithms

### Rvalue References and Move Semantics

The rvalue references feature enables / addresses two distinct concepts in C++
	- move semantics
	- perfect forwarding
	- able to do this because it allows us to express some concepts that we were previously unable to

lvalues vs rvalues
	- lvalue -> something that has a name
	- rvalue -> everything else
	- ask yourself the question: "can I take address-of on this thing??"

lvalues and rvalues refer to expressions
	- this is a fundamental concept

How to think about references
	- "a name for a thing, not the thing itself"
	- "not an object in its own right, just a name for an existing object"

lvalue vs rvalue references
	- lvalue: const string& cr = s + t;
	- rvalue: string&& rr = s + t;
	- ASIDE: we can only bind a temporary like this to a non-modifiable rvalue reference
	    - so the above would fail to compile?

What does std::move do?
	- converts lvalues to rvalues
	- allows us to e.g. preserve the rvalue-ness of arguments passed to functions as rvalue references
    - "std::move is the moral equivalent of a cast"

### Type Traits

How to think about templates?
	- computers only care about bits
	- early languages like B had NO type system whatsoever
	- in languages like C we introduced a type system wherein operations performed on bits declared as having some type behave differently than the same operation performed on bits declared as having a different type
	- in language like C++, we introduce classes and objects
	    - "user defined types"
	- templates simply add another level of abstraction on top of this system
	    - they exist at a level above individual classes

Type traits -> allow us to inspect types at compile time and make decisions based on this information
	- using type traits is what enables template metaprogramming

Basic type traits usage: unary type trait queries
	- use case ex: specialize based on std::is_integral or not
	- ASIDE: the "typename" keyword
	    - allows us to see through a "::" to specify "this thing is a type" because otherwise the compiler is unable to reach into this namespace and deduce this

CONCEPT: STL uses type traits extensively to write special, optimized overloads for algorithms and container operations

SFINAE = "substitution failure is not an error"
	- began life as a feature in the core language
	- compiler fails gracefully instead of throwing a hard error
	- gives us extremely fine-grained control over things that are / are not added to overload sets
    - use case: std::enable_if