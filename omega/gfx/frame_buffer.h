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
    FrameBuffer(uint32_t width, uint32_t height);
    ~FrameBuffer();

    void bind() const;
    static void unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void bind_texture(uint32_t slot = 0) const;
    void unbind_texture() const;
    void resize(uint32_t width, uint32_t height);

    uint32_t get_width() const { return width; }
    uint32_t get_height() const { return height; }
    uint32_t get_render_buffer_id() const { return rbo_depth_stencil; }
    sptr<Texture> get_color_buffer() const { return color_buffer; }

  private:
    uint32_t id;

    uint32_t width;
    uint32_t height;

    sptr<Texture> color_buffer;
    uint32_t rbo_depth_stencil;
};

} // namespace omega::gfx

#endif // OMEGA_GFX_FRAMEBUFFER_H