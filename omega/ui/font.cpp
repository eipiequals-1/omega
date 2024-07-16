#include "font.hpp"

namespace omega::ui {

Font::Font(const std::string &path,
           const std::string &font_characters,
           u32 glyph_height,
           gfx::texture::TextureParam filter) {
    this->glyph_height = glyph_height;

    texture = gfx::texture::Texture::create_from_file(path, filter, filter);

    // iterate through each pixel of the texture
    auto pixels = texture->get_pixels();
    u32 last_x = 0;
    u32 i = 0;
    for (u32 y = 0; y < texture->get_height(); y += glyph_height) {
        last_x = 0;
        for (u32 x = 0; x < texture->get_width(); ++x) {
            auto &color = pixels[y * texture->get_width() + x];
            if (color == 0xff0000ff) { // red color
                Char c;
                c.x = last_x;
                c.y = y;
                c.width = x - last_x + 1;
                c.height = glyph_height;
                last_x = x + 1;
                char_to_pos[font_characters[i]] = c;

                // change it now to transparent
                color = 0x0;
                i++;
            }
        }
    }
    // update the new texture with the removed marker pixels
    texture->load(pixels.get());
}

void Font::render(gfx::SpriteBatch &batch,
                  const std::string &text,
                  f32 px,
                  f32 py,
                  f32 height,
                  const math::vec4 &color) {
    f32 scale_factor = height / (f32)glyph_height;

    math::rectf src, dest;
    dest.x = px;
    for (u32 i = 0; i < text.size(); ++i) {
        const char &c = text[i];
        const Char &char_loc = char_to_pos[c];

        src.x = char_loc.x;
        src.y = char_loc.y;
        src.w = char_loc.width;
        src.h = char_loc.height;

        dest.y = py;
        dest.w = ((f32)src.w) * scale_factor;
        dest.h = height;

        batch.render_texture(texture.get(), src, dest, color);
        // update the x value after rendering
        // sets the pos for the next character
        dest.x += src.w * scale_factor;
    }
}

void Font::render_centered(gfx::SpriteBatch &batch,
                           const std::string &text,
                           f32 px,
                           f32 py,
                           f32 height,
                           const math::vec4 &color) {
    f32 scale_factor = height / (f32)glyph_height;

    f32 width = 0.0f;
    for (u32 i = 0; i < text.size(); ++i) {
        const Char &char_loc = char_to_pos[text[i]];
        width += char_loc.width;
    }

    math::rectf src, dest;
    dest.x = px - width / 2.0f * scale_factor;
    for (u32 i = 0; i < text.size(); ++i) {
        const char &c = text[i];
        const Char &char_loc = char_to_pos[c];

        src.x = char_loc.x;
        src.y = char_loc.y;
        src.w = char_loc.width;
        src.h = char_loc.height;

        dest.y = py;
        dest.w = ((f32)src.w) * scale_factor;
        dest.h = height;

        batch.render_texture(texture.get(), src, dest, color);
        // update the x value after rendering
        // sets the pos for the next character
        dest.x += src.w * scale_factor;
    }
}

} // namespace omega::ui
