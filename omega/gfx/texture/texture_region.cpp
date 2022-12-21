#include "texture_region.h"

namespace omega::gfx::texture {
TextureRegion::TextureRegion(Texture *tex, uint32_t x, uint32_t y, uint32_t w, uint32_t h) : texture(tex), rect(x, y, w, h) {
}
} // namespace omega::gfx::texture