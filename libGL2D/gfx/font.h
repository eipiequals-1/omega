#ifndef _LIBGL2D_GFX_FONT_H_
#define _LIBGL2D_GFX_FONT_H_

#include <SDL2/SDL_ttf.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "libGL2D/core/using.h"
#include "libGL2D/physics/math.h"

namespace libgl {

class Font {
   public:
	Font(const std::string& path, uint32_t size);
	~Font();
	SDL_Surface* RenderText(const std::string& text, const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

   private:
	uint32_t size_;
	TTF_Font* font_;
};

class FontManager {
   public:
	void Load(const std::string& font_name, const std::string& filepath, uint32_t ptsize);
	Sptr<Font> Get(const std::string& font_name);
	bool Contains(const std::string& font_name);

	Sptr<Font> operator[](const std::string& font_name);

   private:
	std::unordered_map<std::string, Sptr<Font>> fonts_;
};

}  // namespace libgl

#endif  // _LIBGL2D_GFX_FONT_H_