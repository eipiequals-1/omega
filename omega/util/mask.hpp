#ifndef OMEGA_UTIL_MASK_HPP
#define OMEGA_UTIL_MASK_HPP

#include "omega/gfx/texture/texture.hpp"

namespace omega::util {

class Mask {
  public:
    Mask(u32 *data, u32 width, u32 height, i32 alpha_threshold = 127);
    ~Mask();

    static uptr<Mask> from_texture(gfx::texture::Texture *texture,
                                   i32 alpha_threshold = 127);

    bool collide_with(const math::rectf &rect, const math::vec2 &mask_pos);
    bool collide_with(const Mask &other,
                      const math::vec2 &other_pos,
                      const math::vec2 &mask_pos);

  private:
    u32 width = 0, height = 0;

    u32 *mask_data = nullptr;
};

} // namespace omega::util

#endif // OMEGA_UTIL_MASK_HPP
