#ifndef OMEGA_SOUND_SOUNDMANAGER_H
#define OMEGA_SOUND_SOUNDMANAGER_H

#include <SDL2/SDL_mixer.h>

#include "omega/sound/music.h"
#include "omega/sound/sound_effect.h"
#include "omega/util/util.h"

namespace omega::sound {

using namespace omega::util;

using MusicID = size_t;
using SoundEffectID = size_t;

class SoundManager {
  public:
    SoundManager(const SoundManager &) = delete;
    SoundManager operator=(const SoundManager &) = delete;
    ~SoundManager();

    static sptr<SoundManager> instance() {
        static sptr<SoundManager> sound_manager = sptr<SoundManager>(new SoundManager());
        return sound_manager;
    }

    SoundEffectID load_sound_effect(const std::string &filepath);
    MusicID load_music(const std::string &filepath);

    void play_sound_effect(SoundEffectID sound, float volume);
    void play_music(MusicID m, float volume);
    void set_music_volume(MusicID m, float volume);
    void set_sound_effect_volume(SoundEffectID sound, float volume);

  private:
    SoundManager();

    std::vector<sptr<Music>> music;
    std::vector<sptr<SoundEffect>> sound_effects;
};

} // namespace omega::sound

#endif // OMEGA_SOUND_SOUNDMANAGER_H