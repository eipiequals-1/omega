#include "ortho_camera.h"

namespace libGL2D {
OrthoCamera::OrthoCamera(float width, float height) {
	view_proj_ = glm::ortho(0.0f, width, 0.0f, height);
}
}  // namespace libGL2D