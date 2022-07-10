#ifndef OMEGA_CORE_VIEWPORT_H
#define OMEGA_CORE_VIEWPORT_H

#include <GL/gl.h>

#include "omega/physics/math.h"

namespace omega {

enum class ViewportType {
	kFit,      // keep aspect ratio to take up max space on the screen
	kStretch,  // world is scaled to take up the full screen
};

class Viewport {
   public:
	Viewport(ViewportType viewport_type, uint32_t initial_width, uint32_t initial_height);
	virtual ~Viewport();

	virtual void OnResize(uint32_t new_width, uint32_t new_height);
	uint32_t GetViewportWidth() const { return current_width_; }
	uint32_t GetViewportHeight() const { return current_height_; }

   private:
	ViewportType viewport_type_;
	uint32_t initial_width_;
	uint32_t initial_height_;
	uint32_t current_width_;
	uint32_t current_height_;
};

}  // namespace omega

#endif  // OMEGA_CORE_VIEWPORT_H