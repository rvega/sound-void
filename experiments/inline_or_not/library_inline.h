#include <stdlib.h>
#include <tgmath.h>

typedef float sample_t;

#define M_PI 3.14159265358979323846264338327950288

typedef struct sine_oscillator {
  unsigned int frequency;
  unsigned int sample_rate;

  sample_t initial_phase;
  sample_t current_phase;

  unsigned int table_size;
  sample_t* table;// Should be static data. Ignore for now.
} sine_oscillator;

inline void sine_oscillator_init(sine_oscillator* self) {
  self->table_size = 1024;
  self->table = (sample_t*)malloc((2+self->table_size) * sizeof(sample_t));

  self->initial_phase = 0;
  self->current_phase = 0;

  for(unsigned int i=0; i<self->table_size; ++i) {
    self->table[i] = sin(i*2*M_PI/self->table_size);
  }
  self->table[self->table_size] = self->table[0];
  self->table[self->table_size+1] = self->table[1];
}

inline void sine_oscillator_free(sine_oscillator* self) {
  free(self->table);
  self->table = NULL;
}

inline int sine_oscillator_tick(sine_oscillator* self, sample_t* out, unsigned int n) {
  unsigned int table_size = self->table_size;
  sample_t* table = self->table;

  // Cubic (4 point) interpolating loookup table
  sample_t size_over_ratio = (sample_t)table_size/(sample_t)self->sample_rate;
  sample_t increment = self->frequency*size_over_ratio;
  sample_t offset = (int)(self->initial_phase*table_size)%table_size;
  sample_t position, y0, y1, y2, y3, tmp, fraction, fraction2, fraction3;
  for(size_t i=0; i<n; ++i) {
    position = self->current_phase + offset;
    fraction = position - (int)position;
    y0 = (int) position>0 ? table[(int)position-1] : table[table_size-1];
    y1 = table[(int)position];
    y2 = table[(int)position+1];
    y3 = table[(int)position+2];

    tmp = y3 + 3.0*y1;
    fraction2 = fraction*fraction;
    fraction3 = fraction2*fraction;

    out[i] = fraction3*(- y0 - 3.0*y2 + tmp)/6.0 +
      fraction2*((y0+y2)/2.0 - y1) +
      fraction*(y2 + (-2.0*y0 - tmp)/6.0) + y1;

    self->current_phase += increment;
    while(self->current_phase >= table_size) self->current_phase -= table_size;
    while(self->current_phase < 0) self->current_phase += table_size;
  }

  return n;
}

inline void array_sum(sample_t* a, sample_t* b, sample_t* result, unsigned int count) {
  unsigned int i;
  for(i=0; i<count; ++i) {
    result[i] = a[i] + b[i]; 
  }
}
