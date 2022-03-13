#ifndef _LIBGL2D_CORE_ORTHOCAMERA_H_
#define _LIBGL2D_CORE_ORTHOCAMERA_H_

#include "libGL2D/physics/math.h"

namespace libGL2D {

class OrthoCamera {
   public:
	OrthoCamera(float width, float height);

	void SetPosition(const glm::vec2& pos) {
		position_ = pos;
	}

	const glm::mat4& GetViewProjectionMatrix() const { return view_proj_; }

   private:
	glm::mat4 view_proj_;
	glm::vec2 position_;
};
}  // namespace libGL2D

#endif  // _LIBGL2D_CORE_ORTHOCAMERA_H_