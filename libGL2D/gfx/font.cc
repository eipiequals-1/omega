#include "font.h"

#include <iostream>

namespace libgl {

Font::Font(const std::string& path, uint32_t size) : size_(size), font_(nullptr) {
	font_ = TTF_OpenFont(path.c_str(), size);
	if (font_ == nullptr) {
		std::cout << "TTF Error: Failed to load font '" + path + "' at size " + std::to_string(size) << '\n';
	}
}

Font::~Font() {
	if (font_ != nullptr) TTF_CloseFont(font_);
	font_ = nullptr;
}

SDL_Surface* Font::RenderText(const std::string& text, const glm::vec4& color) {
	SDL_Color sdl_color;
	sdl_color.r = static_cast<Uint8>(color.r * 255);
	sdl_color.g = static_cast<Uint8>(color.g * 255);
	sdl_color.b = static_cast<Uint8>(color.b * 255);
	sdl_color.a = static_cast<Uint8>(color.a * 255);
	return TTF_RenderText_Blended(font_, text.c_str(), sdl_color);
}

void FontManager::Load(const std::string& font_name, const std::string& filepath, uint32_t ptsize) {
	fonts_[font_name] = std::make_shared<Font>(filepath, ptsize);
}

}  // namespace libgl
