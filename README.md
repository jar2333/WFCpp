# WFCpp

A modern C++ library for image synthesis using Max Gumin's Wave Function Collapse algorithm

Dependencies:
- A C++20 compiler
- CMake >=3.5 build system
- Doxygen documentation generator
- [LCov](https://ltp.sourceforge.net/coverage/lcov.php) extension to gcov coverage tester


To build (library, documentation, and tests):
```bash
cmake --build ./build --config Debug --target all -j 4 -- && make
```

To run tests and get coverage:
```bash
cd build/test
./main.exe && make coverage
```

To-do: put the build targets for each of the tests, library, and documentation in the readme.