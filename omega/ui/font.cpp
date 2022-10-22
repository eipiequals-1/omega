#include "font.h"

#include <iostream>

namespace omega::ui {

Font::Font(const std::string &path, u32 size) : font(nullptr) {
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

sptr<Texture> Font::render_text(const std::string &text, const glm::vec4 &color) {
    SDL_Color sdl_color;
    // shift colors 2 right because of TTF_RenderText_Blended errors
    sdl_color.r = static_cast<u8>(color.b * 255);
    sdl_color.g = static_cast<u8>(color.r * 255);
    sdl_color.b = static_cast<u8>(color.g * 255);
    sdl_color.a = static_cast<u8>(color.a * 255);
    SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), sdl_color);
    sptr<Texture> tex = Texture::create_from_surface(surf, GL_LINEAR, GL_LINEAR);
    SDL_FreeSurface(surf);
    return tex;
}

void FontManager::load(const std::string &font_name, const std::string &filepath, u32 ptsize) {
    fonts[font_name] = std::make_shared<Font>(filepath, ptsize);
}

sptr<Font> FontManager::get(const std::string &font_name) {
    return fonts[font_name];
}

} // namespace omega::ui
