#include "perspective_camera.hpp"

namespace omega::scene {

PerspectiveCamera::PerspectiveCamera(const math::vec3 &position,
                                     f32 yaw,
                                     f32 pitch) : Camera::Camera(),
                                                    front(0.0f, 0.0f, -1.0f),
                                                    world_up(0.0f, 1.0f, 0.0f),
                                                    yaw(yaw),
                                                    pitch(pitch) {
    this->position = position;
    set_projection();
    update_view_vectors();
}

void PerspectiveCamera::set_projection(f32 fov, f32 aspect,
                                       f32 near, f32 far) {
    projection_matrix = math::perspective(math::radians(fov), aspect, near, far);
}

void PerspectiveCamera::recalculate_view_matrix() {
    view_matrix = math::lookAt(position, position + front, up);
}

void PerspectiveCamera::mouse_movement(f32 dx, f32 dy) {
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
    math::vec3 forward;
    forward.x = math::cos(math::radians(yaw)) * math::cos(math::radians(pitch));
    forward.y = math::sin(math::radians(pitch));
    forward.z = math::sin(math::radians(yaw)) * math::cos(math::radians(pitch));
    front = math::normalize(forward);
    right = math::normalize(math::cross(front, world_up));
    up = math::normalize(math::cross(right, front));
}

} // namespace omega
