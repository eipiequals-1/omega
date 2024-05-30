#include "font.hpp"

namespace omega::ui {

Font::Font(const std::string &path,
           const std::string &font_characters,
           u32 glyph_width,
           u32 glyph_height,
           gfx::texture::TextureParam filter) {
    this->glyph_height = glyph_height;
    this->glyph_width = glyph_width;

    texture = gfx::texture::Texture::create_from_file(path, filter, filter);

    // prepare char_to_index map
    for (u32 i = 0; i < font_characters.size(); ++i) {
        char_to_index[font_characters[i]] = i;
    }
}

void Font::render(gfx::SpriteBatch &batch,
                  const std::string &text,
                  f32 px, f32 py, f32 height,
                  const math::vec4& color) {
    u32 rows, cols;
    cols = texture->get_width() / glyph_width;
    rows = texture->get_height() / glyph_height;

    f32 scale_factor = height / (f32) glyph_height;

    math::rectf src, dest;
    for (u32 i = 0; i < text.size(); ++i) {
        const char &c = text[i];
        const u32 char_index = char_to_index[c];

        u32 x, y;
        x = char_index % cols;
        y = char_index / cols;
        x *= glyph_width;
        y *= glyph_height;

        src.x = x;
        src.y = y;
        src.w = glyph_width;
        src.h = glyph_height;

        dest.x = px + ((f32) glyph_width) * scale_factor * i;
        dest.y = py;
        dest.w = ((f32) glyph_width) * scale_factor;
        dest.h = height;

        batch.render_texture(texture.get(), src, dest, color);
    }
}

} // namespace omega::ui
