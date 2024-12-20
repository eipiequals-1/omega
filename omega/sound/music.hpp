#ifndef OMEGA_SOUND_MUSIC_HPP
#define OMEGA_SOUND_MUSIC_HPP

#include <SDL3_mixer/SDL_mixer.h>

#include <string>

#include "omega/util/types.hpp"

namespace omega::sound {

using MusicID = size_t;

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

#endif // OMEGA_SOUND_MUSIC_HPP
