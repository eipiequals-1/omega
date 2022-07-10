#ifndef OMEGA_PHYSICS_PARTICLE_PARTICLEEMITTER_H
#define OMEGA_PHYSICS_PARTICLE_PARTICLEEMITTER_H

#include <string>
#include <vector>

#include "omega/core/using.h"
#include "omega/gfx/index_buffer.h"
#include "omega/gfx/shader.h"
#include "omega/gfx/sprite_batch.h"
#include "omega/gfx/texture/texture.h"
#include "omega/gfx/vertex_array.h"
#include "omega/gfx/vertex_buffer.h"
#include "omega/gfx/vertex_buffer_layout.h"
#include "omega/physics/particle/particle.h"
#include "omega/physics/random.h"

namespace omega {

/**
 * Represents a min and max value for varius Emitter properties
 */
using range = std::pair<float, float>;

/**
 * Represents a particle vertex on the CPU with:
 * position,
 * center, (of the particle for the fragment shader)
 * radius,
 * color,
 */
struct ParticleVertex {
	float pos[2];
	float center[2];
	float radius;
	float color[4];
};

/**
 * Handles setting the settings of the particle emitters
 * including lifespan, starting and ending size, emittion frequency, rotations, accelerations, randomness, etc
 */
struct EmitterBuilder {
	float lifespan;
	float particle_lifespan;
	glm::vec4 begin_color;   // color that particles are to be at the beginning
	glm::vec4 end_color;     // color that particles are to be at the end
	uint32_t max_particles;  // max particles at a given instance
	float emit_freq;         // time to emit particles
	glm::vec2 pos;           // pos in world coordinates
	range radius;            // radius
	range rot_range;         // range in degrees where particles spawn
	range speed;             // scalar range of different speeds
	glm::vec2 accel;         // acceleration
	glm::rect emit_rect;     // random point in rect to spawn particle
};

/**
 * Abstracts all particles and renders and updates them
 */
class ParticleEmitter {
   public:
	explicit ParticleEmitter(EmitterBuilder& builder);
	virtual ~ParticleEmitter();

	virtual bool IsDead() const {
		return timer_ > data_.lifespan;
	}

	/**
	 * Resets the particle data if the life is over
	 * @param del_particles if the remaining particles should be kept or all deleted
	 */
	virtual void Reset(bool del_particles = false) {
		timer_ = 0.0f;
		emit_timer_ = 0.0f;
		if (del_particles) {
			num_particles_ = 0;
		}
	}
	virtual void SetPos(const glm::vec2& pos) {
		data_.pos = pos;
	}

	/**
	 * Updates every particle's size, color, etc
	 * @param dt the timestep
	 */
	virtual void Update(float dt);

	/**
	 * Renders the particle using a specially built shader
	 * @param view_proj_matrx to convert to screen coords
	 */
	virtual void Render(const glm::mat4& view_proj_matrix);

	EmitterBuilder& GetBuilder() {
		return data_;
	}

   protected:
	/**
	 * @return the number of particles that must be emitted
	 */
	uint32_t CanEmit() {
		u_int32_t to_add = 0;
		while (emit_timer_ >= data_.emit_freq) {
			emit_timer_ -= data_.emit_freq;
			if (num_particles_ + to_add < data_.max_particles) {
				to_add++;
			}
		}
		return to_add;
	}

	/**
	 * Emit's a new particle.
	 * Called by ParticleEmitter::Update(float dt);
	 */
	void Emit();

	Particle* particles_;
	uint32_t num_particles_;

	EmitterBuilder data_;
	float timer_;
	float emit_timer_;

	Uptr<VertexArray> vao_;
	Uptr<VertexBuffer> vbo_;
	Uptr<IndexBuffer> ibo_;
	static Uptr<Shader> shader_;
};

}  // namespace omega

#endif  // OMEGA_PHYSICS_PARTICLE_PARTICLEEMITTER_H