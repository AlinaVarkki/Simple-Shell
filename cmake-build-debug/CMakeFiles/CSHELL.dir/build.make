# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.3.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\USER\Desktop\CSHELL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\USER\Desktop\CSHELL\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CSHELL.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CSHELL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CSHELL.dir/flags.make

CMakeFiles/CSHELL.dir/main.c.obj: CMakeFiles/CSHELL.dir/flags.make
CMakeFiles/CSHELL.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\USER\Desktop\CSHELL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CSHELL.dir/main.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\CSHELL.dir\main.c.obj   -c C:\Users\USER\Desktop\CSHELL\main.c

CMakeFiles/CSHELL.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CSHELL.dir/main.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\USER\Desktop\CSHELL\main.c > CMakeFiles\CSHELL.dir\main.c.i

CMakeFiles/CSHELL.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CSHELL.dir/main.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\USER\Desktop\CSHELL\main.c -o CMakeFiles\CSHELL.dir\main.c.s

# Object files for target CSHELL
CSHELL_OBJECTS = \
"CMakeFiles/CSHELL.dir/main.c.obj"

# External object files for target CSHELL
CSHELL_EXTERNAL_OBJECTS =

CSHELL.exe: CMakeFiles/CSHELL.dir/main.c.obj
CSHELL.exe: CMakeFiles/CSHELL.dir/build.make
CSHELL.exe: CMakeFiles/CSHELL.dir/linklibs.rsp
CSHELL.exe: CMakeFiles/CSHELL.dir/objects1.rsp
CSHELL.exe: CMakeFiles/CSHELL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\USER\Desktop\CSHELL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable CSHELL.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\CSHELL.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CSHELL.dir/build: CSHELL.exe

.PHONY : CMakeFiles/CSHELL.dir/build

CMakeFiles/CSHELL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\CSHELL.dir\cmake_clean.cmake
.PHONY : CMakeFiles/CSHELL.dir/clean

CMakeFiles/CSHELL.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\USER\Desktop\CSHELL C:\Users\USER\Desktop\CSHELL C:\Users\USER\Desktop\CSHELL\cmake-build-debug C:\Users\USER\Desktop\CSHELL\cmake-build-debug C:\Users\USER\Desktop\CSHELL\cmake-build-debug\CMakeFiles\CSHELL.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CSHELL.dir/depend

