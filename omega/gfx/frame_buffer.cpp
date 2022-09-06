#include "frame_buffer.h"

namespace omega::gfx {

FrameBuffer::FrameBuffer(u32 width, u32 height) : id(0), width(width), height(height), color_buffer(nullptr), rbo_depth_stencil(0) {
    resize(width, height);
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &id);
    glDeleteRenderbuffers(1, &rbo_depth_stencil);
}

void FrameBuffer::resize(u32 width, u32 height) {
    if (id != 0) {
        glDeleteFramebuffers(1, &id);
        glDeleteRenderbuffers(1, &rbo_depth_stencil);
        id = 0;
        rbo_depth_stencil = 0;
    }
    this->width = width;
    this->height = height;
    glCreateFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glCheckError();
    // create color buffer
    color_buffer = Texture::create_empty(width, height, GL_LINEAR, GL_LINEAR);
    // attach to frame buffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_buffer->get_renderer_id(), 0);
    // create depth and stencil buffer in render buffer
    glCreateRenderbuffers(1, &rbo_depth_stencil);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth_stencil);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_depth_stencil);

    // check if it was successful
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        util::log("FrameBuffer Error: Framebuffer is not complete!");
    }

    // unbind everything
    color_buffer->unbind();
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glCheckError();
}

void FrameBuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glViewport(0, 0, width, height);
}

void FrameBuffer::unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::bind_texture(u32 slot) const {
    color_buffer->bind(slot);
}

void FrameBuffer::unbind_texture() const {
    color_buffer->unbind();
}

} // namespace omega