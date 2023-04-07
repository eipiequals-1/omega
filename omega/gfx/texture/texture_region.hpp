#ifndef OMEGA_GFX_TEXTURE_TEXTUREREGION_HPP
#define OMEGA_GFX_TEXTURE_TEXTUREREGION_HPP

#include <string>

#include "omega/gfx/texture/texture.hpp"
#include "omega/util/math.hpp"

namespace omega::gfx::texture {

/**
 * Represents a part of a texture only to be loaded by TextureAtlas
 */
class TextureRegion {
  public:
    TextureRegion(Texture *tex, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
    : texture(tex), rect(x, y, w, h) {}

    uint32_t get_x() const { return rect.x; }
    uint32_t get_y() const { return rect.y; }
    uint32_t get_w() const { return rect.w; }
    uint32_t get_h() const { return rect.h; }
    const glm::rect<uint32_t> &get_rect() const { return rect; }
    Texture *get_texture() const { return texture; }

  private:
    Texture *texture = nullptr;
    glm::rect<uint32_t> rect;
};
} // namespace omega::gfx::texture

#endif // OMEGA_GFX_TEXTURE_TEXTUREREGION_HPP
