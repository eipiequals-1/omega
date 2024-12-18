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

struct Char {
    u32 x = 0, y = 0;
    u32 width = 0, height = 0;
};

/**
 * Represents a font with uniform width/height for each character because it's
 * just much simpler.
 * */
class Font {
  public:
    Font(const std::string &path,
         const std::string &font_characters,
         u32 glyph_height = 8,
         gfx::texture::TextureParam filter =
             gfx::texture::TextureParam::NEAREST);
    ~Font() = default;

    void render(gfx::SpriteBatch &batch,
                const std::string &text,
                f32 px,
                f32 py,
                f32 height,
                const math::vec4 &color = util::color::white);

    void render(gfx::SpriteBatch &batch,
                const char *text,
                u32 length,
                f32 px,
                f32 py,
                f32 height,
                const math::vec4 &color = util::color::white);

    void render_centered(gfx::SpriteBatch &batch,
                         const std::string &text,
                         f32 px,
                         f32 py,
                         f32 height,
                         const math::vec4 &color = util::color::white);
    u32 get_glyph_height() const {
        return glyph_height;
    }

  private:
    util::uptr<gfx::texture::Texture> texture = nullptr;

    std::unordered_map<char, Char> char_to_pos;

    u32 glyph_height = 8;
};

} // namespace omega::ui

#endif // OMEGA_UI_FONT_HPP
