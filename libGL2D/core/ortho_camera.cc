#include "ortho_camera.h"

namespace libgl {

OrthoCamera::OrthoCamera(float width, float height, const glm::vec2& screen_res) : width_(width), height_(height) {
	position_.x = width_ / 2.0f;
	position_.y = height_ / 2.0f;
	screen_res_ = screen_res;
	Update();
}

void OrthoCamera::Update() {
	float left = position_.x - width_ / 2.0f;
	float right = left + width_;
	float bottom = position_.y - height_ / 2.0f;
	float top = bottom + height_;
	view_proj_ = glm::ortho(left, right, bottom, top);
}

glm::vec2 OrthoCamera::Project(const glm::vec2& vec) const {
	// convert to world size
	glm::vec2 convert;
	convert.x = vec.x / screen_res_.x * width_;
	convert.y = vec.y / screen_res_.y * height_;
	convert += position_ - glm::vec2(width_ / 2.0f, height_ / 2.0f);
	return convert;
}

}  // namespace libgl