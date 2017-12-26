#define NONIUS_RUNNER
#include <nonius_single.h++>

extern "C" {
  #include "library.h"
}

NONIUS_BENCHMARK("Not inline", []{
  sine_oscillator oscillators[16];
  sample_t buffer[48000] = {0};
  sample_t accummulator[48000] = {0};

  for(int i=0; i<16; ++i) {
    sine_oscillator_init(&oscillators[i]);
    oscillators[i].frequency = 55*i;
    oscillators[i].sample_rate = 48000;
  }

  for(int j=0; j<48000; j+=128) {
    for(int i=0; i<16; ++i) {
      sine_oscillator_tick(&oscillators[i], &(buffer[j]), 128);
      array_sum(&buffer[j], &accummulator[j], &accummulator[j], 128);
    }
  }

  /* for(i=0; i<20; ++i) { */
  /*   printf("%f ", buffer[i]); */
  /* } */
  /* for(i=48000-21; i<48000-1; ++i) { */
  /*   printf("%f ", buffer[i]); */
  /* } */

  return accummulator[47999];
})

