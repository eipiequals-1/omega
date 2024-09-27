#ifndef OMEGA_UTIL_ASSETMANAGER_HPP
#define OMEGA_UTIL_ASSETMANAGER_HPP

#include <string>
#include <unordered_map>

#include "omega/gfx/shader.hpp"
#include "omega/gfx/texture/texture.hpp"
#include "omega/gfx/texture/texture_atlas.hpp"
#include "omega/sound/music.hpp"
#include "omega/sound/sound_effect.hpp"
#include "omega/ui/font.hpp"
#include "omega/util/std.hpp"

namespace omega::util {

class AssetManager {
  public:
    AssetManager();
    ~AssetManager();

    // textures
    gfx::texture::Texture *load_texture(
        const std::string &key,
        const std::string &filepath,
        gfx::texture::TextureParam min_filter =
            gfx::texture::TextureParam::NEAREST,
        gfx::texture::TextureParam mag_filter =
            gfx::texture::TextureParam::NEAREST) {
        textures[key] = gfx::texture::Texture::create_from_file(
            filepath, min_filter, mag_filter);
        return textures[key].get();
    }

    gfx::texture::Texture *load_empty_texture(
        const std::string &key,
        u32 width,
        u32 height,
        gfx::texture::TextureParam min_filter =
            gfx::texture::TextureParam::NEAREST,
        gfx::texture::TextureParam mag_filter =
            gfx::texture::TextureParam::NEAREST) {
        textures[key] = gfx::texture::Texture::create_empty(
            width, height, min_filter, mag_filter);
        return textures[key].get();
    }
    gfx::texture::Texture *get_texture(const std::string &key) {
        return textures[key].get();
    }

    gfx::texture::TextureAtlas *load_texture_atlas(
        const std::string &key,
        const std::string &filepath,
        gfx::texture::TextureParam min_filter =
            gfx::texture::TextureParam::NEAREST,
        gfx::texture::TextureParam mag_filter =
            gfx::texture::TextureParam::NEAREST) {
        texture_atlases[key] = util::create_uptr<gfx::texture::TextureAtlas>(
            filepath, min_filter, mag_filter);
        return texture_atlases[key].get();
    }

    gfx::texture::TextureAtlas *get_texture_atlas(const std::string &key) {
        return texture_atlases[key].get();
    }

    // sound effects
    sound::SoundEffectID load_sound_effect(const std::string &filepath);
    sound::MusicID load_music(const std::string &filepath);

    void play_sound_effect(sound::SoundEffectID sound, f32 volume);
    void play_music(sound::MusicID m, f32 volume);
    void set_music_volume(sound::MusicID m, f32 volume);
    void set_sound_effect_volume(sound::SoundEffectID sound, f32 volume);

    // shaders
    gfx::Shader *load_shader(const std::string &key,
                             const std::string &filepath) {
        shaders[key] = util::create_uptr<gfx::Shader>(filepath);
        return shaders[key].get();
    }

    gfx::Shader *load_shader(const std::string &key,
                             const std::string &vert,
                             const std::string &frag) {
        shaders[key] = util::create_uptr<gfx::Shader>(vert, frag);
        return shaders[key].get();
    }

    gfx::Shader *get_shader(const std::string &key) {
        return shaders[key].get();
    }

    // fonts
    ui::Font *load_font(const std::string &key,
                        const std::string &filepath,
                        const std::string &font_characters,
                        u32 glyph_height,
                        gfx::texture::TextureParam filter =
                            gfx::texture::TextureParam::NEAREST) {
        fonts[key] = util::create_uptr<ui::Font>(
            filepath, font_characters, glyph_height, filter);
        return fonts[key].get();
    }

    ui::Font *get_font(const std::string &key) {
        return fonts[key].get();
    }

  private:
    std::unordered_map<std::string, util::uptr<gfx::texture::Texture>> textures;
    std::unordered_map<std::string, util::uptr<gfx::texture::TextureAtlas>>
        texture_atlases;
    std::unordered_map<std::string, util::uptr<gfx::Shader>> shaders;
    std::unordered_map<std::string, util::uptr<ui::Font>> fonts;

    std::vector<util::uptr<sound::Music>> music;
    std::vector<util::uptr<sound::SoundEffect>> sound_effects;
};

} // namespace omega::util

#endif // OMEGA_UTIL_ASSETMANAGER_HPP
