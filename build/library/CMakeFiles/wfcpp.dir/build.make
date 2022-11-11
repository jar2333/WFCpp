# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/elaine/cpp/WFCpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/elaine/cpp/WFCpp/build

# Include any dependencies generated for this target.
include library/CMakeFiles/wfcpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include library/CMakeFiles/wfcpp.dir/compiler_depend.make

# Include the progress variables for this target.
include library/CMakeFiles/wfcpp.dir/progress.make

# Include the compile flags for this target's objects.
include library/CMakeFiles/wfcpp.dir/flags.make

library/CMakeFiles/wfcpp.dir/src/Extractor.cpp.o: library/CMakeFiles/wfcpp.dir/flags.make
library/CMakeFiles/wfcpp.dir/src/Extractor.cpp.o: /home/elaine/cpp/WFCpp/library/src/Extractor.cpp
library/CMakeFiles/wfcpp.dir/src/Extractor.cpp.o: library/CMakeFiles/wfcpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/elaine/cpp/WFCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object library/CMakeFiles/wfcpp.dir/src/Extractor.cpp.o"
	cd /home/elaine/cpp/WFCpp/build/library && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT library/CMakeFiles/wfcpp.dir/src/Extractor.cpp.o -MF CMakeFiles/wfcpp.dir/src/Extractor.cpp.o.d -o CMakeFiles/wfcpp.dir/src/Extractor.cpp.o -c /home/elaine/cpp/WFCpp/library/src/Extractor.cpp

library/CMakeFiles/wfcpp.dir/src/Extractor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wfcpp.dir/src/Extractor.cpp.i"
	cd /home/elaine/cpp/WFCpp/build/library && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/elaine/cpp/WFCpp/library/src/Extractor.cpp > CMakeFiles/wfcpp.dir/src/Extractor.cpp.i

library/CMakeFiles/wfcpp.dir/src/Extractor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wfcpp.dir/src/Extractor.cpp.s"
	cd /home/elaine/cpp/WFCpp/build/library && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/elaine/cpp/WFCpp/library/src/Extractor.cpp -o CMakeFiles/wfcpp.dir/src/Extractor.cpp.s

library/CMakeFiles/wfcpp.dir/src/Solver.cpp.o: library/CMakeFiles/wfcpp.dir/flags.make
library/CMakeFiles/wfcpp.dir/src/Solver.cpp.o: /home/elaine/cpp/WFCpp/library/src/Solver.cpp
library/CMakeFiles/wfcpp.dir/src/Solver.cpp.o: library/CMakeFiles/wfcpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/elaine/cpp/WFCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object library/CMakeFiles/wfcpp.dir/src/Solver.cpp.o"
	cd /home/elaine/cpp/WFCpp/build/library && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT library/CMakeFiles/wfcpp.dir/src/Solver.cpp.o -MF CMakeFiles/wfcpp.dir/src/Solver.cpp.o.d -o CMakeFiles/wfcpp.dir/src/Solver.cpp.o -c /home/elaine/cpp/WFCpp/library/src/Solver.cpp

library/CMakeFiles/wfcpp.dir/src/Solver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wfcpp.dir/src/Solver.cpp.i"
	cd /home/elaine/cpp/WFCpp/build/library && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/elaine/cpp/WFCpp/library/src/Solver.cpp > CMakeFiles/wfcpp.dir/src/Solver.cpp.i

library/CMakeFiles/wfcpp.dir/src/Solver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wfcpp.dir/src/Solver.cpp.s"
	cd /home/elaine/cpp/WFCpp/build/library && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/elaine/cpp/WFCpp/library/src/Solver.cpp -o CMakeFiles/wfcpp.dir/src/Solver.cpp.s

library/CMakeFiles/wfcpp.dir/src/Synthesizer.cpp.o: library/CMakeFiles/wfcpp.dir/flags.make
library/CMakeFiles/wfcpp.dir/src/Synthesizer.cpp.o: /home/elaine/cpp/WFCpp/library/src/Synthesizer.cpp
library/CMakeFiles/wfcpp.dir/src/Synthesizer.cpp.o: library/CMakeFiles/wfcpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/elaine/cpp/WFCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object library/CMakeFiles/wfcpp.dir/src/Synthesizer.cpp.o"
	cd /home/elaine/cpp/WFCpp/build/library && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT library/CMakeFiles/wfcpp.dir/src/Synthesizer.cpp.o -MF CMakeFiles/wfcpp.dir/src/Synthesizer.cpp.o.d -o CMakeFiles/wfcpp.dir/src/Synthesizer.cpp.o -c /home/elaine/cpp/WFCpp/library/src/Synthesizer.cpp

library/CMakeFiles/wfcpp.dir/src/Synthesizer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wfcpp.dir/src/Synthesizer.cpp.i"
	cd /home/elaine/cpp/WFCpp/build/library && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/elaine/cpp/WFCpp/library/src/Synthesizer.cpp > CMakeFiles/wfcpp.dir/src/Synthesizer.cpp.i

library/CMakeFiles/wfcpp.dir/src/Synthesizer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wfcpp.dir/src/Synthesizer.cpp.s"
	cd /home/elaine/cpp/WFCpp/build/library && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/elaine/cpp/WFCpp/library/src/Synthesizer.cpp -o CMakeFiles/wfcpp.dir/src/Synthesizer.cpp.s

# Object files for target wfcpp
wfcpp_OBJECTS = \
"CMakeFiles/wfcpp.dir/src/Extractor.cpp.o" \
"CMakeFiles/wfcpp.dir/src/Solver.cpp.o" \
"CMakeFiles/wfcpp.dir/src/Synthesizer.cpp.o"

# External object files for target wfcpp
wfcpp_EXTERNAL_OBJECTS =

library/libwfcpp.a: library/CMakeFiles/wfcpp.dir/src/Extractor.cpp.o
library/libwfcpp.a: library/CMakeFiles/wfcpp.dir/src/Solver.cpp.o
library/libwfcpp.a: library/CMakeFiles/wfcpp.dir/src/Synthesizer.cpp.o
library/libwfcpp.a: library/CMakeFiles/wfcpp.dir/build.make
library/libwfcpp.a: library/CMakeFiles/wfcpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/elaine/cpp/WFCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libwfcpp.a"
	cd /home/elaine/cpp/WFCpp/build/library && $(CMAKE_COMMAND) -P CMakeFiles/wfcpp.dir/cmake_clean_target.cmake
	cd /home/elaine/cpp/WFCpp/build/library && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wfcpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
library/CMakeFiles/wfcpp.dir/build: library/libwfcpp.a
.PHONY : library/CMakeFiles/wfcpp.dir/build

library/CMakeFiles/wfcpp.dir/clean:
	cd /home/elaine/cpp/WFCpp/build/library && $(CMAKE_COMMAND) -P CMakeFiles/wfcpp.dir/cmake_clean.cmake
.PHONY : library/CMakeFiles/wfcpp.dir/clean

library/CMakeFiles/wfcpp.dir/depend:
	cd /home/elaine/cpp/WFCpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/elaine/cpp/WFCpp /home/elaine/cpp/WFCpp/library /home/elaine/cpp/WFCpp/build /home/elaine/cpp/WFCpp/build/library /home/elaine/cpp/WFCpp/build/library/CMakeFiles/wfcpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : library/CMakeFiles/wfcpp.dir/depend

