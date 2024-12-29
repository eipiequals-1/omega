#include "asset_manager.hpp"

#include <SDL3_mixer/SDL_mixer.h>

#include "omega/util/log.hpp"

namespace omega::util {

AssetManager::AssetManager() {
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_OGG) == 0) {
        OMEGA_ERROR("SDL_mixer error: Failed to initialize! '{}'",
                  SDL_GetError());
    }
    // sound frequency,
    // sample format,
    // # hardware channels,
    // sample size (2048 bytes)
    SDL_AudioDeviceID id;
    SDL_AudioSpec spec;
    spec.freq = 44100;
    spec.format = MIX_DEFAULT_FORMAT;
    spec.channels = 2;
    if (!Mix_OpenAudio(0, &spec)) {
        OMEGA_ERROR("SDL_mixer error: Failed to open mixer! '{}'",
                  SDL_GetError());
    } else {
        Mix_QuerySpec(&spec.freq, &spec.format, &spec.channels);
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

void AssetManager::play_sound_effect(sound::SoundEffectID sound, f32 volume) {
    sound_effects[sound]->play(volume);
}

void AssetManager::play_music(sound::MusicID m, f32 volume) {
    music[m]->play(volume);
}

void AssetManager::set_music_volume(sound::MusicID m, f32 volume) {
    music[m]->set_volume(volume);
}

void AssetManager::set_sound_effect_volume(sound::SoundEffectID sound,
                                           f32 volume) {
    sound_effects[sound]->set_volume(volume);
}

} // namespace omega::util
