#ifndef OMEGA_SCENE_CAMERA_H
#define OMEGA_SCENE_CAMERA_H

#include "omega/physics/math.h"

namespace omega {

class Camera {
   public:
	Camera();
	virtual ~Camera() = default;

	const glm::vec3 &GetPosition() const { return position_; }
	void SetPosition(const glm::vec3 &position) { position_ = position; }

	const glm::mat4 &GetProjectionMatrix() const { return projection_matrix_; }
	const glm::mat4 &GetViewMatrix() const { return view_matrix_; }
	glm::mat4 GetViewProjectionMatrix() const { return projection_matrix_ * view_matrix_; }

	virtual void RecalculateViewMatrix() = 0;

   protected:
	glm::vec3 position_;
	glm::mat4 projection_matrix_;
	glm::mat4 view_matrix_;
};

}  // namespace omega

#endif  // OMEGA_SCENE_CAMERA_H