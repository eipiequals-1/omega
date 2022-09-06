#ifndef OMEGA_PHYSICS_WORLD_H
#define OMEGA_PHYSICS_WORLD_H

#include <Box2D/Box2D.h>

#include "omega/physics/body.h"
#include "omega/physics/physics_defines.h"
#include "omega/util/util.h"

namespace omega::physics {

using namespace omega::util;

class World {
  public:
    World(f32 gravity_x = 0.0f, f32 gravity_y = -9.81f);
    virtual ~World() = default;

    void step(f32 timestep = 1.0f / 60.0f, u32 velocity_iteration = 8, u32 position_iterations = 3);

    uptr<BoxBody> add_box(const glm::rectf &rect, BodyType type, b2FixtureDef fixture_def, f32 gravity_scale, f32 angle);
    uptr<CircleBody> add_circle(const glm::vec2 &center, f32 radius, BodyType type, b2FixtureDef fixture_def, f32 gravity_scale);

  private:
    uptr<b2World> world;
};

} // namespace omega::physics

#endif // OMEGA_PHYSICS_WORLD_H