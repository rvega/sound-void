This test is to see if there is a measurable difference from inlining functions in the audio process vs not inlining them. A simple test that produces 1 second of audio with 16 sine oscillators shows a difference in processing time of a little over a millisecond in a 3GHz intel i7. So yeah, there is a measurable difference.

To make sure the code is actually being inlined, we're looking at the dissassembly of the compiled binaries.

If we compile and link with GCC's -flto flag (link time optimizations), the code is inlined automatically at link time, even in the not_inline version of the test and the performance gains are kept. :)


