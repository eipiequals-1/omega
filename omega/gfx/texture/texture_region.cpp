#include "texture_region.h"

namespace omega {
TextureRegion::TextureRegion(Texture *tex, uint32_t x, uint32_t y, uint32_t w, uint32_t h) : texture_(tex), x_(x), y_(y), w_(w), h_(h) {
}
}  // namespace omega