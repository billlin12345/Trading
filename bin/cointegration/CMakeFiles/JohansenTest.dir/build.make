# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bill/AlgoTradingQTTest/AlgoTradingTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bill/AlgoTradingQTTest/AlgoTradingTest/bin

# Include any dependencies generated for this target.
include cointegration/CMakeFiles/JohansenTest.dir/depend.make

# Include the progress variables for this target.
include cointegration/CMakeFiles/JohansenTest.dir/progress.make

# Include the compile flags for this target's objects.
include cointegration/CMakeFiles/JohansenTest.dir/flags.make

cointegration/CMakeFiles/JohansenTest.dir/JohansenTest.cpp.o: cointegration/CMakeFiles/JohansenTest.dir/flags.make
cointegration/CMakeFiles/JohansenTest.dir/JohansenTest.cpp.o: ../cointegration/JohansenTest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bill/AlgoTradingQTTest/AlgoTradingTest/bin/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object cointegration/CMakeFiles/JohansenTest.dir/JohansenTest.cpp.o"
	cd /home/bill/AlgoTradingQTTest/AlgoTradingTest/bin/cointegration && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/JohansenTest.dir/JohansenTest.cpp.o -c /home/bill/AlgoTradingQTTest/AlgoTradingTest/cointegration/JohansenTest.cpp

cointegration/CMakeFiles/JohansenTest.dir/JohansenTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JohansenTest.dir/JohansenTest.cpp.i"
	cd /home/bill/AlgoTradingQTTest/AlgoTradingTest/bin/cointegration && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bill/AlgoTradingQTTest/AlgoTradingTest/cointegration/JohansenTest.cpp > CMakeFiles/JohansenTest.dir/JohansenTest.cpp.i

cointegration/CMakeFiles/JohansenTest.dir/JohansenTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JohansenTest.dir/JohansenTest.cpp.s"
	cd /home/bill/AlgoTradingQTTest/AlgoTradingTest/bin/cointegration && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bill/AlgoTradingQTTest/AlgoTradingTest/cointegration/JohansenTest.cpp -o CMakeFiles/JohansenTest.dir/JohansenTest.cpp.s

cointegration/CMakeFiles/JohansenTest.dir/JohansenTest.cpp.o.requires:
.PHONY : cointegration/CMakeFiles/JohansenTest.dir/JohansenTest.cpp.o.requires

cointegration/CMakeFiles/JohansenTest.dir/JohansenTest.cpp.o.provides: cointegration/CMakeFiles/JohansenTest.dir/JohansenTest.cpp.o.requires
	$(MAKE) -f cointegration/CMakeFiles/JohansenTest.dir/build.make cointegration/CMakeFiles/JohansenTest.dir/JohansenTest.cpp.o.provides.build
.PHONY : cointegration/CMakeFiles/JohansenTest.dir/JohansenTest.cpp.o.provides

cointegration/CMakeFiles/JohansenTest.dir/JohansenTest.cpp.o.provides.build: cointegration/CMakeFiles/JohansenTest.dir/JohansenTest.cpp.o

cointegration/CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.o: cointegration/CMakeFiles/JohansenTest.dir/flags.make
cointegration/CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.o: ../cointegration/JohansenHelper.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bill/AlgoTradingQTTest/AlgoTradingTest/bin/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object cointegration/CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.o"
	cd /home/bill/AlgoTradingQTTest/AlgoTradingTest/bin/cointegration && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.o -c /home/bill/AlgoTradingQTTest/AlgoTradingTest/cointegration/JohansenHelper.cpp

cointegration/CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.i"
	cd /home/bill/AlgoTradingQTTest/AlgoTradingTest/bin/cointegration && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bill/AlgoTradingQTTest/AlgoTradingTest/cointegration/JohansenHelper.cpp > CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.i

cointegration/CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.s"
	cd /home/bill/AlgoTradingQTTest/AlgoTradingTest/bin/cointegration && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bill/AlgoTradingQTTest/AlgoTradingTest/cointegration/JohansenHelper.cpp -o CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.s

cointegration/CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.o.requires:
.PHONY : cointegration/CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.o.requires

cointegration/CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.o.provides: cointegration/CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.o.requires
	$(MAKE) -f cointegration/CMakeFiles/JohansenTest.dir/build.make cointegration/CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.o.provides.build
.PHONY : cointegration/CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.o.provides

cointegration/CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.o.provides.build: cointegration/CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.o

# Object files for target JohansenTest
JohansenTest_OBJECTS = \
"CMakeFiles/JohansenTest.dir/JohansenTest.cpp.o" \
"CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.o"

# External object files for target JohansenTest
JohansenTest_EXTERNAL_OBJECTS =

cointegration/JohansenTest: cointegration/CMakeFiles/JohansenTest.dir/JohansenTest.cpp.o
cointegration/JohansenTest: cointegration/CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.o
cointegration/JohansenTest: cointegration/CMakeFiles/JohansenTest.dir/build.make
cointegration/JohansenTest: cointegration/CMakeFiles/JohansenTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable JohansenTest"
	cd /home/bill/AlgoTradingQTTest/AlgoTradingTest/bin/cointegration && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/JohansenTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cointegration/CMakeFiles/JohansenTest.dir/build: cointegration/JohansenTest
.PHONY : cointegration/CMakeFiles/JohansenTest.dir/build

cointegration/CMakeFiles/JohansenTest.dir/requires: cointegration/CMakeFiles/JohansenTest.dir/JohansenTest.cpp.o.requires
cointegration/CMakeFiles/JohansenTest.dir/requires: cointegration/CMakeFiles/JohansenTest.dir/JohansenHelper.cpp.o.requires
.PHONY : cointegration/CMakeFiles/JohansenTest.dir/requires

cointegration/CMakeFiles/JohansenTest.dir/clean:
	cd /home/bill/AlgoTradingQTTest/AlgoTradingTest/bin/cointegration && $(CMAKE_COMMAND) -P CMakeFiles/JohansenTest.dir/cmake_clean.cmake
.PHONY : cointegration/CMakeFiles/JohansenTest.dir/clean

cointegration/CMakeFiles/JohansenTest.dir/depend:
	cd /home/bill/AlgoTradingQTTest/AlgoTradingTest/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bill/AlgoTradingQTTest/AlgoTradingTest /home/bill/AlgoTradingQTTest/AlgoTradingTest/cointegration /home/bill/AlgoTradingQTTest/AlgoTradingTest/bin /home/bill/AlgoTradingQTTest/AlgoTradingTest/bin/cointegration /home/bill/AlgoTradingQTTest/AlgoTradingTest/bin/cointegration/CMakeFiles/JohansenTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cointegration/CMakeFiles/JohansenTest.dir/depend

