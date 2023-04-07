#ifndef OMEGA_CORE_ORTHOGRAPHICCAMERA_HPP
#define OMEGA_CORE_ORTHOGRAPHICCAMERA_HPP

#include "omega/scene/camera.hpp"
#include "omega/util/math.hpp"

namespace omega::scene {

/**
 * A general purpose Orthographic Camera for rendering
 * Intended Use:
 *
 * OrthographicCamera cam(left, right, bottom, top, near, far);
 * SpriteBatch batch;
 * cam.recalculate_view_matrix();
 * batch.set_view_projection_matrix(cam.get_view_projection_matrix());
 * batch.begin_render();
 *
 * . . .
 *
 * batch.end_render();
 */
class OrthographicCamera : public Camera {
  public:
    OrthographicCamera(float left, float right,
                       float bottom, float top,
                       float near = -1.0f, float far = 1.0f);

    void set_projection(float left, float right,
                        float bottom, float top,
                        float near = -1.0f, float far = 1.0f);

    float get_rotation() const { return rotation; }
    void set_rotation(float rotation) { this->rotation = rotation; }

    float get_width() const { return width; }
    float get_height() const { return height; }
    float get_depth() const { return depth; }

    /**
     * Converts the screen/pixel coordianates to world coordinates
     * @param vec the coordinates to convert
     */
    glm::vec2 project(const glm::vec2 &vec, const glm::vec2 &screen_res) const;
    /**
     * Updates the view & projection matrix
     *
     * IMPORTANT: must be called before rendering if the camera has changed
     */
    void recalculate_view_matrix() override;

  private:
    float width, height, depth;
    float rotation = 0.0f;
};
} // namespace omega::scene

#endif // OMEGA_CORE_ORTHOGRAPHICCAMERA_HPP
