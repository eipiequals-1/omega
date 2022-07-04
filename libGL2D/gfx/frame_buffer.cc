#include "frame_buffer.h"

namespace libgl {

FrameBuffer::FrameBuffer(const FrameBufferSpecification& spec) {
	(void)spec;
	glCreateFramebuffers(1, &id_);
	Bind();
}

FrameBuffer::~FrameBuffer() {
	glDeleteFramebuffers(1, &id_);
	glDeleteTextures(1, &color_attachment_);
}

void FrameBuffer::Bind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, id_);
	glViewport(0, 0, specification_.width, specification_.height);
}

void FrameBuffer::Unbind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Resize() {
	glCreateFramebuffers(1, &id_);
	glBindFramebuffer(GL_FRAMEBUFFER, id_);
	glCreateTextures(GL_TEXTURE_2D, 1, &color_attachment_);
	// create color buffer
	glBindTexture(GL_TEXTURE_2D, color_attachment_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, specification_.width, specification_.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_attachment_, 0);
	// create depth and stencil buffer
	glCreateTextures(GL_TEXTURE_2D, 1, &depth_attachment_);
	glBindTexture(GL_TEXTURE_2D, depth_attachment_);
	glTexStorage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, specification_.width, specification_.height);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth_attachment_, 0);
	// check for success
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		libgl::Log("Failed to create FrameBuffer");
	}

	Unbind();
}
}  // namespace libgl