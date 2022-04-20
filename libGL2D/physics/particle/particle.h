#ifndef _LIBGL2D_PHYSICS_PARTICLE_PARTICLE_H_
#define _LIBGL2D_PHYSICS_PARTICLE_PARTICLE_H_

#include "libGL2D/core/using.h"
#include "libGL2D/physics/math.h"
#include "libGL2D/physics/random.h"

namespace libgl {

struct Particle {
	Particle();
	virtual ~Particle();

	void Update(float dt);
	bool is_dead() const {
		return life_remaining <= 0.0f;
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

	glm::vec2 pos;  // bottom left of "rect"
	glm::vec2 vel;
	float life_remaining;
	float w, h;

	glm::vec4 color;
};
}  // namespace libgl

#endif  // _LIBGL2D_PHYSICS_PARTICLE_PARTICLE_H_