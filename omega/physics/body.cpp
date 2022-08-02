#include "body.h"

namespace omega {
BoxBody::BoxBody(const glm::rectf& rect, BodyType type, b2FixtureDef& fixture_def, float gravity_scale, float angle, b2World* world) : body_(nullptr), dimensions_(rect.w, rect.h) {
	b2BodyDef body_def;
	body_def.type = (b2BodyType)type;
	body_def.position.Set(rect.x + rect.w / 2.0f, rect.y + rect.h / 2.0f);
	body_def.angle = glm::radians(angle);
	body_def.gravityScale = gravity_scale;
	body_ = world->CreateBody(&body_def);

	// create shape
	b2PolygonShape box;
	box.SetAsBox(rect.w / 2.0f, rect.h / 2.0f);
	fixture_def.shape = &box;
	body_->CreateFixture(&fixture_def);
}

CircleBody::CircleBody(const glm::vec2& center, float radius, BodyType type, b2FixtureDef& fixture_def, float gravity_scale, b2World* world) : center_(center), radius_(radius) {
	b2BodyDef body_def;
	body_def.type = (b2BodyType)type;
	body_def.position.Set(center.x, center.y);
	body_def.angle = 0.0f;
	body_def.gravityScale = gravity_scale;
	body_ = world->CreateBody(&body_def);

	// create shape
	b2CircleShape circle;
	circle.m_p = body_def.position;
	circle.m_radius = radius_;
	circle.m_type = (b2Shape::Type)ShapeType::kCircle;
	fixture_def.shape = &circle;
	body_->CreateFixture(&fixture_def);
}

}  // namespace omega