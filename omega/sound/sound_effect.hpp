#ifndef OMEGA_SOUND_SOUNDEFFECT_HPP
#define OMEGA_SOUND_SOUNDEFFECT_HPP

#include <SDL3_mixer/SDL_mixer.h>

#include <string>

#include "omega/util/types.hpp"

namespace omega::sound {

using SoundEffectID = size_t;

class SoundEffect {
  public:
    SoundEffect(const std::string &filepath);
    ~SoundEffect();

    void play(f32 volume);
    void set_volume(f32 volume);

  private:
    Mix_Chunk *chunk;
};

} // namespace omega::sound

#endif // OMEGA_SOUND_SOUNDEFFECT_HPP
