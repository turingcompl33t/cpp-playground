## Memory Management in C++

### Managing the Heap

We can overload the `new` and `delete` operators to manually take control of dynamic memory allocation in our C++ programs. To do so, we must include the `<new>` header. 

We can use _placement operators_ to manually construct objects in memory locations of our choosing. 