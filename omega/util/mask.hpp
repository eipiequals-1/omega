#ifndef OMEGA_UTIL_MASK_HPP
#define OMEGA_UTIL_MASK_HPP

#include "omega/gfx/texture/texture.hpp"

namespace omega::util {

class Mask {
  public:
    Mask(uint32_t* data, uint32_t width, uint32_t height, int alpha_threshold = 127);
    ~Mask();

    static uptr<Mask> from_texture(
        gfx::texture::Texture *texture, int alpha_threshold = 127);

    bool collide_with(const glm::rectf &rect, const glm::vec2 &mask_pos);
    bool collide_with(const Mask& other, const glm::vec2 &other_pos,
                      const glm::vec2 &mask_pos);
    

  private:
    uint32_t width = 0, height = 0;

    uint32_t* mask_data = nullptr;
};

} // namespace omega::util

#endif // OMEGA_UTIL_MASK_HPP
