#ifndef OMEGA_SCENE_ORTHOGRAPHICCAMERA_HPP
#define OMEGA_SCENE_ORTHOGRAPHICCAMERA_HPP

#include "omega/math/math.hpp"
#include "omega/scene/camera.hpp"
#include "omega/util/types.hpp"

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
    OrthographicCamera(f32 left,
                       f32 right,
                       f32 bottom,
                       f32 top,
                       f32 near = -1.0f,
                       f32 far = 1.0f);

    void set_projection(f32 left,
                        f32 right,
                        f32 bottom,
                        f32 top,
                        f32 near = -1.0f,
                        f32 far = 1.0f);

    f32 get_rotation() const {
        return rotation;
    }
    void set_rotation(f32 rotation) {
        this->rotation = rotation;
    }

    f32 get_width() const {
        return width;
    }
    f32 get_height() const {
        return height;
    }
    f32 get_depth() const {
        return depth;
    }

    /**
     * Converts the screen/pixel coordianates to world coordinates
     * @param vec the coordinates to convert
     */
    math::vec2 project(const math::vec2 &vec,
                       const math::vec2 &screen_res) const;
    /**
     * Updates the view & projection matrix
     *
     * IMPORTANT: must be called before rendering if the camera has changed
     */
    void recalculate_view_matrix() override;

  private:
    f32 width, height, depth;
    f32 rotation = 0.0f;
};
} // namespace omega::scene

#endif // OMEGA_SCENE_ORTHOGRAPHICCAMERA_HPP
