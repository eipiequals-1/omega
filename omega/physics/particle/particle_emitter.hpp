#ifndef OMEGA_PHYSICS_PARTICLE_PARTICLEEMITTER_HPP
#define OMEGA_PHYSICS_PARTICLE_PARTICLEEMITTER_HPP

#include <string>
#include <vector>

#include "omega/gfx/index_buffer.hpp"
#include "omega/gfx/shader.hpp"
#include "omega/gfx/sprite_batch.hpp"
#include "omega/gfx/texture/texture.hpp"
#include "omega/gfx/vertex_array.hpp"
#include "omega/gfx/vertex_buffer.hpp"
#include "omega/gfx/vertex_buffer_layout.hpp"
#include "omega/physics/particle/particle.hpp"
#include "omega/util/math.hpp"
#include "omega/util/std.hpp"

namespace omega::physics::particle {

using namespace omega::gfx;
using namespace omega::util;

/**
 * Represents a min and max value for varius Emitter properties
 */
using range = std::pair<float, float>;

/**
 * Handles setting the settings of the particle emitters
 * including lifespan, starting and ending size, emittion frequency,
 * rotations, accelerations, randomness, etc
 */
struct EmitterBuilder {
    float lifespan;
    float particle_lifespan;
    glm::vec4 begin_color;  // color that particles are to be at the beginning
    glm::vec4 end_color;    // color that particles are to be at the end
    uint32_t max_particles; // max particles at a given instance
    float emit_freq;        // time to emit particles
    glm::vec2 pos;          // pos in world coordinates
    range radius;           // radius
    range rot_range;        // range in degrees where particles spawn
    range speed;            // scalar range of different speeds
    glm::vec2 accel;        // acceleration
    glm::rectf emit_rect;   // random point in rect to spawn particle
};

/**
 * Abstracts all particles and renders and updates them
 */
class ParticleEmitter {
  public:
    explicit ParticleEmitter(EmitterBuilder &builder);
    virtual ~ParticleEmitter();

    virtual bool is_dead() const {
        return timer > data.lifespan;
    }

    /**
     * Resets the particle data if the life is over
     * @param del_particles if the remaining particles should be kept or deleted
     */
    virtual void reset(bool del_particles = false) {
        timer = 0.0f;
        emit_timer = 0.0f;
        if (del_particles) {
            num_particles = 0;
        }
    }
    virtual void set_pos(const glm::vec2 &pos) {
        data.pos = pos;
    }

    /**
     * Updates every particle's size, color, etc
     * @param dt the timestep
     */
    virtual void update(float dt);

    /**
     * Renders the particle using a specially built shader
     * @param view_proj_matrx to convert to screen coords
     */
    virtual void render(const glm::mat4 &view_proj_matrix);

    EmitterBuilder &get_builder() {
        return data;
    }

  protected:
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
     * @return the number of particles that must be emitted
     */
    uint32_t can_emit() {
        u_int32_t to_add = 0;
        while (emit_timer >= data.emit_freq) {
            emit_timer -= data.emit_freq;
            if (num_particles + to_add < data.max_particles) {
                to_add++;
            }
        }
        return to_add;
    }

    /**
     * Emit's a new particle.
     * Called by ParticleEmitter::update(float dt);
     */
    void emit();

    // particle data
    Particle *particles;
    uint32_t num_particles;

    // emission data
    EmitterBuilder data;
    float timer;
    float emit_timer;

    // gl objections
    uptr<VertexArray> vao;
    uptr<VertexBuffer> vbo;
    uptr<IndexBuffer> ibo;
    static uptr<Shader> shader;
};

} // namespace omega::physics::particle

#endif // OMEGA_PHYSICS_PARTICLE_PARTICLEEMITTER_HPP
