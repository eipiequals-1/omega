#include "music.h"

namespace omega::sound {

Music::Music(const std::string &filepath) : music(nullptr) {
    music = Mix_LoadMUS(filepath.c_str());
    if (music == nullptr) {
        log("SDL mixer: Failed to load music from file '", filepath, "' SDL mixer Traceback: '", Mix_GetError(), "'");
    }
}

Music::~Music() {
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }
    music = nullptr;
}

void Music::play(f32 volume) {
    Mix_HaltMusic();
    Mix_VolumeMusic((int)(MIX_MAX_VOLUME * volume));
    Mix_PlayMusic(music, -1);
}

void Music::set_volume(f32 volume) {
    Mix_VolumeMusic((int)(MIX_MAX_VOLUME * volume));
}

} // namespace omega::sound