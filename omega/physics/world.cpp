#include "world.h"

namespace omega {

World::World(float gravity_x, float gravity_y) : world_(nullptr) {
	world_ = CreateUptr<b2World>(b2Vec2(gravity_x, gravity_y));
}

void World::Step(float timestep, uint32_t velocity_iteration, uint32_t position_iterations) {
	world_->Step(timestep, velocity_iteration, position_iterations);
}

Uptr<BoxBody> World::AddBox(const glm::rect& rect, BodyType type, b2FixtureDef fixture_def, float gravity_scale, float angle) {
	BoxBody* body = new BoxBody(rect, type, fixture_def, gravity_scale, angle, world_.get());
	return Uptr<BoxBody>(body);
}

Uptr<CircleBody> World::AddCircle(const glm::vec2& center, float radius, BodyType type, b2FixtureDef fixture_def, float gravity_scale) {
	CircleBody* body = new CircleBody(center, radius, type, fixture_def, gravity_scale, world_.get());
	return Uptr<CircleBody>(body);
}
}  // namespace omega