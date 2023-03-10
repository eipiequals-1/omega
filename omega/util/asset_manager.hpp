#ifndef OMEGA_UTIL_ASSETMANAGER_HPP
#define OMEGA_UTIL_ASSETMANAGER_HPP

#include <string>
#include <unordered_map>

#include "omega/gfx/texture/texture.hpp"
#include "omega/gfx/shader.hpp"
#include "omega/sound/sound_effect.hpp"
#include "omega/sound/music.hpp"

namespace omega::util {

class AssetManager {
  public:
    AssetManager();
    ~AssetManager();
    
    // textures
    gfx::texture::Texture* load_texture(
        const std::string &key,
        const std::string &filepath,
        GLenum min_filter = GL_NEAREST,
        GLenum mag_filter = GL_NEAREST)
    {
        textures[key] = gfx::texture::Texture::create_from_file(filepath, min_filter, mag_filter);
        return textures[key].get();
    }

    gfx::texture::Texture* load_empty_texture(
        const std::string &key,
        uint32_t width,
        uint32_t height,
        GLenum min_filter = GL_NEAREST,
        GLenum mag_filter = GL_NEAREST)
    {
        textures[key] = gfx::texture::Texture::create_empty(width, height, min_filter, mag_filter);
        return textures[key].get();
    }
    gfx::texture::Texture* get_texture(const std::string &key) {
        return textures[key].get();
    }
    
    // sound effects
    sound::SoundEffectID load_sound_effect(const std::string &filepath);
    sound::MusicID load_music(const std::string &filepath);

    void play_sound_effect(sound::SoundEffectID sound, float volume);
    void play_music(sound::MusicID m, float volume);
    void set_music_volume(sound::MusicID m, float volume);
    void set_sound_effect_volume(sound::SoundEffectID sound, float volume);

    // shaders
    gfx::Shader *load_shader(const std::string &key, const std::string &filepath) {
        shaders[key] = util::create_uptr<gfx::Shader>(filepath);
        return shaders[key].get();
    }

    gfx::Shader *load_shader(const std::string &key, const std::string &vert, const std::string &frag) {
        shaders[key] = util::create_uptr<gfx::Shader>(vert, frag);
        return shaders[key].get();
    }

    gfx::Shader *get_shader(const std::string &key) { 
        return shaders[key].get();
    }

  private:
    std::unordered_map<std::string, util::uptr<gfx::texture::Texture>> textures;
    std::unordered_map<std::string, util::uptr<gfx::Shader>> shaders;

    std::vector<util::uptr<sound::Music>> music;
    std::vector<util::uptr<sound::SoundEffect>> sound_effects;
};

} // namespace omega::util

#endif // OMEGA_UTIL_ASSETMANAGER_HPP
