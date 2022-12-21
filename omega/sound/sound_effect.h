#ifndef OMEGA_SOUND_SOUNDEFFECT_H
#define OMEGA_SOUND_SOUNDEFFECT_H

#include "omega/util/util.h"
#include <SDL2/SDL_mixer.h>

namespace omega::sound {

using namespace omega::util;

class SoundEffect {
  public:
    SoundEffect(const std::string &filepath);
    ~SoundEffect();

    void play(float volume);
    void set_volume(float volume);

  private:
    Mix_Chunk *chunk;
};

} // namespace omega::sound

#endif // OMEGA_SOUND_SOUNDEFFECT_H