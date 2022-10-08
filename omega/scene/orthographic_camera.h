#ifndef OMEGA_CORE_ORTHOCAMERA_H
#define OMEGA_CORE_ORTHOCAMERA_H

#include "omega/scene/camera.h"
#include "omega/util/util.h"

namespace omega::scene {

/**
 * A 2D Orthographic Camera for rendering
 * Intended Use:
 *
 * OrthographicCamera cam(left, right, bottom, top);
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
    OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top);

    void set_projection(f32 left, f32 right, f32 bottom, f32 top);

    f32 get_rotation() const { return rotation; }
    void set_rotation(f32 rotation) { this->rotation = rotation; }

    f32 get_width() const { return width; }
    f32 get_height() const { return height; }

    /**
     * Converts the screen/pixel coordianates to world coordinates
     * @param vec the coordinates to convert
     */
    glm::vec2 project(const glm::vec2 &vec, const glm::vec2 &screen_res) const;
    /**
     * Updates the view projection matrix if position, rotation, and/or size have changed
     *
     * IMPORTANT: must be called before rendering if the camera has changed
     */
    void recalculate_view_matrix() override;

  private:
    f32 width, height;
    f32 rotation;
};
} // namespace omega::scene

#endif // OMEGA_CORE_ORTHOCAMERA_H