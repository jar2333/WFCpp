# WFCpp

## Overview

A modern C++ library for image synthesis using Max Gumin's Wave Function Collapse algorithm

Dependencies:
- A C++20 compiler (tested on gcc version 10.2.1 20210110 , Debian 10.2.1-6)
- CMake >=3.5 build system
- Doxygen documentation generator
- [LCov](https://ltp.sourceforge.net/coverage/lcov.php) extension to gcov coverage tester\

To build (library, documentation, and test executable) assumming the root directory is the working directory:
```bash
cmake --build ./build --config Debug --target all --
```
the `--config Debug` should be omitted in release, as it enables flags related to coverage testing and disables optimization.

A list of all targets that can be used instead of `all`
- `wfcpp` to compile WFCpp as a static library (part of `all`).
- `main.exe` to compile test executable (part of `all`).
- `doc` to build Doxygen documentation for WFCpp (part of `all`).
- `run` to run test executable (IO not possible, currently okay, builds `main.exe` target).
- `coverage` to build LCov coverage report for test executable (builds `run` target).
- `EasyBMP` to compile EasyBMP as a static library (part of `all`).
- `lodepng` to compile lodepng as a static library (part of `all`).

Since it is not part of the `all` target, remember that to build the coverage report for the test executable, use:
```bash
cmake --build ./build --config Debug --target coverage
```
The `--config Debug` flag is required to build `coverage`.

To use this library, the easiest method is to use CMake for your project, and add a `target_link_libraries(<target> wfcpp)` command to your CMakeLists.txt file, where `<target>` refers to whatever executable you are compiling. CMake will ensure that you can access the library's headers by using angle bracket includes such as `#include <Solver.h>`. Alternatively, one can always build `libwfcpp.a` to link with using the `wfcpp` target, and copy-paste the library's headers to your own project. This is inadvisable but nontheless entirely possible.

## Statistics

Overall coverage rate:
  lines......: 91.0% (806 of 886 lines)
  functions..: 87.2% (102 of 117 functions)

LoC: 740
Number of functions: 107
