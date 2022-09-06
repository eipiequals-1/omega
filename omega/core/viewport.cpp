#include "viewport.h"

namespace omega::core {

Viewport::Viewport(ViewportType viewport_type, u32 initial_width, u32 initial_height) : viewport_type(viewport_type), initial_width(initial_width), initial_height(initial_height), current_width(initial_width), current_height(initial_height) {
    on_resize(initial_width, initial_height);
}

Viewport::~Viewport() {
}

void Viewport::on_resize(u32 new_width, u32 new_height) {
    switch (viewport_type) {
    case ViewportType::k_fit: {
        const auto fit_aspect_ratio = [](f32 src_width, f32 src_height, f32 max_width, f32 max_height) {
            const f32 ratio = glm::min(max_width / src_width, max_height / src_height);
            return glm::vec2(src_width * ratio, src_height * ratio);
        };
        const glm::vec2 viewport_size = fit_aspect_ratio(initial_width, initial_height, new_width, new_height);
        current_width = (u32)glm::round(viewport_size.x);
        current_height = (u32)glm::round(viewport_size.y);
        // u32 margin_left = (u32)glm::round((new_width - viewport_size.x) / 2.0f);
        // u32 margin_bottom = (u32)glm::round((new_height - viewport_size.y) / 2.0f);
        // glViewport(margin_left, margin_bottom, current_width_, current_height_);
        break;
    }
    case ViewportType::k_stretch: {
        current_width = new_width;
        current_height = new_height;
        glViewport(0, 0, new_width, new_height);
        break;
    }
    default:
        break;
    }
}

} // namespace omega