#ifndef OMEGA_GFX_TEXTURE_TEXTUREREGION_HPP
#define OMEGA_GFX_TEXTURE_TEXTUREREGION_HPP

#include <string>

#include "omega/gfx/texture/texture.hpp"
#include "omega/math/math.hpp"

namespace omega::gfx::texture {

/**
 * Represents a part of a texture only to be loaded by TextureAtlas
 */
class TextureRegion {
  public:
    TextureRegion(Texture *tex, u32 x, u32 y, u32 w, u32 h)
        : texture(tex), rect(x, y, w, h) {}

    const math::rect<u32> &get_rect() const {
        return rect;
    }
    Texture *get_texture() const {
        return texture;
    }

  private:
    Texture *texture = nullptr;
    math::rect<u32> rect;
};
} // namespace omega::gfx::texture

#endif // OMEGA_GFX_TEXTURE_TEXTUREREGION_HPP
