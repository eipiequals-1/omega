#include "viewport.h"

namespace omega {

Viewport::Viewport(ViewportType viewport_type, uint32_t initial_width, uint32_t initial_height) : viewport_type_(viewport_type), initial_width_(initial_width), initial_height_(initial_height), current_width_(initial_width), current_height_(initial_height) {
	OnResize(initial_width, initial_height);
}

Viewport::~Viewport() {
}

void Viewport::OnResize(uint32_t new_width, uint32_t new_height) {
	switch (viewport_type_) {
	case ViewportType::kFit: {
		const auto fit_aspect_ratio = [](float src_width, float src_height, float max_width, float max_height) {
			const float ratio = glm::min(max_width / src_width, max_height / src_height);
			return glm::vec2(src_width * ratio, src_height * ratio);
		};
		const glm::vec2 viewport_size = fit_aspect_ratio(initial_width_, initial_height_, new_width, new_height);
		current_width_ = (uint32_t)glm::round(viewport_size.x);
		current_height_ = (uint32_t)glm::round(viewport_size.y);
		uint32_t margin_left = (uint32_t)glm::round((new_width - viewport_size.x) / 2.0f);
		uint32_t margin_bottom = (uint32_t)glm::round((new_height - viewport_size.y) / 2.0f);
		glViewport(margin_left, margin_bottom, current_width_, current_height_);
		break;
	}
	case ViewportType::kStretch: {
		current_width_ = new_width;
		current_height_ = new_height;
		glViewport(0, 0, new_width, new_height);
		break;
	}
	default:
		break;
	}
}

}  // namespace omega