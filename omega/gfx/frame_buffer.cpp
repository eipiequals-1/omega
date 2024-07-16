#include "frame_buffer.hpp"

#include <array>

#include "omega/gfx/gl.hpp"

namespace omega::gfx {

FrameBuffer::FrameBuffer(
    u32 width,
    u32 height,
    const std::vector<FrameBufferAttachment> &attachments) {
    std::vector<std::string> to_init;
    for (const auto &attachment : attachments) {
        this->attachments[attachment.name] = attachment;
        to_init.push_back(attachment.name);
    }
    // create the framebuffer with all the given attachments
    resize(width, height, to_init);
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &id);
    glDeleteRenderbuffers(1, &rbo_depth_stencil);
}

void FrameBuffer::resize(u32 width,
                         u32 height,
                         const std::vector<std::string> &attachments) {
    if (id != 0) {
        glDeleteFramebuffers(1, &id);
        glDeleteRenderbuffers(1, &rbo_depth_stencil);
        id = 0;
        rbo_depth_stencil = 0;
    }
    this->width = width;
    this->height = height;
#ifdef EMSCRIPTEN
    glGenFramebuffers(1, &id);
#else
    glCreateFramebuffers(1, &id);
#endif
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    // initialize the attachments
    u32 i = 0;
    for (const auto &attachment_name : attachments) {
        auto &attach = this->attachments[attachment_name];
        attach.init(attach.width, attach.height);
        // attach to framebuffer
        if (attach.draw_buffer) {
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_COLOR_ATTACHMENT0 + i,
                                   GL_TEXTURE_2D,
                                   attach.id,
                                   0);
            ++i;
        } else {
            // TODO: should be able to have both depth attachment and other
            // buffers
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_DEPTH_ATTACHMENT,
                                   GL_TEXTURE_2D,
                                   attach.id,
                                   0);
#ifndef EMSCRIPTEN
            glDrawBuffer(GL_NONE);
#endif
            glReadBuffer(GL_NONE);
        }
    }

    if (i > 0) {
        u32 draw_buffers[i];
        for (u32 idx = 0; idx < i; ++idx) {
            draw_buffers[idx] = GL_COLOR_ATTACHMENT0 + idx;
        }
        glDrawBuffers(i, draw_buffers);
    }

    // create depth and stencil buffer in render buffer
    if (i > 0) {
#ifdef EMSCRIPTEN
        glGenRenderbuffers(1, &rbo_depth_stencil);
#else
        glCreateRenderbuffers(1, &rbo_depth_stencil);
#endif
        glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth_stencil);

#ifdef EMSCRIPTEN
        glRenderbufferStorage(
            GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                  GL_DEPTH_ATTACHMENT,
                                  GL_RENDERBUFFER,
                                  rbo_depth_stencil);
#else
        glRenderbufferStorage(
            GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                  GL_DEPTH_STENCIL_ATTACHMENT,
                                  GL_RENDERBUFFER,
                                  rbo_depth_stencil);
#endif
    }
    // check if it was successful
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        util::warn("Frame Buffer Error: Frame Buffer is not complete!");
    }

    // unbind everything
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    check_error();
}

void FrameBuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glViewport(0, 0, width, height);
}

} // namespace omega::gfx
