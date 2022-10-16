#include "sound_manager.h"

namespace omega::sound {

SoundManager::SoundManager() {
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_OGG) == 0) {
        log("SDL_mixer error: Failed to initialize! '", Mix_GetError(), "'");
    }
    // sound frequency, sample format, number of hardware channels, sample size (2048 bytes)
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        log("SDL_mixer error: Failed to open mixer! '", Mix_GetError(), "'");
    }
}

SoundManager::~SoundManager() {
    Mix_CloseAudio();
    Mix_Quit();
}

SoundEffectID SoundManager::load_sound_effect(const std::string &filepath) {
    sptr<SoundEffect> effect = create_sptr<SoundEffect>(filepath);
    sound_effects.push_back(effect);
    return sound_effects.size() - 1;
}

MusicID SoundManager::load_music(const std::string &filepath) {
    sptr<Music> m = create_sptr<Music>(filepath);
    music.push_back(m);
    return music.size() - 1;
}

void SoundManager::play_sound_effect(SoundEffectID sound, f32 volume) {
    sound_effects[sound]->play(volume);
}

void SoundManager::play_music(MusicID m, f32 volume) {
    music[m]->play(volume);
}

void SoundManager::set_music_volume(MusicID m, f32 volume) {
    music[m]->set_volume(volume);
}

void SoundManager::set_sound_effect_volume(SoundEffectID sound, f32 volume) {
    sound_effects[sound]->set_volume(volume);
}

} // namespace omega::sound
