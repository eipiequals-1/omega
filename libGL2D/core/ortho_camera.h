#ifndef _LIBGL2D_CORE_ORTHOCAMERA_H_
#define _LIBGL2D_CORE_ORTHOCAMERA_H_

#include "libGL2D/physics/math.h"

namespace libgl {

class OrthoCamera {
   public:
	OrthoCamera(float width, float height, const glm::vec2& screen_res);

	void set_position(const glm::vec2& pos) { position_ = pos; }
	void set_screen_res(const glm::vec2& screen_res) { screen_res_ = screen_res; }
	void set_x(float x) { position_.x = x; }
	void set_y(float y) { position_.y = y; }
	void set_w(float w) { width_ = w; }
	void set_h(float h) { height_ = h; }

	const glm::vec2& get_position() const { return position_; }
	float get_x() const { return position_.x; }
	float get_y() const { return position_.y; }
	float get_width() const { return width_; }
	float get_height() const { return height_; }

	bool InView(float x, float y) const {
		return x >= position_.x - width_ / 2.0f && x <= position_.x + width_ / 2.0f && y >= position_.y - height_ / 2.0f && y <= position_.y + height_ / 2.0f;
	}

	void Update();
	const glm::mat4& GetViewProjectionMatrix() const { return view_proj_; }
	glm::vec2 Project(const glm::vec2& vec) const;

   private:
	float width_, height_;
	glm::vec2 screen_res_;
	glm::mat4 view_proj_;
	glm::vec2 position_;
};
}  // namespace libgl

#endif  // _LIBGL2D_CORE_ORTHOCAMERA_H_