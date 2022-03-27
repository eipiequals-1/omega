#include "ortho_camera.h"

namespace libgl {

OrthoCamera::OrthoCamera(float width, float height) : width_(width), height_(height) {
	position_.x = width_ / 2.0f;
	position_.y = height_ / 2.0f;
	Update();
}

void OrthoCamera::Update() {
	float left = position_.x - width_ / 2.0f;
	float right = left + width_;
	float bottom = position_.y - height_ / 2.0f;
	float top = bottom + height_;
	view_proj_ = glm::ortho(left, right, bottom, top);
}

}  // namespace libgl