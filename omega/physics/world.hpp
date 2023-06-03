#ifndef OMEGA_PHYSICS_WORLD_HPP
#define OMEGA_PHYSICS_WORLD_HPP

#include <box2d/box2d.h>

#include "omega/physics/body.hpp"
#include "omega/physics/physics_defines.hpp"
#include "omega/util/std.hpp"
#include "omega/util/types.hpp"

namespace omega::physics {

using namespace omega::util;

/**
 * Represents a Box2D world
 */
class World {
  public:
    World(f32 gravity_x = 0.0f, f32 gravity_y = -9.81f);
    virtual ~World() = default;

    /**
     * Update the phyics model with the given params (default: suggested params)
     * @param timestep
     * @param velocity_iterations
     * @param position_iterations
     */
    void step(f32 timestep = 1.0f / 60.0f,
              u32 velocity_iteration = 8,
              u32 position_iterations = 3);

    /**
     * Add a box to the world with the following params
     * @param rect the position and size
     * @param type
     * @param fixture_def
     * @param gravity_scale
     * @param angle
     * @return BoxBody
     */
    uptr<BoxBody> add_box(const glm::rectf &rect,
                          BodyType type,
                          b2FixtureDef fixture_def,
                          f32 gravity_scale,
                          f32 angle);

    /**
     * Add a circle to the world with the following params
     * @param center
     * @param radius
     * @param type
     * @param fixture_def
     * @param gravity_scale
     * @return CircleBody
     */
    uptr<CircleBody> add_circle(const glm::vec2 &center,
                                f32 radius,
                                BodyType type,
                                b2FixtureDef fixture_def,
                                f32 gravity_scale);

  private:
    uptr<b2World> world = nullptr;
};

} // namespace omega::physics

#endif // OMEGA_PHYSICS_WORLD_HPP
