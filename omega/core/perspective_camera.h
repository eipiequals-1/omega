#ifndef OMEGA_CORE_PERSPECTIVECAMERA_H
#define OMEGA_CORE_PERSPECTIVECAMERA_H

#include "omega/physics/math.h"

namespace omega {

class PerspectiveCamera {
   public:
	PerspectiveCamera(const glm::vec3& position = glm::vec3(0.0f), float yaw = -90.0f, float pitch = 0.0f);
	~PerspectiveCamera() = default;

	void SetProjection(float fov = 45.0f, float aspect = 16.0f / 9.0f, float near = 0.1f, float far = 100.0f);

	const glm::vec3& GetPosition() const { return position_; }
	void SetPosition(const glm::vec3& pos) { position_ = pos; }

	const glm::vec3& GetFront() const { return front_; }
	const glm::vec3& GetRight() const { return right_; }

	const glm::mat4& GetProjectionMatrix() const { return projection_matrix_; }
	const glm::mat4& GetViewMatrix() const { return view_matrix_; }
	const glm::mat4& GetViewProjectionMatrix() const { return view_projection_matrix_; }

	/**
	 * Updates the view projection matrix if position, fov, near, or far plane have changed
	 *
	 * IMPORTANT: must be called before rendering if the camera has changed
	 */
	void RecalculateViewMatrix();
	void MouseMovement(float dx, float dy, float mouse_sensitivity = 0.1f);

   private:
	void UpdateViewVectors();
	// view fields
	glm::vec3 position_;
	glm::vec3 front_;
	glm::vec3 up_;
	glm::vec3 right_;
	glm::vec3 world_up_;
	// euler angles
	float yaw_;    // rotating left and right
	float pitch_;  // rotating up and down

	glm::mat4 projection_matrix_;
	glm::mat4 view_matrix_;
	glm::mat4 view_projection_matrix_;
};

}  // namespace omega

#endif  // OMEGA_CORE_PERSPECTIVECAMERA_H