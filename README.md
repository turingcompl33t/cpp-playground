## C++ Playground

Exploring C++ features, new and old.

### External Libraries

Some of the examples in this repository make use of the following external C++ libraries:

- Google Benchmark
- Boost
- Catch2
- {fmt}
- Google Test / Google Mock
- Range V3

Building and utilizing these libraries each involve their own set of "gotchas" - below I have attempted to record make note of these in order to simplify recreating the programs in this repository.

### Google Benchmark

Assuming you cloned the repository recursively (i.e. with `git clone --recursive`) you have the Google Benchmark library added as a submodule. The `CMakeLists.txt` in each module directory takes care of the rest of the configuration.

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

### Google Test / Google Mock

Build Google Test / Google Mock (the GMock target automatically builds the GTest target) with CMake.

```
cd _Deps/GoogleTest
mkdir build && cd build
cmake .. -G Ninja
ninja
```

This build produces four (4) distinct static libraries for use by our applications:

- `gmockd.lib`: debug version of the GMock library
- `gmock_maind.lib`: debug version of the GMock library with support for automatic entry point generation
- `gtestd.lib`: debug version of the GTest library
- `gtest_maind.lib`: debug version of the GTest library with support for automatic entry point generation

Which of course implies that the default build (invoked above) generates the debug versions of the Google Test and Google Mock libraries. Obviously you will need to alter this process slightly if you require the release versions.

Generating the debug versions of the Google Test and Google Mock libraries has a few implications for how we need to compile and link our applications that make use of these libraries:

- If we don't specify a runtime library explicitly at compile time, we link with the static release version of the runtime (equivalent to specifying `/MT`). However, the debug versions of Google Test and Google Mock link with the static debug version of the runtime. Therefore, if we attempt to link our default-generated object file with the debug Google Test / Google Mock libraries, we will get a nasty runtime library mismatch. Fix this by specifying `/MTd` to link with the static debug version of the runtime.
- Changing the runtime version in this way also implicitly changes our iterator debug level(`_ITERATOR_DEBUG_LEVEL`) to 2, which matches the version defined by the static debug versions of the libraries.

The remaining steps for getting started with Google Test / Google Mock are standard:

- Add the public include directory to the compiler's include path
- Add the directory in which the static libraries were generated to the linker's search path
- Link against the appropriate version of the library for your needs

Thus far I have been unsuccessful in getting an application in which the entry point is provided by GTest to link. I always recieve the "entry point must be defined" linker error, but if I specify `/SUBSYSTEM:CONSOLE` in an attempt to tell the linker to look for the `main()` provided by GTest, I suddenly get unresolved externals for the application object file.

### Range V3

TODO

### Reading List

- [Fluent C++ Blog](https://www.fluentcpp.com/)
- [A Visitor's Guide to C++ Allocators](https://rawgit.com/google/cxx-std-draft/allocator-paper/allocator_user_guide.html)

### References 

- _C++ Crash Course_ by Josh Lospinoso
- _Effective Modern C++_ by Scott Meyers
- _C++ Concurrency in Action, Second Edition_ by Anthony Williams
- [C++20 Standard Working Draft](LocalResources/CppStd.pdf)
