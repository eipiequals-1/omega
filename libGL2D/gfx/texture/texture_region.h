#ifndef _LIBGL2D_GFX_TEXTURE_TEXTUREREGION_H_
#define _LIBGL2D_GFX_TEXTURE_TEXTUREREGION_H_

#include <string>

#include "libGL2D/gfx/texture/texture.h"
#include "libGL2D/physics/math.h"

namespace libgl {

/**
 * Represents a part of a texture only to be loaded by libgl::TextureAtlas
 */
class TextureRegion {
   public:
	TextureRegion(Texture *tex, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
	uint32_t GetX() const { return x_; }
	uint32_t GetY() const { return y_; }
	uint32_t GetW() const { return w_; }
	uint32_t GetH() const { return h_; }
	glm::rect GetRect() const { return glm::rect(x_, y_, w_, h_); }
	Texture *GetTexture() { return texture_; }

   private:
	Texture *texture_;
	uint32_t x_;
	uint32_t y_;
	uint32_t w_;
	uint32_t h_;
	std::string region_name_;
};
}  // namespace libgl

#endif  // _LIBGL2D_GFX_TEXTURE_TEXTUREREGION_H_