#ifndef OMEGA_PHYSICS_PARTICLE_PARTICLE_HPP
#define OMEGA_PHYSICS_PARTICLE_PARTICLE_HPP

#include "omega/util/math.hpp"
#include "omega/util/random.hpp"
#include "omega/util/types.hpp"

namespace omega::physics::particle {

/**
 * Represents the particle's position, velocity, radius, color, and life
 * to be used by ParticleEmitter
 */
struct Particle {
    Particle() = default;
    virtual ~Particle() = default;

    /**
     * Handles updating Particle Emitter independent data such as position, life
     * @param dt the timestep
     */
    virtual void update(f32 dt);

    bool is_dead() const {
        return life_remaining <= 0.0f;
    }

    /**
     * @param src_color the base color
     * @param rgb_diff_factor 0.0f-1.0f random offset
     * @param a_diff_factor 0.0f-1.0f random offset since alpha is usually max
     * @return a random color similar to the src_color
     */
    static glm::vec4 random_color(const glm::vec4 &src_color,
                                  f32 rgb_diff_factor,
                                  f32 a_diff_factor) {
        glm::vec4 color;
        color.r = src_color.r +
            util::random<f32>(-rgb_diff_factor / 2.0f, rgb_diff_factor / 2.0f);
        color.g = src_color.g +
            util::random<f32>(-rgb_diff_factor / 2.0f, rgb_diff_factor / 2.0f);
        color.b = src_color.b +
            util::random<f32>(-rgb_diff_factor / 2.0f, rgb_diff_factor / 2.0f);
        color.a = src_color.a +
            util::random<f32>(-a_diff_factor / 2.0f, a_diff_factor / 2.0f);

        glm::clamp(color.r, 0.0f, 1.0f);
        glm::clamp(color.g, 0.0f, 1.0f);
        glm::clamp(color.b, 0.0f, 1.0f);
        glm::clamp(color.a, 0.0f, 1.0f);
        return color;
    }

    glm::vec2 pos{0.0f}; // bottom left of "rect"
    glm::vec2 vel{10.0f};
    f32 life_remaining = 0.0f;
    f32 radius = 0.0f;

    glm::vec4 color{1.0f};
};
} // namespace omega::physics::particle

#endif // OMEGA_PHYSICS_PARTICLE_PARTICLE_HPP
