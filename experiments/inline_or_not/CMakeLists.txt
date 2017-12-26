cmake_minimum_required(VERSION 3.5)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -O3 -flto") 
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -O3 -flto") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -O3 ") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -O3 ") 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
include_directories(../../vendors/nonius/include)
include_directories(../../vendors/nonius/include/nonius)

# Add asm files to `make clean`
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ../bin/inline.asm 
                                    ADDITIONAL_MAKE_CLEAN_FILES ../bin/not_inline.asm)


# Benchmark for inline version
add_executable(benchmark_inline benchmark_inline.cpp)
target_link_libraries(benchmark_inline m pthread)
add_custom_target(inline_report ALL 
                  ../bin/benchmark_inline -r html -o ../bin/benchmark_inline.html &&
                  xdg-open ../bin/benchmark_inline.html)
add_dependencies(inline_report benchmark_inline)
add_custom_target(bench_inline_assembly ALL objdump -drwC -Mintel ../bin/benchmark_inline > ../bin/benchmark_inline.asm)
add_dependencies(bench_inline_assembly benchmark_inline)


# Benchmark for not inline version
add_executable(benchmark_not_inline benchmark_not_inline.cpp library.c)
target_link_libraries(benchmark_not_inline m pthread)
add_custom_target(not_inline_report ALL 
                  ../bin/benchmark_not_inline -r html -o ../bin/benchmark_not_inline.html &&
                  xdg-open ../bin/benchmark_not_inline.html)
add_dependencies(not_inline_report benchmark_not_inline)
add_custom_target(bench_not_inline_assembly ALL objdump -drwC -Mintel ../bin/benchmark_not_inline > ../bin/benchmark_not_inline.asm)
add_dependencies(bench_not_inline_assembly benchmark_not_inline)
