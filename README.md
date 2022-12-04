# WFCpp

A modern C++ library for image synthesis using Max Gumin's Wave Function Collapse algorithm

Dependencies:
- A C++20 compiler (tested on gcc version 10.2.1 20210110 , Debian 10.2.1-6)
- CMake >=3.5 build system
- Doxygen documentation generator
- [LCov](https://ltp.sourceforge.net/coverage/lcov.php) extension to gcov coverage tester


To build (library, documentation, and tests):
```bash
cmake --build ./build --config Debug --target all --
```
the `--config Debug` should be omitted in release, as it enables flags related to coverage testing and disables optimization.

To run tests and build coverage:
```bash
cd build
make run
make coverage
```

`make run` runs the test program, and `make coverage` builds the coverage report based on the last test run.

To-do: put the individual build target commands for each of the demo, tests, library, and documentation in the readme.
