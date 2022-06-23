#include "orthographic_camera.h"

namespace libgl {

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : position_(0.0f, 0.0f, 0.0f), projection_matrix_(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), view_matrix_(1.0f), rotation_(0.0f) {
	view_projection_matrix_ = projection_matrix_ * view_matrix_;
	width_ = (right - left);
	height_ = (top - bottom);
}

glm::vec2 OrthographicCamera::Project(const glm::vec2& vec, const glm::vec2& screen_res) const {
	// convert to world size
	glm::vec2 convert;
	convert.x = vec.x / screen_res.x * width_;
	convert.y = vec.y / screen_res.y * height_;
	convert += glm::vec2(position_.x, position_.y) - glm::vec2(width_ / 2.0f, height_ / 2.0f);
	return convert;
}

void OrthographicCamera::RecalculateViewMatrix() {
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position_) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation_), glm::vec3(0.0f, 0.0f, 1.0f));

	view_matrix_ = glm::inverse(transform);
	view_projection_matrix_ = projection_matrix_ * view_matrix_;
}

}  // namespace libgl