#ifndef OMEGA_PHYSICS_WORLD_H
#define OMEGA_PHYSICS_WORLD_H

#include <Box2D/Box2D.h>

#include "omega/core/using.h"
#include "omega/physics/body.h"
#include "omega/physics/math.h"
#include "omega/physics/physics.h"

namespace omega {

class World {
   public:
	World(float gravity_x = 0.0f, float gravity_y = -9.81f);
	virtual ~World() = default;

	void Step(float timestep = 1.0f / 60.0f, uint32_t velocity_iteration = 8, uint32_t position_iterations = 3);

	Uptr<BoxBody> AddBox(const glm::rectf& rect, BodyType type, b2FixtureDef fixture_def, float gravity_scale, float angle);
	Uptr<CircleBody> AddCircle(const glm::vec2& center, float radius, BodyType type, b2FixtureDef fixture_def, float gravity_scale);

   private:
	Uptr<b2World> world_;
};

}  // namespace omega

#endif  // OMEGA_PHYSICS_WORLD_H