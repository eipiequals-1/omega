#include "perspective_camera.h"

namespace omega {

PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, float yaw, float pitch) : position_(position), front_(0.0f, 0.0f, -1.0f), world_up_(0.0f, 1.0f, 0.0f), yaw_(yaw), pitch_(pitch) {
	SetProjection();
	UpdateViewVectors();
}

void PerspectiveCamera::SetProjection(float fov, float aspect, float near, float far) {
	projection_matrix_ = glm::perspective(glm::radians(fov), aspect, near, far);
}

void PerspectiveCamera::RecalculateViewMatrix() {
	view_matrix_ = glm::lookAt(position_, position_ + front_, up_);
	view_projection_matrix_ = projection_matrix_ * view_matrix_;
}

void PerspectiveCamera::MouseMovement(float dx, float dy, float mouse_sensitivity) {
	dx *= mouse_sensitivity;
	dy *= mouse_sensitivity;
	yaw_ += dx;
	pitch_ += dy;

	if (pitch_ > 89.0f) pitch_ = 89.0f;
	if (pitch_ < -89.0f) pitch_ = -89.0f;
	UpdateViewVectors();
}

void PerspectiveCamera::UpdateViewVectors() {
	glm::vec3 forward;
	forward.x = glm::cos(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_));
	forward.y = glm::sin(glm::radians(pitch_));
	forward.z = glm::sin(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_));
	front_ = glm::normalize(forward);
	right_ = glm::normalize(glm::cross(front_, world_up_));
	up_ = glm::normalize(glm::cross(right_, front_));
}

}  // namespace omega