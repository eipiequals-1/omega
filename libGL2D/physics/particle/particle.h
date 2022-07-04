#ifndef LIBGL2D_PHYSICS_PARTICLE_PARTICLE_H
#define LIBGL2D_PHYSICS_PARTICLE_PARTICLE_H

#include "libGL2D/core/using.h"
#include "libGL2D/physics/math.h"
#include "libGL2D/physics/random.h"

namespace libgl {

/**
 * Represents the particle's position, velocity, radius, color, and life
 * to be used by libgl::ParticleEmitter
 */
struct Particle {
	Particle();
	virtual ~Particle();

	/**
	 * Handles updating Particle Emitter independent data such as position and life
	 * @param dt the timestep
	 */
	virtual void Update(float dt);
	bool IsDead() const {
		return life_remaining <= 0.0f;
	}

	/**
	 * @param src_color the base color
	 * @param rgb_diff_factor 0.0f - 1.0f random offset
	 * @param a_diff_factor 0.0f - 1.0f random offset since alpha is usually max
	 * @return a random color similar to the src_color and off by the given factors
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
	float radius;

	glm::vec4 color;
};
}  // namespace libgl

#endif  // LIBGL2D_PHYSICS_PARTICLE_PARTICLE_H