#ifndef OMEGA_CORE_ORTHOCAMERA_H
#define OMEGA_CORE_ORTHOCAMERA_H

#include "omega/physics/math.h"

namespace omega {

/**
 * A 2D Orthographic Camera for rendering
 * Intended Use:
 *
 * OrthographicCamera cam(left, right, bottom, top);
 * SpriteBatch batch;
 * cam.RecalculateViewMatrix();
 * batch.SetViewProjectionMatrix(cam.GetViewProjectionMatrix());
 * batch.BeginRender();
 *
 * . . .
 *
 * batch.EndRender();
 */
class OrthographicCamera {
   public:
	OrthographicCamera(float left, float right, float bottom, float top);

	const glm::vec3& GetPosition() const { return position_; }
	void SetPosition(const glm::vec3& position) { position_ = position; }

	float GetRotation() const { return rotation_; }
	void SetRotation(float rotation) { rotation_ = rotation; }

	float GetWidth() const { return width_; }
	float GetHeight() const { return height_; }

	const glm::mat4& GetProjectionMatrix() const { return projection_matrix_; }
	const glm::mat4& GetViewMatrix() const { return view_matrix_; }
	const glm::mat4& GetViewProjectionMatrix() const { return view_projection_matrix_; }

	/**
	 * Converts the screen/pixel coordianates to world coordinates
	 * @param vec the coordinates to convert
	 */
	glm::vec2 Project(const glm::vec2& vec, const glm::vec2& screen_res) const;
	/**
	 * Updates the view projection matrix if position, rotation, and/or size have changed
	 *
	 * IMPORTANT: must be called before rendering if the camera has changed
	 */
	void RecalculateViewMatrix();

   private:
	float width_, height_;

	glm::vec3 position_;
	glm::mat4 projection_matrix_;
	glm::mat4 view_matrix_;
	glm::mat4 view_projection_matrix_;
	float rotation_;
};
}  // namespace omega

#endif  // OMEGA_CORE_ORTHOCAMERA_H