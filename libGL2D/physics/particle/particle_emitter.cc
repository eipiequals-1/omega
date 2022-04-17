#include "particle_emitter.h"

#include <algorithm>

namespace libgl {

ParticleEmitter::ParticleEmitter(EmitterBuilder &builder) : data_(builder) {
	Reset();

	circle_texture_ = std::make_unique<Texture>("./res/gfx/circle.png", GL_LINEAR, GL_LINEAR);
	Emit();
}

ParticleEmitter::~ParticleEmitter() {
}

void ParticleEmitter::Emit() {
	particles_.push_back(std::make_unique<Particle>());
	Particle *particle = particles_[particles_.size() - 1].get();
	particle->set_color(Particle::RandomColor(data_.begin_color, 0.2f, 0.1f));

	float x = data_.pos.x + randlib::RandFloat(data_.emit_rect.x, data_.emit_rect.x + data_.emit_rect.w);
	float y = data_.pos.y + randlib::RandFloat(data_.emit_rect.y, data_.emit_rect.y + data_.emit_rect.h);

	particle->set_pos(glm::vec2(x, y));
	particle->set_w(data_.size.x);
	particle->set_h(data_.size.y);

	particle->set_lifespan(data_.particle_lifespan);
	float rotation = glm::radians(randlib::RandFloat(data_.rot_range.first, data_.rot_range.second));
	float speed = randlib::RandFloat(data_.speed.first, data_.speed.second);

	particle->set_vel(glm::vec2(glm::cos(-rotation) * speed, glm::sin(-rotation) * speed));
}

void ParticleEmitter::Update(float dt) {
	timer_ += dt;
	emit_timer_ += dt;
	// add new particles if necessary
	uint32_t to_add = CanEmit();
	for (uint32_t i = 0; i < glm::min(to_add, (uint32_t)3); i++) {
		Emit();
	}

	for (int idx = particles_.size() - 1; idx >= 0; idx--) {
		auto &p = particles_[idx];
		p->Update(dt);
		p->set_vel(p->get_vel() + data_.accel * dt);
		// change size / time
		glm::vec2 diff_size = data_.size / data_.particle_lifespan;
		p->set_w(p->get_w() - diff_size.x * dt);
		p->set_h(p->get_h() - diff_size.y * dt);

		// change color
		// color change / time = color change / particle_lifespan
		glm::vec4 diff_color = (data_.end_color - data_.begin_color) / data_.particle_lifespan;
		glm::vec4 new_color = p->get_color() + (diff_color * dt);
		p->set_color(new_color);

		if (p->is_dead()) {
			particles_.erase(particles_.begin() + idx);
			continue;
		}
	}
}

void ParticleEmitter::Render(SpriteBatch &batch) {
	for (int i = particles_.size() - 1; i >= 0; i--) {
		Particle &p = *particles_[i];
		const glm::vec2 &pos = p.get_pos();
		float w = p.get_w();
		float h = p.get_h();
		const glm::vec4 &color = p.get_color();

		batch.RenderTexture(circle_texture_.get(), pos.x, pos.y, w, h, color);
	}
}

}  // namespace libgl