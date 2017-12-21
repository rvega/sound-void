cmake_minimum_required(VERSION 3.5)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -O3")

# Where the .h files are
include_directories(../../library/)

# Enable support for jack
add_definitions(-DSV_WRAPPER_JACK)

# The app
add_executable(app main.cpp)

# Export compiler commands for use within code editor.
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
