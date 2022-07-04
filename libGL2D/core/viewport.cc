#include "viewport.h"

namespace libgl {

Viewport::Viewport(ViewportType viewport_type, uint32_t initial_width, uint32_t initial_height) : viewport_type_(viewport_type), initial_width_(initial_width), initial_height_(initial_height) {
	OnResize(initial_width, initial_height);
}

Viewport::~Viewport() {
}

void Viewport::OnResize(uint32_t new_width, uint32_t new_height) {
	const auto fit_aspect_ratio = [](float src_width, float src_height, float max_width, float max_height) {
		const float ratio = glm::min(max_width / src_width, max_height / src_height);
		return glm::vec2(src_width * ratio, src_height * ratio);
	};

	switch (viewport_type_) {
	case ViewportType::kFit: {
		const glm::vec2 viewport_size = fit_aspect_ratio(initial_width_, initial_height_, new_width, new_height);
		float viewport_width = glm::round(viewport_size.x);
		float viewport_height = glm::round(viewport_size.y);
		float margin_left = glm::round((new_width - viewport_size.x) / 2.0f);
		float margin_bottom = glm::round((new_height - viewport_size.y) / 2.0f);
		glViewport((GLint)margin_left, (GLint)margin_bottom, (GLint)viewport_width, (GLint)viewport_height);
		break;
	}
	case ViewportType::kStretch: {
		glViewport(0, 0, new_width, new_height);
		break;
	}
	default:
		break;
	}
}

}  // namespace libgl