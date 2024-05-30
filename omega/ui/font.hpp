#ifndef OMEGA_UI_FONT_HPP
#define OMEGA_UI_FONT_HPP

#include <string>
#include <unordered_map>

#include "omega/gfx/sprite_batch.hpp"
#include "omega/gfx/texture/texture.hpp"
#include "omega/math/math.hpp"
#include "omega/util/color.hpp"
#include "omega/util/std.hpp"

namespace omega::ui {

/**
 * Represents a font with uniform width/height for each character
 * */
class Font {
  public:
    Font(const std::string &path,
         const std::string &font_characters,
         u32 glyph_width = 8,
         u32 glyph_height = 8,
         gfx::texture::TextureParam filter
            = gfx::texture::TextureParam::NEAREST);
    ~Font() = default;

    void render(gfx::SpriteBatch &batch,
                const std::string &text,
                f32 px, f32 py, f32 height,
                const math::vec4& color = util::color::white);

    u32 get_glyph_width() const { return glyph_width; }
    u32 get_glyph_height() const { return glyph_height; }

  private:
    util::uptr<gfx::texture::Texture> texture = nullptr;

    std::unordered_map<char, u32> char_to_index;

    u32 glyph_width = 8, glyph_height = 8;
};

} // namespace omega::ui

#endif // OMEGA_UI_FONT_HPP
