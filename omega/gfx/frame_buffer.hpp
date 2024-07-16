#ifndef OMEGA_GFX_FRAMEBUFFER_HPP
#define OMEGA_GFX_FRAMEBUFFER_HPP

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "omega/gfx/gl.hpp"
#include "omega/gfx/texture/texture.hpp"
#include "omega/util/std.hpp"
#include "omega/util/types.hpp"
#include "omega/util/util.hpp"

namespace omega::gfx {

using namespace omega::util;

using namespace omega::gfx::texture;

struct FrameBufferAttachment {
    u32 id = 0;
    u32 width = 0, height = 0;
    std::string name;

    TextureFormat internal_fmt = TextureFormat::RGBA;
    TextureFormat external_fmt = TextureFormat::RGBA;

    TextureParam min_filter = TextureParam::NEAREST,
                 mag_filter = TextureParam::NEAREST,
                 wrap_s = TextureParam::REPEAT, wrap_t = TextureParam::REPEAT;
    bool draw_buffer = true;

    void init(u32 width, u32 height) {
        if (id != 0) {
            glDeleteTextures(1, &id);
            id = 0;
        }
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     (i32)internal_fmt,
                     width,
                     height,
                     0,
                     (i32)external_fmt,
                     GL_FLOAT,
                     nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (i32)min_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (i32)mag_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (i32)wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (i32)wrap_t);
    }

    void bind(u32 position) {
        glActiveTexture(GL_TEXTURE0 + position);
        glBindTexture(GL_TEXTURE_2D, id);
    }

    ~FrameBufferAttachment() {
        glDeleteTextures(1, &id);
        id = 0;
    }
};

/**
 * Wrapper for OpenGL frame buffers
 */
class FrameBuffer {
  public:
    FrameBuffer(u32 width,
                u32 height,
                const std::vector<FrameBufferAttachment> &attachments);

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

    u32 get_width() const {
        return width;
    }
    u32 get_height() const {
        return height;
    }

    /**
     * Resizes the frame buffer with the new parameters
     * according to the attachments
     * @param width
     * @param height
     */
    void resize(u32 width,
                u32 height,
                const std::vector<std::string> &attachments);

    /**
     * @returns the render buffer id (depth and stencil buffers)
     */
    u32 get_render_buffer_id() const {
        return rbo_depth_stencil;
    }

    FrameBufferAttachment &get_attachment(const std::string &attachment_name) {
        return attachments[attachment_name];
    }

  private:
    std::unordered_map<std::string, FrameBufferAttachment> attachments;
    // width and height of default color buffer
    u32 width = 0, height = 0;

    // gl objects
    u32 id = 0;

    u32 rbo_depth_stencil = 0;
};

} // namespace omega::gfx

#endif // OMEGA_GFX_FRAMEBUFFER_HPP
