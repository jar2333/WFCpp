# LoC

Lines of code analysis using `cloc` with a [WFC library written in C](https://github.com/ic-pcg/waveFunctionCollapse.git)

For `waveFunctionCollapse` (graphics code omitted due to no equivalent functionality in C):
```bash
$ cloc --exclude-lang=Markdown,XML,make --exclude-dir=graphics .
      21 text files.
      21 unique files.                              
       8 files ignored.

github.com/AlDanial/cloc v 1.86  T=0.02 s (627.9 files/s, 55391.2 lines/s)
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C                                7            195             94            741
C/C++ Header                     7             59             27            119
-------------------------------------------------------------------------------
SUM:                            14            254            121            860
-------------------------------------------------------------------------------
```

For `WFCpp` (external libs and documentation omitted):

```bash
$ cloc --exclude-lang=CMake --exclude-dir=lib,docs,test .
      17 text files.
      17 unique files.                              
       3 files ignored.

github.com/AlDanial/cloc v 1.86  T=0.02 s (760.0 files/s, 88367.3 lines/s)
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C++                              4            162             32            539
C/C++ Header                    11            169            447            395
-------------------------------------------------------------------------------
SUM:                            15            331            479            934
-------------------------------------------------------------------------------
```

Our library is written in C++, including modern features, separation of concerns, and well-defined classes. Despite this, our code is only 74 lines longer, and our file count is bigger by 1. Our code is also much more extensively documented, using Doxygen to generate an API manual.