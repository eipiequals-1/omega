#include "world.hpp"

namespace omega::physics {

World::World(float gravity_x, float gravity_y) {
    world = create_uptr<b2World>(b2Vec2(gravity_x, gravity_y));
}

void World::step(float timestep,
                 uint32_t velocity_iteration,
                 uint32_t position_iterations) {
    world->Step(timestep, velocity_iteration, position_iterations);
}

uptr<BoxBody> World::add_box(const glm::rectf &rect,
                             BodyType type,
                             b2FixtureDef fixture_def,
                             float gravity_scale,
                             float angle) {
    BoxBody *body = new BoxBody(rect, type, fixture_def, gravity_scale, angle, world.get());
    return uptr<BoxBody>(body);
}

uptr<CircleBody> World::add_circle(const glm::vec2 &center,
                                   float radius,
                                   BodyType type,
                                   b2FixtureDef fixture_def,
                                   float gravity_scale) {
    CircleBody *body = new CircleBody(center, radius, type, fixture_def, gravity_scale, world.get());
    return uptr<CircleBody>(body);
}
} // namespace omega
