#ifndef OMEGA_GFX_FRAMEBUFFER_H
#define OMEGA_GFX_FRAMEBUFFER_H

#include <GL/gl.h>

#include <cstdint>
#include <vector>

#include "omega/core/using.h"
#include "omega/gfx/texture/texture.h"

namespace omega {

class FrameBuffer {
   public:
	FrameBuffer(uint32_t width, uint32_t height);
	~FrameBuffer();

	void Bind() const;
	void Unbind() const;
	void BindTexture(uint32_t slot = 0) const;
	void UnbindTexture() const;
	void Resize(uint32_t width, uint32_t height);

	uint32_t GetWidth() const { return width_; }
	uint32_t GetHeight() const { return height_; }
	uint32_t GetRenderBufferID() const { return rbo_depth_stencil_; }
	Texture* GetColorBuffer() const { return color_buffer_; }

   private:
	uint32_t id_;

	uint32_t width_;
	uint32_t height_;

	Texture* color_buffer_;
	uint32_t rbo_depth_stencil_;
};

}  // namespace omega

#endif  // OMEGA_GFX_FRAMEBUFFER_H