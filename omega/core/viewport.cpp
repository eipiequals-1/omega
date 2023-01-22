#include "viewport.hpp"

namespace omega::core {

Viewport::Viewport(ViewportType viewport_type, uint32_t initial_width, uint32_t initial_height) : viewport_type(viewport_type), initial_width(initial_width), initial_height(initial_height), current_width(initial_width), current_height(initial_height) {
    on_resize(initial_width, initial_height);
}

glm::rect<uint32_t> Viewport::on_resize(uint32_t new_width, uint32_t new_height) {
    switch (viewport_type) {
    case ViewportType::fit: {
        const auto fit_aspect_ratio = [](float src_width, float src_height, float max_width, float max_height) {
            const float ratio = glm::min(max_width / src_width, max_height / src_height);
            return glm::vec2(src_width * ratio, src_height * ratio);
        };
        const glm::vec2 viewport_size = fit_aspect_ratio(initial_width, initial_height, new_width, new_height);
        current_width = (uint32_t)glm::round(viewport_size.x);
        current_height = (uint32_t)glm::round(viewport_size.y);
        uint32_t margin_left = (uint32_t)glm::round((new_width - viewport_size.x) / 2.0f);
        uint32_t margin_bottom = (uint32_t)glm::round((new_height - viewport_size.y) / 2.0f);
        glViewport(margin_left, margin_bottom, current_width, current_height);
        return glm::rect<uint32_t>(margin_left, margin_bottom, current_width, current_height);
    }
    case ViewportType::stretch: {
        current_width = new_width;
        current_height = new_height;
        glViewport(0, 0, new_width, new_height);
        return glm::rect<uint32_t>(0, 0, current_width, current_height);
        break;
    }
    default:
        return glm::rect<uint32_t>();
    }
}

} // namespace omega::core
