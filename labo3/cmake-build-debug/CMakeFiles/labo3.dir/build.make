# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Stefano\Documents\HEIG\1 semestre\PROG1\labo\labo3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Stefano\Documents\HEIG\1 semestre\PROG1\labo\labo3\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/labo3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/labo3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/labo3.dir/flags.make

CMakeFiles/labo3.dir/main.cpp.obj: CMakeFiles/labo3.dir/flags.make
CMakeFiles/labo3.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Stefano\Documents\HEIG\1 semestre\PROG1\labo\labo3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/labo3.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\labo3.dir\main.cpp.obj -c "C:\Users\Stefano\Documents\HEIG\1 semestre\PROG1\labo\labo3\main.cpp"

CMakeFiles/labo3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/labo3.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Stefano\Documents\HEIG\1 semestre\PROG1\labo\labo3\main.cpp" > CMakeFiles\labo3.dir\main.cpp.i

CMakeFiles/labo3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/labo3.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Stefano\Documents\HEIG\1 semestre\PROG1\labo\labo3\main.cpp" -o CMakeFiles\labo3.dir\main.cpp.s

# Object files for target labo3
labo3_OBJECTS = \
"CMakeFiles/labo3.dir/main.cpp.obj"

# External object files for target labo3
labo3_EXTERNAL_OBJECTS =

labo3.exe: CMakeFiles/labo3.dir/main.cpp.obj
labo3.exe: CMakeFiles/labo3.dir/build.make
labo3.exe: CMakeFiles/labo3.dir/linklibs.rsp
labo3.exe: CMakeFiles/labo3.dir/objects1.rsp
labo3.exe: CMakeFiles/labo3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Stefano\Documents\HEIG\1 semestre\PROG1\labo\labo3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable labo3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\labo3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/labo3.dir/build: labo3.exe

.PHONY : CMakeFiles/labo3.dir/build

CMakeFiles/labo3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\labo3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/labo3.dir/clean

CMakeFiles/labo3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Stefano\Documents\HEIG\1 semestre\PROG1\labo\labo3" "C:\Users\Stefano\Documents\HEIG\1 semestre\PROG1\labo\labo3" "C:\Users\Stefano\Documents\HEIG\1 semestre\PROG1\labo\labo3\cmake-build-debug" "C:\Users\Stefano\Documents\HEIG\1 semestre\PROG1\labo\labo3\cmake-build-debug" "C:\Users\Stefano\Documents\HEIG\1 semestre\PROG1\labo\labo3\cmake-build-debug\CMakeFiles\labo3.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/labo3.dir/depend

