#ifndef OMEGA_SCENE_CAMERA_HPP
#define OMEGA_SCENE_CAMERA_HPP

#include "omega/util/util.hpp"

namespace omega::scene {

/**
 * Interface for a Camera representing both a projection and view matrix
 */
class Camera {
  public:
    glm::vec3 position{0.0f};

    Camera() = default;
    virtual ~Camera() = default;

    /**
     * @return the projection matrix
     */
    const glm::mat4 &get_projection_matrix() const { return projection_matrix; }

    /**
     * @return the view matrix
     */
    const glm::mat4 &get_view_matrix() const { return view_matrix; }

    /**
     * @return the combined view projection matrix
     */
    glm::mat4 get_view_projection_matrix() const { return projection_matrix * view_matrix; }

    virtual void recalculate_view_matrix() = 0;

  protected:
    glm::mat4 projection_matrix;
    glm::mat4 view_matrix;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_CAMERA_HPP
