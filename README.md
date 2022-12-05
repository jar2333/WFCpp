# WFCpp

A modern C++ library for image synthesis using Max Gumin's Wave Function Collapse algorithm

Dependencies:
- A C++20 compiler (tested on gcc version 10.2.1 20210110 , Debian 10.2.1-6)
- CMake >=3.5 build system
- Doxygen documentation generator
- [LCov](https://ltp.sourceforge.net/coverage/lcov.php) extension to gcov coverage tester


To build (library, documentation, and tests) assumming the root directory is the working directory:
```bash
cmake --build ./build --config Debug --target all --
```
the `--config Debug` should be omitted in release, as it enables flags related to coverage testing and disables optimization.

A list of all targets that can be used instead of `all`
- `wfcpp` to compile WFCpp as a static library (part of `all`).
- `main.exe` to compile test executable (part of `all`).
- `doc` to build Doxygen documentation for WFCpp (part of `all`).
- `coverage` to build LCov coverage report for test executable (running of test executable required beforehand).
- `run` to run test executable (IO not possible, manual run preferred).
- `EasyBMP` to compile EasyBMP as a static library (part of `all`).
- `lodepng` to compile lodepng as a static library (part of `all`).

Alternative way to run tests and build coverage report:
```bash
cd build
make run
make coverage
```
`make run` runs the test program, and `make coverage` builds the coverage report based on the last test run.
