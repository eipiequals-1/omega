#ifndef OMEGA_SOUND_SOUNDEFFECT_H
#define OMEGA_SOUND_SOUNDEFFECT_H

#include <SDL2/SDL_mixer.h>

#include <string>

namespace omega::sound {

using SoundEffectID = size_t;

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
