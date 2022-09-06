#ifndef OMEGA_GFX_FRAMEBUFFER_H
#define OMEGA_GFX_FRAMEBUFFER_H

#include <GL/gl.h>

#include <cstdint>
#include <vector>

#include "omega/gfx/texture/texture.h"
#include "omega/util/util.h"

namespace omega::gfx {

using namespace omega::util;

using namespace omega::gfx::texture;

class FrameBuffer {
  public:
    FrameBuffer(u32 width, u32 height);
    ~FrameBuffer();

    void bind() const;
    void unbind() const;
    void bind_texture(u32 slot = 0) const;
    void unbind_texture() const;
    void resize(u32 width, u32 height);

    u32 get_width() const { return width; }
    u32 get_height() const { return height; }
    u32 get_render_buffer_id() const { return rbo_depth_stencil; }
    sptr<Texture> get_color_buffer() const { return color_buffer; }

  private:
    u32 id;

    u32 width;
    u32 height;

    sptr<Texture> color_buffer;
    u32 rbo_depth_stencil;
};

} // namespace omega::gfx

#endif // OMEGA_GFX_FRAMEBUFFER_H