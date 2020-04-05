## Setting Up a C++ Development Environment

### Precompiled Headers

C++ projects have notoriously long build times. For instance, it is said that the Go programming language was conceived while waiting for a C++ program to compile. Precompiled headers can help us here by significantly reducing the amount of time taken in the preprocessing stage of program compilation.

Because the preprocessor performs simple substitution and file injection, projects that use a large number of `#include` directives (such as for standard library headers) suffer greatly from amount of build time taken up by the preprocessor as it reads file contents ands writes them in to the file that has included them. I/O is slow. 
 