#include "world.hpp"

namespace omega::physics {

World::World(const math::vec2 &gravity) : world({gravity.x, gravity.y}) {}

World::~World() {}

void World::step(f32 timestep,
                 u32 velocity_iteration,
                 u32 position_iterations) {
    world.Step(timestep, velocity_iteration, position_iterations);
}

uptr<BoxBody> World::add_box(const math::rectf &rect,
                             BodyType type,
                             b2FixtureDef fixture_def,
                             f32 gravity_scale,
                             f32 angle) {
    uptr<BoxBody> body = util::create_uptr<BoxBody>(
        rect, type, fixture_def, gravity_scale, angle, &world);
    return std::move(body);
}

uptr<CircleBody> World::add_circle(const math::vec2 &center,
                                   f32 radius,
                                   BodyType type,
                                   b2FixtureDef fixture_def,
                                   f32 gravity_scale) {
    uptr<CircleBody> body = util::create_uptr<CircleBody>(
        center, radius, type, fixture_def, gravity_scale, &world);
    return std::move(body);
}
} // namespace omega::physics
