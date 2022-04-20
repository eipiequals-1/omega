#include "particle_emitter.h"

#include <algorithm>

namespace libgl {

ParticleEmitter::ParticleEmitter(EmitterBuilder &builder) : particles_(nullptr), num_particles_(0), data_(builder) {
	Reset();

	circle_texture_ = std::make_unique<Texture>("./res/gfx/circle.png", GL_LINEAR, GL_LINEAR);
	particles_ = new Particle[data_.max_particles];

	Emit();
}

ParticleEmitter::~ParticleEmitter() {
	delete[] particles_;
}

void ParticleEmitter::Emit() {
	Particle &particle = particles_[num_particles_];
	particle.color = Particle::RandomColor(data_.begin_color, 0.2f, 0.1f);

	particle.pos.x = data_.pos.x + randlib::RandFloat(data_.emit_rect.x, data_.emit_rect.x + data_.emit_rect.w);
	particle.pos.y = data_.pos.y + randlib::RandFloat(data_.emit_rect.y, data_.emit_rect.y + data_.emit_rect.h);

	particle.w = randlib::RandFloat(data_.width.first, data_.width.second);
	particle.h = randlib::RandFloat(data_.height.first, data_.height.second);

	particle.life_remaining = data_.particle_lifespan;
	float rotation = glm::radians(randlib::RandFloat(data_.rot_range.first, data_.rot_range.second));
	float speed = randlib::RandFloat(data_.speed.first, data_.speed.second);

	particle.vel = glm::vec2(glm::cos(-rotation) * speed, glm::sin(-rotation) * speed);
	num_particles_++;  // increment num particles
}

void ParticleEmitter::Update(float dt) {
	timer_ += dt;
	emit_timer_ += dt;
	// add new particles if necessary
	const uint32_t to_add = CanEmit();
	for (uint32_t i = 0; i < glm::min(to_add, (uint32_t)3); i++) {
		Emit();
	}

	for (size_t idx = 0; idx < num_particles_; idx++) {
		Particle &p = particles_[idx];
		p.Update(dt);
		p.vel += data_.accel * dt;

		// color change / time = color change / particle_lifespan
		glm::vec4 diff_color = (data_.end_color - data_.begin_color) / data_.particle_lifespan;
		p.color += diff_color * dt;

		if (p.is_dead()) {
			// bring last active particle to this spot
			Particle &last_particle = particles_[num_particles_ - 1];
			p = last_particle;  // copy last particles data to old particle
			num_particles_--;
			idx--;
		}
	}
}

void ParticleEmitter::Render(SpriteBatch &batch) {
	for (size_t i = 0; i < num_particles_; i++) {
		Particle &p = particles_[i];
		const glm::vec2 &pos = p.pos;
		float w = p.w;
		float h = p.h;
		const glm::vec4 &color = p.color;

		batch.RenderTexture(circle_texture_.get(), pos.x, pos.y, w, h, color);
	}
}

}  // namespace libgl