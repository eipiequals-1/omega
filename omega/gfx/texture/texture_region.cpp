#include "texture_region.h"

namespace omega::gfx::texture {
TextureRegion::TextureRegion(Texture *tex, u32 x, u32 y, u32 w, u32 h) : texture(tex), rect(x, y, w, h) {
}
} // namespace omega::gfx::texture