#ifndef OMEGA_GFX_TEXTURE_TEXTUREREGION_H
#define OMEGA_GFX_TEXTURE_TEXTUREREGION_H

#include <string>

#include "omega/gfx/texture/texture.h"
#include "omega/util/util.h"

namespace omega::gfx::texture {

/**
 * Represents a part of a texture only to be loaded by TextureAtlas
 */
class TextureRegion {
  public:
    TextureRegion(Texture *tex, u32 x, u32 y, u32 w, u32 h);
    u32 get_x() const { return rect.x; }
    u32 get_y() const { return rect.y; }
    u32 get_w() const { return rect.w; }
    u32 get_h() const { return rect.h; }
    const glm::rect<u32> &get_rect() const { return rect; }
    Texture *get_texture() const { return texture; }

  private:
    Texture *texture;
    glm::rect<u32> rect;
    std::string region_name;
};
} // namespace omega::gfx::texture

#endif // OMEGA_GFX_TEXTURE_TEXTUREREGION_H