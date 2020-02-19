## C++ Playground

Exploring C++ features, new and old.

### External Libraries

Some of the examples in this repository make use of the following external C++ libraries:
- Boost
- Catch
- {fmt}

Building and utilizing these libraries each involve their own set of "gotchas" - below I have attempted to record make note of these in order to simplify recreating the programs in this repository.

#### Boost

Get up and running with the Boost libraries by following the procedure below:

- Download the latest Boost release from the [Boost website](https://www.boost.org/) and extract the contents of the archive your desired location
- Alternatively, clone the [Boost metarepo](https://github.com/boostorg/boost) recursively to your desired location (e.g. `git clone --recursive ...`)
- Build the Boost libraries; navigate to the top-level directory of the extracted Boost archive and run:
    - `bootstrap`: bootstrap the Boost build system
    - `.\b2` OR `.\b2 --build-type=complete`: build Boost libraries; the latter version of the second command is necessary if you plan to statically link with Boost; the build process will take some time
    - `.\b2 headers`: build just the Boost headers
- Modify the compiler's include path to include the base directory for the Boost project; when compiling from the command line (as the programs in this project assume) this may be accomplished via the `/I` compiler option (e.g. `/I path/to/boost`)
- Modify the linker's search path to include the directory where Boost.Build generated the build outputs during the library build (should be `/Boost/stage/lib`) via the `/LIBPATH` linker option (e.g. `/link /LIBPATH:path/to/boost/stage/lib`)
- If your compiler supports auto-linking (like MSVC) then this is all that is required as the linker automatically selects the correct library against which to link and resolves it for us (i.e. there is no need to specify the name of the library we want to link against via something like a `#pragma comment()`)

As a final note, Intellisense support is extremely helpful when working with Boost (because the set of libraries is so massive). If editing in VS Code, one may enable Intellisense support for included Boost headers by editing the _c\_cpp\_properties.json_ file that is created in the _.vscode/_ directory automatically when a new workspace is created (e.g. via `code .`); just add an entry to the `includePath` property under a particular configuration that points to the top-level Boost directory.

#### Catch

Getting up and running with Catch is extremely simple:

- Download the header file that comprises Catch from the link available on the [Catch2 Github repository](https://github.com/catchorg/Catch2) page
- Place the downloaded header in your preferred location
- Modify the compiler's include path to include the directory where the header is located; when compiling from the command line (as the programs in this project assume) this may be accomplished via the `/I` compiler option (e.g. `/I path/to/catch`)
- Include the `catch.hpp` header
- No linking setup required 

As with Boost, enable Intellisense support for Catch by adding the path to the directory where the Catch header is located to the _c\_cpp\_properties.json_ configuration file (if editing in VS Code).

#### {fmt}

Getting up and running with the {fmt} library is still relatively straightforward, but requires a bit more care than setting up Catch:

- Clone the project's [Github repository](https://github.com/fmtlib/fmt)
- Modify the compiler's include path to include the `include` directory under the top-level project directory; when compiling from the command line (as the programs in this project assume) this may be accomplished via the `/I` compiler option (e.g. `/I path/to/fmt/include`)
- Define the header-only macro (i.e. `#define FMT_HEADER_ONLY`); it is important that this definition is placed above the following includes
- Include the `fmt/core.h`, `fmt/format.h`, and `fmt/format-inl.h` header files
- No linking setup required

As before, enable Intellisense support by editing the _c\_cpp\_properties.json_ configuration file.

### References 

- _C++ Crash Course_ by Josh Lospinoso
- _Effective Modern C++_ by Scott Meyers
- _C++ Concurrency in Action, Second Edition_ by Anthony Williams
- [C++20 Standard Working Draft](LocalResources/CppStd.pdf)
