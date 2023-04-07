#include "asset_manager.hpp"

#include <SDL2/SDL_mixer.h>

#include "omega/util/log.hpp"

namespace omega::util {

AssetManager::AssetManager() {
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_OGG) == 0) {
        util::error("SDL_mixer error: Failed to initialize! '{}'",
                    Mix_GetError());
    }
    // sound frequency,
    // sample format,
    // # hardware channels,
    // sample size (2048 bytes)
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        util::error("SDL_mixer error: Failed to open mixer! '{}'",
                    Mix_GetError());
    }
}

AssetManager::~AssetManager() {
    Mix_CloseAudio();
    Mix_Quit();
}

sound::SoundEffectID AssetManager::load_sound_effect(
    const std::string &filepath) {

    util::uptr<sound::SoundEffect> effect =
        util::create_uptr<sound::SoundEffect>(filepath);
    sound_effects.push_back(std::move(effect));
    return sound_effects.size() - 1;
}

sound::MusicID AssetManager::load_music(const std::string &filepath) {
    util::uptr<sound::Music> m = util::create_uptr<sound::Music>(filepath);
    music.push_back(std::move(m));
    return music.size() - 1;
}

void AssetManager::play_sound_effect(sound::SoundEffectID sound,
                                     float volume) {
    sound_effects[sound]->play(volume);
}

void AssetManager::play_music(sound::MusicID m, float volume) {
    music[m]->play(volume);
}

void AssetManager::set_music_volume(sound::MusicID m, float volume) {
    music[m]->set_volume(volume);
}

void AssetManager::set_sound_effect_volume(sound::SoundEffectID sound,
                                           float volume) {
    sound_effects[sound]->set_volume(volume);
}

} // namespace omega::util
