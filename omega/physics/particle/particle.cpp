#include "particle.hpp"

namespace omega::physics::particle {

void Particle::update(float dt) {
    life_remaining -= dt;
    pos += vel * dt;
}

} // namespace omega::physics::particle
