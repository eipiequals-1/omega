#include "particle.h"

namespace libgl {
Particle::Particle() {
	pos_ = glm::vec2(0.0f);
	vel_ = glm::vec2(10.0f);
	w_ = 0.0f;
	h_ = 0.0f;
	timer_ = 0.0f;
	lifespan_ = 0.0f;
	color_ = glm::vec4(1.0f);
}

Particle::~Particle() {
}

void Particle::Update(float dt) {
	timer_ += dt;
	pos_ += vel_ * dt;
}

}  // namespace libgl