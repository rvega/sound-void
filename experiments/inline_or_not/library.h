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

void sine_oscillator_init(sine_oscillator* self);
void sine_oscillator_free(sine_oscillator* self);
int sine_oscillator_tick(sine_oscillator* self, sample_t* out, unsigned int n);
void array_sum(sample_t* a, sample_t* b, sample_t* result, unsigned int count);
