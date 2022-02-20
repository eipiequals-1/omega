#ifndef _LIBGL2D_GFX_TEXTURE_TEXTUREATLAS_H_
#define _LIBGL2D_GFX_TEXTURE_TEXTUREATLAS_H_

#include <unordered_map>
#include <vector>

#include "libGL2D/gfx/texture/texture.h"

namespace libGL2D {

struct TextureData {
	Texture *texture;
	uint32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;
};

class TextureAtlas {
   public:
	TextureAtlas(const std::string &atlas_file_path);
	Texture *Get(const std::string &texture_name);

   private:
	std::unordered_map<std::string, Texture *> textures_;
};
}  // namespace libGL2D

#endif  // _LIBGL2D_GFX_TEXTURE_TEXTUREATLAS_H_