#include <jack/jack.h>

// TODO add assertions before calling callbacks, before setting client name, others.

/////////////////////////////////////////////////////////////////////
// Declarations, data types.

struct sv_audio_io; // Forward declaration.
typedef int (*sv_audio_callback)(sv_audio_io*); // Avoid function pointer syntax.     
                                                // sv_audio_callback is now a type

/**
 * This struct holds all the data related to audio input and output. It will be passed 
 * around the different callbacks and values here should be set up before calling 
 * sv_audio_start
 */
typedef struct sv_audio_io {
  /**
   * Set the desired sample rate before calling sv_audio_io_start.
   * Get the actual sample rate after the setup_callback has been fired.
   */
  unsigned int sample_rate;

  /**
   * Set the desired block size before calling sv_audio_io_start.
   * Get the actual block size after the setup_callback has been fired.
   */
  unsigned int block_size;

  /**
   * Set the desired input channel count before calling sv_audio_io_start.
   * Get the actual input channel count after the setup_callback has been fired.
   */
  unsigned int input_channels;

  /**
   * Set the desired output channel count before calling sv_audio_io_start.
   * Get the actual output channel count after the setup_callback has been fired.
   */
  unsigned int output_channels;

  /**
   * Read only. Get audio input from these addresses.
   */
  sample_t** audio_in_buffers;

  /**
   * Read only. Set audio output to these addresses.
   */
  sample_t** audio_out_buffers;

  /**
   * Process callback will be fired from audio thread when output samples need to be
   * calculated
   */
  sv_audio_callback process_callback;

  /**
   * Setup callback will be fired from audio thread when connection to audio engine 
   * has been performed and actual connection properties like sample rate, channel 
   * count, etc. are known. You should do things like memory allocation for your 
   * audio processing graph (based on block size and channel count) during this callback.
   */
  sv_audio_callback setup_callback;

  /**
   * Teardown callback will be fired from audio thread when connection to audio engine 
   * has been interrupted. You can usually free the memory you allocated the memory
   * in the setup callback during the teardown callback.
   */
  sv_audio_callback teardown_callback;

  /**
   * This app's name as seen from the audio engine/server
   */
  char client_name[32];

  /**
   * Jack stuff. Private 
   */
  jack_client_t* jack_client;
  jack_port_t** audio_out_ports;
  jack_port_t** audio_in_ports;

} sv_audio_io;

/////////////////////////////////////////////////////////////////////
// Jack related functions/callbacks (private)

static|extern void av_jack_shutdown_callback(int a, int b) {
  .s.kjsdsd.skdjsdlkdjslksd slkjsdlkj lkjslksdjdl
}

/////////////////////////////////////////////////////////////////////
// Public functions

/* 
 * @public 
 * @description: Creates jack client with appropriate input and output ports and starts
 *               audio processing.
 */
int sv_audio_io_start(sv_audio_io* self) {
  int i;
  char port_name[8];
  unsigned long flags; 

  // Create jack client
  if((self->jack_client = jack_client_open(self->client_name, JackNullOption, NULL)) == NULL){
    return(1);
  }

  // Register audio in ports:
  flags = JackPortIsInput | JackPortIsTerminal;
  self->audio_in_ports = (jack_port_t**) malloc(input_channels*sizeof(jack_port_t*));
  self->audio_in_buffers = (sample_t**) malloc(input_channels*sizeof(sample_t*));
  for(i=0; i<input_channels; ++i) {
    sprintf(port_name, "In %i", i+1);
    audio_in_ports[i] = jack_port_register(jack_client, port_name, JACK_DEFAULT_AUDIO_TYPE, flags, 0);
  }

  // Register audio out ports:
  flags = JackPortIsOutput | JackPortIsTerminal;
  audio_out_ports = (jack_port_t**) malloc(output_channels*sizeof(jack_port_t*));
  audio_out_buffers = (sample_t**) malloc(output_channels*sizeof(sample_t*));
  for(i=0; i<output_channels; ++i) {
    sprintf(port_name, "Out %i", i+1);
    audio_out_ports[i] = jack_port_register(jack_client, port_name, JACK_DEFAULT_AUDIO_TYPE, flags, 0);
  }
  
  // Call processor's setup method
  self->buffer_size = jack_get_buffer_size(jack_client);
  self->sample_rate = jack_get_sample_rate(jack_client);
  processor->setup(self);

  // Register callbacks
  jack_on_shutdown(jack_client, av_jack_shutdown_callback, this);
  jack_set_process_callback(jack_client, AudioMidiIO::jackProcess, this);
  jack_set_sample_rate_callback(jack_client, AudioMidiIO::jackSampleRate, this);
  jack_set_buffer_size_callback(jack_client, AudioMidiIO::jackBufferSize, this);

  // Go!
  shouldProcess = true;
  if (jack_activate(jack_client)) {
    return 1;
  }

  // Connect to "system" outputs
  const char** ports = jack_get_ports(jack_client, "system:*", "audio", JackPortIsInput|JackPortIsTerminal);
  /* int i = 0; */
  while(ports[i]!=NULL) {
    if(i>1) break;
    jack_connect(jack_client, jack_port_name(audio_out_ports[i]), ports[i]);
    i++;
  }
  jack_free(ports);
}

int sv_audio_io_stop(sv_audio_io* self) {
  printf("%s\n", "Audio io stop");
  // TODO: free ports and buffers, close jack connection, call teardown callback
  return 0;
}

