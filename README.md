# WFCpp

A modern C++ library for image synthesis using Max Gumin's Wave Function Collapse algorithm

Dependencies:
- A C++20 compiler
- CMake >=3.5 build system
- Doxygen documentation generator
- [LCov](https://ltp.sourceforge.net/coverage/lcov.php) extension to gcov coverage tester


To build (library, documentation, and tests) assumming the root directory is the working directory:
```bash
cmake --build ./build --config Debug --target all -- && make
```

To run tests and get coverage:
```bash
cd build/test
./main.exe && make coverage
```

To-do: put the individual build target commands for each of the demo, tests, library, and documentation in the readme.
