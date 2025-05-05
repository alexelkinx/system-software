# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(Lab3)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Include directory with header files
include_directories(include)

# Specify source files
set(SOURCES
    src/main.c
    src/filter.c
    src/ma_filter.c
    src/low_pass_filter.c
    src/io.c
    )

# Default to Debug build if no build type is specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Debug flags:
# -g: adds debugging info for gdb
# -Wall: enables basic warnings
# -Wextra: enables extra warnings
# -Werror: treats warnings as errors
set(CMAKE_C_FLAGS_DEBUG "-g -Wall -Wextra -Werror")

# Set the build type to Release by default
# set(CMAKE_BUILD_TYPE Release)

# Release flags:
# -O3: enables maximum optimization for performance
set(CMAKE_C_FLAGS_RELEASE "-O3")

# Create/build the executable
add_executable(filter ${SOURCES})

# Custom target to run the program
add_custom_target(run
    COMMAND filter # Run the filter executable.
    DEPENDS filter # Ensures that filter is built before it’s run.
)

# Custom target to run the program with Low Pass filter
add_custom_target(low
    COMMAND filter ../data/temperature_data.csv ../data/filtered_data.csv -low
    DEPENDS filter
)

# Custom clean target
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove_directory -f CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove -f cmake_install.cmake
    COMMAND ${CMAKE_COMMAND} -E remove -f CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E remove -f filter
)