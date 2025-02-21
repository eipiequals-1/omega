#ifndef OMEGA_PHYSICS_WORLD_HPP
#define OMEGA_PHYSICS_WORLD_HPP

#include <box2d/box2d.h>

#include "omega/math/math.hpp"
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
    World(const math::vec2 &gravity);
    virtual ~World();

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
    uptr<BoxBody> add_box(const math::rectf &rect,
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
    uptr<CircleBody> add_circle(const math::vec2 &center,
                                f32 radius,
                                BodyType type,
                                b2FixtureDef fixture_def,
                                f32 gravity_scale);

  private:
    b2World world;
};

} // namespace omega::physics

#endif // OMEGA_PHYSICS_WORLD_HPP
