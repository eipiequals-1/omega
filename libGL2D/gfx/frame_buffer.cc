#include "frame_buffer.h"

namespace libgl {

FrameBuffer::FrameBuffer(uint32_t width, uint32_t height) : id_(0), width_(width), height_(height), color_buffer_(0), rbo_depth_stencil_(0) {
	glCreateFramebuffers(1, &id_);
	glBindFramebuffer(GL_FRAMEBUFFER, id_);
	// create color buffer
	glCreateTextures(GL_TEXTURE_2D, 1, &color_buffer_);
	glBindTexture(GL_TEXTURE_2D, color_buffer_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// attach to frame buffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_buffer_, 0);
	// create depth and stencil buffer in render buffer
	glCreateRenderbuffers(1, &rbo_depth_stencil_);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth_stencil_);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_depth_stencil_);

	// check if it was successful
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		libgl::Log("FrameBuffer Error: Framebuffer is not complete!");
	}

	// unbind everything
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer() {
	glDeleteFramebuffers(1, &id_);
	glDeleteTextures(1, &color_buffer_);
	glDeleteRenderbuffers(1, &rbo_depth_stencil_);
}

void FrameBuffer::Bind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, id_);
	glViewport(0, 0, width_, height_);
}

void FrameBuffer::Unbind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::BindTexture(uint32_t slot) const {
	glBindTexture(GL_TEXTURE_2D, color_buffer_);
	glActiveTexture(GL_TEXTURE0 + slot);
}

void FrameBuffer::UnbindTexture() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

}  // namespace libgl