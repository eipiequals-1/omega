#include "orthographic_camera.hpp"

namespace omega::scene {

OrthographicCamera::OrthographicCamera(f32 left,
                                       f32 right,
                                       f32 bottom,
                                       f32 top,
                                       f32 near,
                                       f32 far)
    : Camera::Camera() {
    position = math::vec3(0.0f);
    set_projection(left, right, bottom, top, near, far);
}

void OrthographicCamera::set_projection(f32 left,
                                        f32 right,
                                        f32 bottom,
                                        f32 top,
                                        f32 near,
                                        f32 far) {
    projection_matrix = math::ortho(left, right, bottom, top, near, far);
    width = (right - left);
    height = (top - bottom);
    depth = (far - near);
}

math::vec2 OrthographicCamera::project(const math::vec2 &vec,
                                       const math::vec2 &screen_res) const {
    // convert to world size
    math::vec2 convert;
    convert.x = vec.x / screen_res.x * width;
    convert.y = vec.y / screen_res.y * height;
    convert += math::vec2(position.x, position.y);
    return convert;
}

void OrthographicCamera::recalculate_view_matrix() {
    math::mat4 transform = math::translate(math::mat4(1.0f), position) *
                           math::rotate(math::mat4(1.0f),
                                        math::radians(rotation),
                                        math::vec3(0.0f, 0.0f, 1.0f));

    view_matrix = math::inverse(transform);
}

} // namespace omega::scene
