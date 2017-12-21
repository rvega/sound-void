#include <iostream>

extern "C" {
  #include "SoundVoid.h"
}

/////////////////////////////////////////////////////////////////////
// Audio engine callbacks

void audio_teardown(sv_audio_io* audio_io) {

}

void audio_setup(sv_audio_io* audio_io) {
  // Get sample rate and frame size here.
}

int process_audio(sv_audio_io* audio_io, unsigned int n_frames) {
  std::cout << "Process\n"; 
  return 0;
}

int main(int argc, char *argv[]) {
  std::cout << "main\n";

  sv_audio_io audio_io;
  if(sv_audio_io_start(&audio_io, 2, 2, &process_audio, "Sound Void Example")) {
    std::cerr << "Could not start audio io\n";
    return 1;
  }

  if(sv_audio_io_stop(&audio_io)) {
    std::cerr << "Could not stop audio io\n";
    return 1;
  }

  return 0;
}
