#include "particle.hpp"

namespace omega::physics::particle {

void Particle::update(f32 dt) {
    life_remaining -= dt;
    pos += vel * dt;
}

} // namespace omega::physics::particle
