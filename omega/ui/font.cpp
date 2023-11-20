#include "font.hpp"

#include "omega/util/log.hpp"

namespace omega::ui {

Font::Font(const std::string &path, uint32_t size) : font(nullptr) {
    font = TTF_OpenFont(path.c_str(), size);
    if (font == nullptr) {
        util::error("TTF Error: Failed to load font '", path, "' at size ", size);
    }
}

Font::~Font() {
    if (font != nullptr)
        TTF_CloseFont(font);
    font = nullptr;
}

util::sptr<gfx::texture::Texture> Font::render_text(const std::string &text,
                                                    const math::vec4 &color) {
    SDL_Color sdl_color;
    // shift colors 2 right because of TTF_RenderText_Blended errors
    sdl_color.r = static_cast<uint8_t>(color.b * 255);
    sdl_color.g = static_cast<uint8_t>(color.r * 255);
    sdl_color.b = static_cast<uint8_t>(color.g * 255);
    sdl_color.a = static_cast<uint8_t>(color.a * 255);
    // create surface
    SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), sdl_color);
    util::sptr<gfx::texture::Texture> tex =
        gfx::texture::Texture::create_from_surface(surf, gfx::texture::TextureParam::LINEAR, gfx::texture::TextureParam::LINEAR);

    SDL_FreeSurface(surf);
    return tex;
}

void FontManager::load(const std::string &font_name,
                       const std::string &filepath,
                       uint32_t ptsize) {
    fonts[font_name] = util::create_sptr<Font>(filepath, ptsize);
}

util::sptr<Font> FontManager::get(const std::string &font_name) {
    return fonts[font_name];
}

bool FontManager::contains(const std::string &font_name) {
    return fonts.find(font_name) != fonts.end();
}

util::sptr<Font> FontManager::operator[](const std::string &font_name) {
    return get(font_name);
}

} // namespace omega::ui
