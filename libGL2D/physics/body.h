#ifndef LIBGL2D_PHYSICS_BODY_H
#define LIBGL2D_PHYSICS_BODY_H

#include <Box2D/Box2D.h>

#include "libGL2D/core/using.h"
#include "libGL2D/physics/math.h"
#include "libGL2D/physics/physics.h"

namespace libgl {

using Body = b2Body;

class BoxBody {
   public:
	BoxBody(const glm::rect &rect, BodyType type, b2FixtureDef &fixture_def, float gravity_scale, float angle, b2World *world);
	virtual ~BoxBody() = default;

	const glm::vec2 &GetDimensions() const { return dimensions_; }
	glm::rect GetRect() const {
		return glm::rect(body_->GetPosition().x - dimensions_.x / 2.0f, body_->GetPosition().y - dimensions_.y / 2.0f, dimensions_.x, dimensions_.y);
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
}  // namespace libgl

#endif  // LIBGL2D_PHYSICS_BODY_H