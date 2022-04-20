#ifndef _LIBGL2D_PHYSICS_PARTICLE_PARTICLEEMITTER_H_
#define _LIBGL2D_PHYSICS_PARTICLE_PARTICLEEMITTER_H_

#include <string>
#include <vector>

#include "libGL2D/core/using.h"
#include "libGL2D/gfx/index_buffer.h"
#include "libGL2D/gfx/shader.h"
#include "libGL2D/gfx/sprite_batch.h"
#include "libGL2D/gfx/texture/texture.h"
#include "libGL2D/gfx/vertex_array.h"
#include "libGL2D/gfx/vertex_buffer.h"
#include "libGL2D/gfx/vertex_buffer_layout.h"
#include "libGL2D/physics/particle/particle.h"
#include "libGL2D/physics/random.h"

namespace libgl {

using range = std::pair<float, float>;

struct EmitterBuilder {
	float lifespan;
	float particle_lifespan;
	glm::vec4 begin_color;   // color that particles are to be at the beginning
	glm::vec4 end_color;     // color that particles are to be at the end
	uint32_t max_particles;  // max particles at a given instance
	float emit_freq;         // time to emit particles
	glm::vec2 pos;           // pos in world coordinates
	range width;             // width
	range height;            // height
	range rot_range;         // range in degrees where particles spawn
	range speed;             // scalar range of different speeds
	glm::vec2 accel;         // acceleration
	glm::rect emit_rect;     // random point in rect to spawn particle

	// ShaderProgramSource shader_source;  // special shader to draw particles
};

class ParticleEmitter {
   public:
	explicit ParticleEmitter(EmitterBuilder& builder);
	virtual ~ParticleEmitter();

	bool is_dead() const {
		return timer_ > data_.lifespan;
	}
	void Reset(bool del_particles = false) {
		timer_ = 0.0f;
		emit_timer_ = 0.0f;
		if (del_particles) {
			num_particles_ = 0;
		}
	}
	void set_pos(const glm::vec2& pos) {
		data_.pos = pos;
	}

	void Update(float dt);
	void Render(SpriteBatch& batch);

	EmitterBuilder& get_builder() {
		return data_;
	}

   protected:
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

	void Emit();

	Particle* particles_;
	uint32_t num_particles_;

	// std::vector<libgl::Uptr<Particle>> particles_;
	EmitterBuilder data_;
	float timer_;
	float emit_timer_;

	Uptr<Texture> circle_texture_;
};

}  // namespace libgl

#endif  // _LIBGL2D_PHYSICS_PARTICLE_PARTICLEEMITTER_H_