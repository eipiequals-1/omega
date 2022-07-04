#ifndef _LIBGL2D_CORE_VIEWPORT_H_
#define _LIBGL2D_CORE_VIEWPORT_H_

#include <GL/gl.h>

#include "libGL2D/physics/math.h"

namespace libgl {

enum class ViewportType {
	kFit,      // keep aspect ratio to take up max space on the screen
	kStretch,  // world is scaled to take up the full screen
};

class Viewport {
   public:
	Viewport(ViewportType viewport_type, uint32_t initial_width, uint32_t initial_height);
	virtual ~Viewport();

	virtual void OnResize(uint32_t new_width, uint32_t new_height);

   private:
	ViewportType viewport_type_;
	uint32_t initial_width_;
	uint32_t initial_height_;
};

}  // namespace libgl

#endif  // _LIBGL2D_CORE_VIEWPORT_H_