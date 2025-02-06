# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(Lab4)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Include directory with header files
include_directories(include)

# Source files
set(SOURCES
    src/main.c
    src/traffic_light.c
)

# Create/build the executable
add_executable(traffic_light ${SOURCES})

# Apply debug flags to the 'traffic_light' target
target_compile_options(traffic_light PRIVATE -g -Wall -Wextra -Werror -pedantic)

# 'Run' target to build and run the executable
add_custom_target(run
    COMMAND traffic_light # Run the executable
    DEPENDS traffic_light # Built before run
)

# Custom clean target
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove_directory -f CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove -f cmake_install.cmake
    COMMAND ${CMAKE_COMMAND} -E remove -f CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E remove -f traffic_light
)