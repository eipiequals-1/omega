#ifndef OMEGA_PHYSICS_WORLD_H
#define OMEGA_PHYSICS_WORLD_H

#include <box2d/box2d.h>

#include "omega/physics/body.h"
#include "omega/physics/physics_defines.h"
#include "omega/util/util.h"

namespace omega::physics {

using namespace omega::util;

class World {
  public:
    World(float gravity_x = 0.0f, float gravity_y = -9.81f);
    virtual ~World() = default;

    void step(float timestep = 1.0f / 60.0f, uint32_t velocity_iteration = 8, uint32_t position_iterations = 3);

    uptr<BoxBody> add_box(const glm::rectf &rect, BodyType type, b2FixtureDef fixture_def, float gravity_scale, float angle);
    uptr<CircleBody> add_circle(const glm::vec2 &center, float radius, BodyType type, b2FixtureDef fixture_def, float gravity_scale);

  private:
    uptr<b2World> world;
};

} // namespace omega::physics

#endif // OMEGA_PHYSICS_WORLD_H