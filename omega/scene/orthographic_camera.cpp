#include "orthographic_camera.h"

namespace omega::scene {

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far) : Camera::Camera() {
    position = glm::vec3(0.0f);
    set_projection(left, right, bottom, top, near, far);
}

void OrthographicCamera::set_projection(float left, float right, float bottom, float top, float near, float far) {
    projection_matrix = glm::ortho(left, right, bottom, top, near, far);
    width = (right - left);
    height = (top - bottom);
    depth = (far - near);
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