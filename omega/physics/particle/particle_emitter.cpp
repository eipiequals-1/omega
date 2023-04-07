#include "particle_emitter.hpp"

#include <algorithm>

namespace omega::physics::particle {

uptr<Shader> ParticleEmitter::shader;

ParticleEmitter::ParticleEmitter(EmitterBuilder &builder) : 
    particles(nullptr), num_particles(0), data(builder) {
    reset();
    if (shader == nullptr) {
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
        shader =
            create_uptr<Shader>(std::string(vertex), std::string(fragment));
    }

    vbo = create_uptr<VertexBuffer>(
        sizeof(ParticleVertex) * 4 * data.max_particles);
    
    const uint32_t index_buffer_capacity = 6 * data.max_particles;
    uint32_t *indices = new uint32_t[index_buffer_capacity];
    uint32_t offset = 0;
    for (size_t i = 0; i < index_buffer_capacity; i += 6) {
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
    ibo = create_uptr<IndexBuffer>(indices, index_buffer_capacity);
    delete[] indices;
    indices = nullptr;
    vao = create_uptr<VertexArray>();
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2);
    layout.push(GL_FLOAT, 2);
    layout.push(GL_FLOAT, 1);
    layout.push(GL_FLOAT, 4);
    vao->add_buffer(*vbo, layout);
    particles = new Particle[data.max_particles];
    emit();
}

ParticleEmitter::~ParticleEmitter() {
    delete[] particles;
    particles = nullptr;
}

void ParticleEmitter::emit() {
    Particle &particle = particles[num_particles];
    particle.color = Particle::random_color(data.begin_color, 0.2f, 0.1f);

    particle.pos.x = data.pos.x + util::random<float>(
        data.emit_rect.x, data.emit_rect.x + data.emit_rect.w);
    particle.pos.y = data.pos.y + util::random<float>(
        data.emit_rect.y, data.emit_rect.y + data.emit_rect.h);

    particle.radius = util::random<float>(
        data.radius.first, data.radius.second);

    particle.life_remaining = data.particle_lifespan;
    float rotation = glm::radians(
        util::random<float>(data.rot_range.first, data.rot_range.second));
    float speed = util::random<float>(
        data.speed.first, data.speed.second);

    particle.vel = glm::vec2(
        glm::cos(-rotation) * speed, glm::sin(-rotation) * speed);
    num_particles++; // increment num particles
}

void ParticleEmitter::update(float dt) {
    timer += dt;
    emit_timer += dt;
    // add new particles if necessary
    const uint32_t to_add = can_emit();
    for (uint32_t i = 0; i < glm::min(to_add, (uint32_t)3); i++) {
        emit();
    }

    for (size_t idx = 0; idx < num_particles; idx++) {
        Particle &p = particles[idx];
        p.update(dt);
        p.vel += data.accel * dt;

        // color change / time = color change / particle_lifespan
        glm::vec4 diff_color = 
            (data.end_color - data.begin_color) / data.particle_lifespan;
        p.color += diff_color * dt;

        if (p.is_dead()) {
            // bring last active particle to this spot
            Particle &last_particle = particles[num_particles - 1];
            p = last_particle; // copy last particles data to old particle
            num_particles--;
            idx--;
        }
    }
}

void ParticleEmitter::render(const glm::mat4 &view_proj_matrix) {
    for (size_t i = 0; i < num_particles; i++) {
        Particle &p = particles[i];
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
        
        vbo->sub_data(
            i * sizeof(ParticleVertex) * 4, sizeof(ParticleVertex) * 4, quad);
    }
    shader->bind();
    shader->set_uniform_mat4f("u_ViewProjMatrix", view_proj_matrix);
    vao->bind();
    ibo->bind();
    glDrawElements(GL_TRIANGLES, 6 * num_particles, GL_UNSIGNED_INT, nullptr);
    ibo->unbind();
    vao->unbind();
    shader->unbind();
}

} // namespace omega
