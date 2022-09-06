#include "world.h"

namespace omega::physics {

World::World(f32 gravity_x, f32 gravity_y) : world(nullptr) {
    world = create_uptr<b2World>(b2Vec2(gravity_x, gravity_y));
}

void World::step(f32 timestep, u32 velocity_iteration, u32 position_iterations) {
    world->Step(timestep, velocity_iteration, position_iterations);
}

uptr<BoxBody> World::add_box(const glm::rectf &rect, BodyType type, b2FixtureDef fixture_def, f32 gravity_scale, f32 angle) {
    BoxBody *body = new BoxBody(rect, type, fixture_def, gravity_scale, angle, world.get());
    return uptr<BoxBody>(body);
}

uptr<CircleBody> World::add_circle(const glm::vec2 &center, f32 radius, BodyType type, b2FixtureDef fixture_def, f32 gravity_scale) {
    CircleBody *body = new CircleBody(center, radius, type, fixture_def, gravity_scale, world.get());
    return uptr<CircleBody>(body);
}
} // namespace omega