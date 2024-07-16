#include "sound_effect.hpp"

#include "omega/util/log.hpp"

namespace omega::sound {

SoundEffect::SoundEffect(const std::string &filepath) : chunk(nullptr) {
    chunk = Mix_LoadWAV(filepath.c_str());
    if (chunk == nullptr) {
        util::warn(
            "SDL mixer: Failed to load sound from file '{}'\n SDL mixer "
            "Traceback '{}'",
            filepath,
            Mix_GetError());
    }
}

SoundEffect::~SoundEffect() {
    if (chunk != nullptr) {
        Mix_FreeChunk(chunk);
    }
    chunk = nullptr;
}

void SoundEffect::play(f32 volume) {
    Mix_VolumeChunk(chunk, MIX_MAX_VOLUME * volume);
    Mix_PlayChannel(-1, chunk, 0);
}
void SoundEffect::set_volume(f32 volume) {
    Mix_VolumeChunk(chunk, MIX_MAX_VOLUME * volume);
}

} // namespace omega::sound
