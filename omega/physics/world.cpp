#include "world.h"

namespace omega {

World::World(float gravity_x, float gravity_y) : world_(nullptr) {
	world_ = create_uptr<b2World>(b2Vec2(gravity_x, gravity_y));
}

void World::Step(float timestep, uint32_t velocity_iteration, uint32_t position_iterations) {
	world_->Step(timestep, velocity_iteration, position_iterations);
}

uptr<BoxBody> World::AddBox(const glm::rectf& rect, BodyType type, b2FixtureDef fixture_def, float gravity_scale, float angle) {
	BoxBody* body = new BoxBody(rect, type, fixture_def, gravity_scale, angle, world_.get());
	return uptr<BoxBody>(body);
}

uptr<CircleBody> World::AddCircle(const glm::vec2& center, float radius, BodyType type, b2FixtureDef fixture_def, float gravity_scale) {
	CircleBody* body = new CircleBody(center, radius, type, fixture_def, gravity_scale, world_.get());
	return uptr<CircleBody>(body);
}
}  // namespace omega