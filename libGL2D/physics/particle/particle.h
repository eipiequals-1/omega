#ifndef _LIBGL2D_PHYSICS_PARTICLE_PARTICLE_H_
#define _LIBGL2D_PHYSICS_PARTICLE_PARTICLE_H_

#include "libGL2D/core/using.h"
#include "libGL2D/physics/math.h"
#include "libGL2D/physics/random.h"

namespace libgl {

class Particle {
   public:
	Particle();
	virtual ~Particle();

	void Update(float dt);
	bool is_dead() const {
		return timer_ > lifespan_;
	}
	const glm::vec2 &get_pos() { return pos_; }
	const glm::vec2 &get_vel() const { return vel_; }
	const glm::vec4 &get_color() const { return color_; }
	float get_w() const {
		return w_;
	}
	float get_h() const {
		return h_;
	}
	void set_pos(const glm::vec2 &p) {
		pos_ = p;
	}
	void set_vel(const glm::vec2 &v) {
		vel_ = v;
	}
	void set_lifespan(float l) {
		lifespan_ = l;
	}
	void set_color(const glm::vec4 &c) {
		color_ = c;
	}
	void set_w(float w) {
		w_ = w;
	}
	void set_h(float h) {
		h_ = h;
	}

	/**
	 * @param src_color the base color
	 * @param rgb_diff_factor 0.0f - 1.0f random offset
	 * @param a_diff_factor 0.0f - 1.0f random offset since alpha is usually max
	 */
	static glm::vec4 RandomColor(const glm::vec4 &src_color, float rgb_diff_factor, float a_diff_factor) {
		glm::vec4 color;
		color.r = src_color.r + randlib::RandFloat(-rgb_diff_factor / 2.0f, rgb_diff_factor / 2.0f);
		color.g = src_color.g + randlib::RandFloat(-rgb_diff_factor / 2.0f, rgb_diff_factor / 2.0f);
		color.b = src_color.b + randlib::RandFloat(-rgb_diff_factor / 2.0f, rgb_diff_factor / 2.0f);
		color.a = src_color.a + randlib::RandFloat(-a_diff_factor / 2.0f, a_diff_factor / 2.0f);

		glm::clamp(color.r, 0.0f, 1.0f);
		glm::clamp(color.g, 0.0f, 1.0f);
		glm::clamp(color.b, 0.0f, 1.0f);
		glm::clamp(color.a, 0.0f, 1.0f);
		return color;
	}

   protected:
	glm::vec2 pos_;  // bottom left of "rect"
	glm::vec2 vel_;
	float timer_;
	float lifespan_;
	float w_, h_;

	glm::vec4 color_;
};
}  // namespace libgl

#endif  // _LIBGL2D_PHYSICS_PARTICLE_PARTICLE_H_