#ifndef OMEGA_SCENE_CAMERA_H
#define OMEGA_SCENE_CAMERA_H

#include "omega/util/util.h"

namespace omega::scene {

class Camera {
  public:
    Camera() : position(0.0f) {}
    virtual ~Camera() = default;

    const glm::vec3 &get_position() const { return position; }
    void set_position(const glm::vec3 &position) { this->position = position; }

    const glm::mat4 &get_projection_matrix() const { return projection_matrix; }
    const glm::mat4 &get_view_matrix() const { return view_matrix; }
    glm::mat4 get_view_projection_matrix() const { return projection_matrix * view_matrix; }

    virtual void recalculate_view_matrix() = 0;

  protected:
    glm::vec3 position;
    glm::mat4 projection_matrix;
    glm::mat4 view_matrix;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_CAMERA_H