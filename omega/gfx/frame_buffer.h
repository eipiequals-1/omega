#ifndef OMEGA_GFX_FRAMEBUFFER_H
#define OMEGA_GFX_FRAMEBUFFER_H

#include <GL/gl.h>

#include <cstdint>
#include <vector>

#include "omega/core/using.h"

namespace omega {

class FrameBuffer {
   public:
	FrameBuffer(uint32_t width, uint32_t height);
	~FrameBuffer();

	void Bind() const;
	void Unbind() const;
	void BindTexture(uint32_t slot = 0) const;
	void UnbindTexture() const;

	uint32_t GetWidth() const { return width_; }
	uint32_t GetHeight() const { return height_; }

   private:
	uint32_t id_;

	uint32_t width_;
	uint32_t height_;

	uint32_t color_buffer_;
	uint32_t rbo_depth_stencil_;
};

}  // namespace omega

#endif  // OMEGA_GFX_FRAMEBUFFER_H