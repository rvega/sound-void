cmake_minimum_required(VERSION 3.5)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -O3 -g") 

include_directories(../vendors/nonius/include)
include_directories(../vendors/nonius/include/nonius)

###########################################################
# Hello world

add_executable(hello_world hello_world/main.cpp) 
target_link_libraries(hello_world pthread)
add_custom_target(run-benchmarks ./hello_world)
