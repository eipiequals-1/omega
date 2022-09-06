#include "particle.h"

namespace omega::physics::particle {

Particle::Particle() {
    pos = glm::vec2(0.0f);
    vel = glm::vec2(10.0f);
    radius = 0.0f;
    life_remaining = 0.0f;
    color = glm::vec4(1.0f);
}

Particle::~Particle() {
}

void Particle::update(f32 dt) {
    life_remaining -= dt;
    pos += vel * dt;
}

} // namespace omega::physics