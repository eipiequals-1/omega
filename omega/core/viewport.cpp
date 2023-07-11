#include "viewport.hpp"

namespace omega::core {

Viewport::Viewport(
    ViewportType viewport_type, u32 initial_width, u32 initial_height
) : viewport_type(viewport_type),
    initial_width(initial_width),
    initial_height(initial_height),
    current_width(initial_width),
    current_height(initial_height) {
    
    on_resize(initial_width, initial_height);
}

math::rect<u32> Viewport::on_resize(u32 new_width,
                                        u32 new_height) {
    switch (viewport_type) {
    case ViewportType::fit: {
        const auto fit_aspect_ratio = [](f32 src_width, f32 src_height, 
                                         f32 max_width, f32 max_height) {

            const f32 ratio = math::min(max_width / src_width,
                                         max_height / src_height);
            return math::vec2(src_width * ratio, src_height * ratio);
        };
        const math::vec2 viewport_size = fit_aspect_ratio(
            initial_width,
            initial_height,
            new_width,
            new_height
        );

        current_width = (u32)math::round(viewport_size.x);
        current_height = (u32)math::round(viewport_size.y);

        u32 margin_left = (u32)math::round(
            (new_width - viewport_size.x) / 2.0f
        );
        u32 margin_bottom = (u32)math::round(
            (new_height - viewport_size.y) / 2.0f
        );

        glViewport(margin_left, margin_bottom, current_width, current_height);
        return math::rect<u32>(margin_left, margin_bottom, current_width,
                                   current_height);
    }
    case ViewportType::stretch: {
        current_width = new_width;
        current_height = new_height;
        glViewport(0, 0, new_width, new_height);
        return math::rect<u32>(0, 0, current_width, current_height);
        break;
    }
    default:
        return math::rect<u32>();
    }
}

} // namespace omega::core
