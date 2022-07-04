#include "particle_emitter.h"

#include <algorithm>

namespace libgl {

Uptr<Shader> ParticleEmitter::shader_;

ParticleEmitter::ParticleEmitter(EmitterBuilder &builder) : particles_(nullptr), num_particles_(0), data_(builder) {
	Reset();
	if (shader_ == nullptr) {
		const char vertex[] = R"glsl(
			#version 450

			layout(location=0) in vec2 a_Pos;
			layout(location=1) in vec2 a_Center;
			layout(location=2) in float a_Radius;
			layout(location=3) in vec4 a_Color;

			layout(location=0) out vec2 v_Pos;
			layout(location=1) out vec2 v_Center;
			layout(location=2) out float v_Radius;
			layout(location=3) out vec4 v_Color;

			uniform mat4 u_ViewProjMatrix;

			void main() {
				gl_Position = u_ViewProjMatrix * vec4(a_Pos, 0.0, 1.0);
				v_Pos = a_Pos;
				v_Radius = a_Radius;
				v_Center = a_Center;
				v_Color = a_Color;
			}
		)glsl";
		const char fragment[] = R"glsl(
			#version 450

			layout(location=0) in vec2 v_Pos;
			layout(location=1) in vec2 v_Center;
			layout(location=2) in float v_Radius;
			layout(location=3) in vec4 v_Color;

			out vec4 color;

			void main() {
				color = vec4(0.0);
				float dist = distance(v_Pos, v_Center);
				if (dist <= v_Radius) {
					color = v_Color;
					color.a *= 1.0 - (dist / v_Radius);
				}
			}
		)glsl";
		shader_ = CreateUptr<Shader>(std::string(vertex), std::string(fragment));
	}

	vbo_ = CreateUptr<VertexBuffer>(sizeof(ParticleVertex) * 4 * data_.max_particles);
	const uint32_t kIndexBufferCapacity = 6 * data_.max_particles;
	uint32_t *indices = new uint32_t[kIndexBufferCapacity];
	uint32_t offset = 0;
	for (size_t i = 0; i < kIndexBufferCapacity; i += 6) {
		// triangle 1
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;
		// triangle 2
		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;
		offset += 4;
	}
	ibo_ = CreateUptr<IndexBuffer>(indices, kIndexBufferCapacity);
	delete[] indices;
	indices = nullptr;
	vao_ = CreateUptr<VertexArray>();
	VertexBufferLayout layout;
	layout.Push(GL_FLOAT, 2);
	layout.Push(GL_FLOAT, 2);
	layout.Push(GL_FLOAT, 1);
	layout.Push(GL_FLOAT, 4);
	vao_->AddBuffer(*vbo_, layout);
	particles_ = new Particle[data_.max_particles];
	Emit();
}

ParticleEmitter::~ParticleEmitter() {
	delete[] particles_;
	particles_ = nullptr;
}

void ParticleEmitter::Emit() {
	Particle &particle = particles_[num_particles_];
	particle.color = Particle::RandomColor(data_.begin_color, 0.2f, 0.1f);

	particle.pos.x = data_.pos.x + randlib::RandFloat(data_.emit_rect.x, data_.emit_rect.x + data_.emit_rect.w);
	particle.pos.y = data_.pos.y + randlib::RandFloat(data_.emit_rect.y, data_.emit_rect.y + data_.emit_rect.h);

	particle.radius = randlib::RandFloat(data_.radius.first, data_.radius.second);

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

		if (p.IsDead()) {
			// bring last active particle to this spot
			Particle &last_particle = particles_[num_particles_ - 1];
			p = last_particle;  // copy last particles data to old particle
			num_particles_--;
			idx--;
		}
	}
}

void ParticleEmitter::Render(const glm::mat4 &view_proj_matrix) {
	for (size_t i = 0; i < num_particles_; i++) {
		Particle &p = particles_[i];
		const glm::vec2 &pos = p.pos;
		const glm::vec4 &color = p.color;
		glm::vec2 center(pos.x + p.radius, pos.y + p.radius);
		ParticleVertex quad[4];
		quad[0] = {
		    {pos.x, pos.y},
		    {center.x, center.y},
		    p.radius,
		    {color.r, color.g, color.b, color.a}};
		quad[1] = {
		    {pos.x + p.radius * 2.0f, pos.y},
		    {center.x, center.y},
		    p.radius,
		    {color.r, color.g, color.b, color.a}};
		quad[2] = {
		    {pos.x + p.radius * 2.0f, pos.y + p.radius * 2.0f},
		    {center.x, center.y},
		    p.radius,
		    {color.r, color.g, color.b, color.a}};
		quad[3] = {
		    {pos.x, pos.y + p.radius * 2.0f},
		    {center.x, center.y},
		    p.radius,
		    {color.r, color.g, color.b, color.a}};
		vbo_->SubData(i * sizeof(ParticleVertex) * 4, sizeof(ParticleVertex) * 4, quad);
	}
	shader_->Bind();
	shader_->SetUniformMat4f("u_ViewProjMatrix", view_proj_matrix);
	vao_->Bind();
	ibo_->Bind();
	glDrawElements(GL_TRIANGLES, 6 * num_particles_, GL_UNSIGNED_INT, nullptr);
	ibo_->Unbind();
	vao_->Unbind();
	shader_->Unbind();
}

}  // namespace libgl