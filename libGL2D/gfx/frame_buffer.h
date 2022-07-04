#ifndef _LIBGL2D_GFX_FRAMEBUFFER_H_
#define _LIBGL2D_GFX_FRAMEBUFFER_H_

#include <GL/gl.h>

#include <cstdint>

#include "libGL2D/core/using.h"

namespace libgl {

struct FrameBufferSpecification {
	uint32_t width, height;
	uint32_t samples = 1;
	bool swapChainTarget = false;
};

class FrameBuffer {
   public:
	FrameBuffer(const FrameBufferSpecification& spec);
	virtual ~FrameBuffer();

	const FrameBufferSpecification& GetSpecification() const {
		return specification_;
	}

	uint32_t GetColorAttachmentID() const {
		return color_attachment_;
	}

	void Bind() const;
	void Unbind() const;
	// recreate framebuffer
	void Resize();

   private:
	uint32_t id_;
	uint32_t color_attachment_;
	uint32_t depth_attachment_;
	FrameBufferSpecification specification_;
};

}  // namespace libgl

#endif  // _LIBGL2D_GFX_FRAMEBUFFER_H_