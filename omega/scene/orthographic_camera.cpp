#include "orthographic_camera.h"

namespace omega::scene {

OrthographicCamera::OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top) : Camera::Camera(), rotation(0.0f) {
    position = glm::vec3(0.0f);
    set_projection(left, right, bottom, top);
}

void OrthographicCamera::set_projection(f32 left, f32 right, f32 bottom, f32 top) {
    projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    width = (right - left);
    height = (top - bottom);
}

glm::vec2 OrthographicCamera::project(const glm::vec2 &vec, const glm::vec2 &screen_res) const {
    // convert to world size
    glm::vec2 convert;
    convert.x = vec.x / screen_res.x * width;
    convert.y = vec.y / screen_res.y * height;
    convert += glm::vec2(position.x, position.y); // + glm::vec2(width_ / 2.0f, height_ / 2.0f);
    return convert;
}

void OrthographicCamera::recalculate_view_matrix() {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

    view_matrix = glm::inverse(transform);
}

} // namespace omega::scene