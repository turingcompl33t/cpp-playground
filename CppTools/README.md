## C++ Development Tools

Various C++-specific tools to improve both the development experience and code quality.

### Clang Powertools

Available on Windows as a VS extension.

### Clang Format

Available on Windows as a VS extension.

### LLVM for Windows

Download LLVM for Windows [here](https://releases.llvm.org/download.html).

### Cppcheck

Download Cppcheck for Windows [here](http://cppcheck.sourceforge.net/).

The VS extension for for Cppcheck is available [here](https://github.com/VioletGiraffe/cppcheck-vs-addin/releases/tag/1.3.6), but currently only supports VS 2015 and VS 2017.

You can download the tool and invoke it from the commandline on your projects in the following manner:

```
cppcheck.exe --enable=all --suppress=missingIncludeSystem .
```

- `enable=all` enables all checks
- `--suppress=missingIncludeSystem` allows the static analysis to continue even though cppcheck is unable to find a referenced system header file; it appears that the tool is currenly abysmal at locating even the most common headers.