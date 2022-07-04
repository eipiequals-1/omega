#ifndef LIBGL2D_GFX_FONT_H
#define LIBGL2D_GFX_FONT_H

#include <SDL2/SDL_ttf.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "libGL2D/core/using.h"
#include "libGL2D/gfx/texture/texture.h"
#include "libGL2D/physics/math.h"

namespace libgl {

/**
 * Represents a ttf / SDL_ttf font at a given size
 */
class Font {
   public:
	Font(const std::string& path, uint32_t size);
	~Font();
	/**
	 * Creates a Textre to draw
	 * @param text to render
	 * @param color to draw it
	 * @return a Texture
	 */
	Texture* RenderText(const std::string& text, const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

   private:
	TTF_Font* font_;
};

/**
 * Stores multiple fonts to avoid memory leaks and for easier-to-read / cleaner code
 */
class FontManager {
   public:
	/**
	 * @param font_name the key to represent the font
	 * @param filepath the path to the font
	 * @param ptsize the size in pixels of the font
	 */
	void Load(const std::string& font_name, const std::string& filepath, uint32_t ptsize);

	/**
	 * @param font_name the key representing the font
	 * @return a Sptr<Font> containing the font
	 * IMPORTANT: the font name must be loaded, since the other case is not handled
	 */
	Sptr<Font> Get(const std::string& font_name);

	/**
	 * @param font_name
	 * @return if the font is already loaded
	 */
	bool Contains(const std::string& font_name);

	/**
	 * Another easy access method to get the font
	 * Same as Sptr<Font> Font::Get(const std::string &font_name);
	 */
	Sptr<Font> operator[](const std::string& font_name);

   private:
	std::unordered_map<std::string, Sptr<Font>> fonts_;
};

}  // namespace libgl

#endif  // LIBGL2D_GFX_FONT_H