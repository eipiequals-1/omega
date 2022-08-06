#include "font.h"

#include <iostream>

namespace omega {

Font::Font(const std::string& path, uint32_t size) : font_(nullptr) {
	font_ = TTF_OpenFont(path.c_str(), size);
	if (font_ == nullptr) {
		Log("TTF Error: Failed to load font '", path, "' at size ", size);
	}
}

Font::~Font() {
	if (font_ != nullptr) TTF_CloseFont(font_);
	font_ = nullptr;
}

Sptr<Texture> Font::RenderText(const std::string& text, const glm::vec4& color) {
	SDL_Color sdl_color;
	// shift colors 2 right because of TTF_RenderText_Blended errors
	sdl_color.r = static_cast<Uint8>(color.b * 255);
	sdl_color.g = static_cast<Uint8>(color.r * 255);
	sdl_color.b = static_cast<Uint8>(color.g * 255);
	sdl_color.a = static_cast<Uint8>(color.a * 255);
	SDL_Surface* surf = TTF_RenderText_Blended(font_, text.c_str(), sdl_color);
	Sptr<Texture> tex = Texture::CreateFromSurface(surf, GL_LINEAR, GL_LINEAR);
	SDL_FreeSurface(surf);
	return tex;
}

void FontManager::Load(const std::string& font_name, const std::string& filepath, uint32_t ptsize) {
	fonts_[font_name] = std::make_shared<Font>(filepath, ptsize);
}

Sptr<Font> FontManager::Get(const std::string& font_name) {
	return fonts_[font_name];
}

}  // namespace omega
