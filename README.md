# Sound Void

## Compiling.

Sound Void is written using only header files so you don't really need to compile the library. What you need to do is compile your application so that it includes the library. We use the GCC compiler at version 7.2.0. Sound Void should compile fine with other compilers that support the C++17 standard. The example applications use cmake to automate builds, look at the CMakeLists.txt files there to see the compiler flags we use.

There are some pre-processor macros we use in the library for setting some compile-time options. You can set these options in your CMakeLists.txt: `add_definitions(-DSV_WRAPPER_JACK)`. Get the full list of macros from [SoundVoid.hpp](library/SoundVoid.hpp).

## TO-DO

* Profiling
* Unit test filters, maybe with impulse response.
* Design the audio graph, we need multi-threaded, rt-safe, fast stuff.
* Benchmark and profiling: ¿nonius?

## Tests and benchmarks

[CppUTest](http://cpputest.github.io) is used for unit testing. To compile and run the tests:

    cd tests
    mkdir build
    cd build 
    cmake .. && make

## Licensing

The sound void library is licensed under the Mozilla Public License v2.

You get the full source code. You can examine the code, modify it, and share your modified code under the terms of the MPLv2.

Sound Void is safe for use in close-source applications. The MPLv2 share-alike terms do not apply to applications built on top of Sound Void.

You do not need a commercial license. The MPLv2 applies to Sound Void's own source code, not your applications. At least one commercial application uses Sound Void.
