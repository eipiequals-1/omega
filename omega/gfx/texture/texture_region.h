#ifndef OMEGA_GFX_TEXTURE_TEXTUREREGION_H
#define OMEGA_GFX_TEXTURE_TEXTUREREGION_H

#include <string>

#include "omega/gfx/texture/texture.h"
#include "omega/physics/math.h"

namespace omega {

/**
 * Represents a part of a texture only to be loaded by TextureAtlas
 */
class TextureRegion {
   public:
	TextureRegion(Texture *tex, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
	uint32_t GetX() const { return rect_.x; }
	uint32_t GetY() const { return rect_.y; }
	uint32_t GetW() const { return rect_.w; }
	uint32_t GetH() const { return rect_.h; }
	const glm::rect<uint32_t> &GetRect() const { return rect_; }
	Texture *GetTexture() const { return texture_; }

   private:
	Texture *texture_;
	glm::rect<uint32_t> rect_;
	std::string region_name_;
};
}  // namespace omega

#endif  // OMEGA_GFX_TEXTURE_TEXTUREREGION_H