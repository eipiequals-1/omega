#ifndef OMEGA_PHYSICS_BODY_H
#define OMEGA_PHYSICS_BODY_H

#include <Box2D/Box2D.h>

#include "omega/physics/physics.h"
#include "omega/util/util.h"

namespace omega {

using Body = b2Body;

class BoxBody {
   public:
	BoxBody(const glm::rectf &rect, BodyType type, b2FixtureDef &fixture_def, float gravity_scale, float angle, b2World *world);
	virtual ~BoxBody() = default;

	const glm::vec2 &GetDimensions() const { return dimensions_; }
	glm::rectf GetRect() const {
		return glm::rectf(body_->GetPosition().x - dimensions_.x / 2.0f, body_->GetPosition().y - dimensions_.y / 2.0f, dimensions_.x, dimensions_.y);
	}
	Body *GetBody() { return body_; }

   protected:
	Body *body_;
	glm::vec2 dimensions_;
};

class CircleBody {
   public:
	CircleBody(const glm::vec2 &center, float radius, BodyType type, b2FixtureDef &fixture_def, float gravity_scale, b2World *world);
	virtual ~CircleBody() = default;

	const glm::vec2 &GetCenter() const { return center_; }
	float GetRadius() const { return radius_; }
	Body *GetBody() { return body_; }

   protected:
	Body *body_;
	glm::vec2 center_;
	float radius_;
};
}  // namespace omega

#endif  // OMEGA_PHYSICS_BODY_H