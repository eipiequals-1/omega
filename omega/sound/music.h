#ifndef OMEGA_SOUND_MUSIC_H
#define OMEGA_SOUND_MUSIC_H

#include <SDL2/SDL_mixer.h>

#include "omega/util/util.h"

namespace omega::sound {

using namespace omega::util;

class Music {
  public:
    Music(const std::string &filepath);
    ~Music();

    void play(f32 volume);
    void set_volume(f32 volume);

  private:
    Mix_Music *music;
};

} // namespace omega::sound

#endif // OMEGA_SOUND_MUSIC_H