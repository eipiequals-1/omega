#include "sound_effect.h"

namespace omega::sound {

SoundEffect::SoundEffect(const std::string &filepath) : chunk(nullptr) {
    chunk = Mix_LoadWAV(filepath.c_str());
    if (chunk == nullptr) {
        error("Failed to load wav file: '", filepath, "' Mix Callback: '", Mix_GetError(), "'");
    }
}

SoundEffect::~SoundEffect() {
    if (chunk != nullptr) {
        Mix_FreeChunk(chunk);
    }
    chunk = nullptr;
}

void SoundEffect::play(float volume) {
    Mix_VolumeChunk(chunk, MIX_MAX_VOLUME * volume);
    Mix_PlayChannel(-1, chunk, 0);
}
void SoundEffect::set_volume(float volume) {
    Mix_VolumeChunk(chunk, MIX_MAX_VOLUME * volume);
}

} // namespace omega::sound