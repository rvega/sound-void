cmake_minimum_required(VERSION 3.5)

# Compile unity library
include(ExternalProject)
ExternalProject_Add(unity SOURCE_DIR ../../vendors/unity INSTALL_COMMAND "")
ExternalProject_Get_Property(unity install_dir)

# Compile tests
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11 -Wall -O3 -g")
include_directories(../vendors/unity/src)
add_executable(run-tests hello-test.c) 

# Link tests and CppUTest library
add_dependencies(run-tests unity)
target_link_libraries(run-tests ${install_dir}/src/unity-build/libunity.a)

# Dummy target `make run`
add_custom_target(run ./run-tests)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
