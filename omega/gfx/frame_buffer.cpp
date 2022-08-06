#include "frame_buffer.h"

namespace omega {

FrameBuffer::FrameBuffer(uint32_t width, uint32_t height) : id_(0), width_(width), height_(height), color_buffer_(nullptr), rbo_depth_stencil_(0) {
	Resize(width, height);
}

FrameBuffer::~FrameBuffer() {
	glDeleteFramebuffers(1, &id_);
	glDeleteRenderbuffers(1, &rbo_depth_stencil_);
}

void FrameBuffer::Resize(uint32_t width, uint32_t height) {
	if (id_ != 0) {
		glDeleteFramebuffers(1, &id_);
		glDeleteRenderbuffers(1, &rbo_depth_stencil_);
		id_ = 0;
		rbo_depth_stencil_ = 0;
	}
	width_ = width;
	height_ = height;
	glCreateFramebuffers(1, &id_);
	glBindFramebuffer(GL_FRAMEBUFFER, id_);
	GLCheckError();
	// create color buffer
	color_buffer_ = Texture::CreateEmpty(width_, height_, GL_LINEAR, GL_LINEAR);
	// attach to frame buffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_buffer_->GetRendererID(), 0);
	// create depth and stencil buffer in render buffer
	glCreateRenderbuffers(1, &rbo_depth_stencil_);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth_stencil_);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_depth_stencil_);

	// check if it was successful
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		Log("FrameBuffer Error: Framebuffer is not complete!");
	}

	// unbind everything
	color_buffer_->Unbind();
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	GLCheckError();
}

void FrameBuffer::Bind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, id_);
	glViewport(0, 0, width_, height_);
}

void FrameBuffer::Unbind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::BindTexture(uint32_t slot) const {
	color_buffer_->Bind(slot);
}

void FrameBuffer::UnbindTexture() const {
	color_buffer_->Unbind();
}

}  // namespace omega