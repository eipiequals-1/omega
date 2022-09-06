#include "perspective_camera.h"

namespace omega::core {

PerspectiveCamera::PerspectiveCamera(const glm::vec3 &position, f32 yaw, f32 pitch) : Camera::Camera(), front(0.0f, 0.0f, -1.0f), world_up(0.0f, 1.0f, 0.0f), yaw(yaw), pitch(pitch) {
    this->position = position;
    set_projection();
    update_view_vectors();
}

void PerspectiveCamera::set_projection(f32 fov, f32 aspect, f32 near, f32 far) {
    projection_matrix = glm::perspective(glm::radians(fov), aspect, near, far);
}

void PerspectiveCamera::recalculate_view_matrix() {
    view_matrix = glm::lookAt(position, position + front, up);
}

void PerspectiveCamera::mouse_movement(f32 dx, f32 dy, f32 mouse_sensitivity) {
    dx *= mouse_sensitivity;
    dy *= mouse_sensitivity;
    yaw += dx;
    pitch += dy;

    constexpr f32 max_pitch = 90.0f; // cannot rotate 360 deg up and down
    if (pitch > max_pitch)
        pitch = max_pitch;
    if (pitch < -max_pitch)
        pitch = -max_pitch;
    update_view_vectors();
}

void PerspectiveCamera::update_view_vectors() {
    glm::vec3 forward;
    forward.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    forward.y = glm::sin(glm::radians(pitch));
    forward.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    front = glm::normalize(forward);
    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));
}

} // namespace omega