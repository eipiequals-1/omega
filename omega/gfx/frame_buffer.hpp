#ifndef OMEGA_GFX_FRAMEBUFFER_HPP
#define OMEGA_GFX_FRAMEBUFFER_HPP

#include "omega/gfx/gl.hpp"

#include <cstdint>
#include <vector>

#include "omega/gfx/texture/texture.hpp"
#include "omega/util/util.hpp"

namespace omega::gfx {

using namespace omega::util;

using namespace omega::gfx::texture;

/**
 * Wrapper for OpenGL frame buffers
 */
class FrameBuffer {
  public:
    FrameBuffer(uint32_t width, uint32_t height);
    ~FrameBuffer();

    /**
     * binds the current frame buffer
     * and calls sets the whole frame buffer as the viewport
     */
    void bind() const;

    /**
     * unbinds the frame buffer (i.e. binds to the window frame buffer)
     */
    static void unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    /**
     * Binds the texture and sets it to the "slot" active texture
     * @param slot to bind the texture to
     */
    void bind_texture(uint32_t slot = 0) const;

    /**
     * unbinds the texture
     */
    void unbind_texture() const;

    /**
     * Resizes the frame buffer with the current dimensions
     * @param width
     * @param height
     */
    void resize(uint32_t width, uint32_t height);

    /**
     * @returns the width
     */
    uint32_t get_width() const { return width; }

    /**
     * @returns the height
     */
    uint32_t get_height() const { return height; }

    /**
     * @returns the render buffer id (depth and stencil buffers)
     */
    uint32_t get_render_buffer_id() const { return rbo_depth_stencil; }

    /**
     * @returns the color buffer
     */
    sptr<Texture> get_color_buffer() const { return color_buffer; }

  private:
    // dimensions
    uint32_t width;
    uint32_t height;

    // gl objects
    uint32_t id = 0;

    sptr<Texture> color_buffer = nullptr;
    uint32_t rbo_depth_stencil = 0;
};

} // namespace omega::gfx

#endif // OMEGA_GFX_FRAMEBUFFER_HPP
