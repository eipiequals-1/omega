#include "body.hpp"

namespace omega::physics {

BoxBody::BoxBody(const glm::rectf &rect,
                 BodyType type,
                 b2FixtureDef &fixture_def,
                 f32 gravity_scale,
                 f32 angle,
                 b2World *world) :
    dimensions(rect.w, rect.h) {
    
    b2BodyDef body_def;
    body_def.type = (b2BodyType)type;
    body_def.position.Set(rect.x + rect.w / 2.0f, rect.y + rect.h / 2.0f);
    body_def.angle = glm::radians(angle);
    body_def.gravityScale = gravity_scale;
    body = world->CreateBody(&body_def);

    // create shape
    b2PolygonShape box;
    box.SetAsBox(rect.w / 2.0f, rect.h / 2.0f);
    fixture_def.shape = &box;
    body->CreateFixture(&fixture_def);
}

CircleBody::CircleBody(const glm::vec2 &center,
                       f32 radius,
                       BodyType type,
                       b2FixtureDef &fixture_def,
                       f32 gravity_scale,
                       b2World *world) :
    center(center), radius(radius) {
    
    b2BodyDef body_def;
    body_def.type = (b2BodyType)type;
    body_def.position.Set(center.x, center.y);
    body_def.angle = 0.0f;
    body_def.gravityScale = gravity_scale;
    body = world->CreateBody(&body_def);

    // create shape
    b2CircleShape circle;
    circle.m_p = body_def.position;
    circle.m_radius = radius;
    circle.m_type = (b2Shape::Type)ShapeType::circle;
    fixture_def.shape = &circle;
    body->CreateFixture(&fixture_def);
}

} // namespace omega
