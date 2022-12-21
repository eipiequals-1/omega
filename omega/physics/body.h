#ifndef OMEGA_PHYSICS_BODY_H
#define OMEGA_PHYSICS_BODY_H

#include <box2d/box2d.h>

#include "omega/physics/physics_defines.h"
#include "omega/util/util.h"

namespace omega::physics {

using namespace omega::util;

using Body = b2Body;

class BoxBody {
  public:
    BoxBody(const glm::rectf &rect, BodyType type, b2FixtureDef &fixture_def, float gravity_scale, float angle, b2World *world);
    virtual ~BoxBody() = default;

    const glm::vec2 &get_dimensions() const { return dimensions; }
    glm::rectf get_rect() const {
        return glm::rectf(body->GetPosition().x - dimensions.x / 2.0f, body->GetPosition().y - dimensions.y / 2.0f, dimensions.x, dimensions.y);
    }
    Body *get_body() { return body; }

  protected:
    Body *body;
    glm::vec2 dimensions;
};

class CircleBody {
  public:
    CircleBody(const glm::vec2 &center, float radius, BodyType type, b2FixtureDef &fixture_def, float gravity_scale, b2World *world);
    virtual ~CircleBody() = default;

    const glm::vec2 &get_center() const { return center; }
    float get_radius() const { return radius; }
    Body *get_body() { return body; }

  protected:
    Body *body;
    glm::vec2 center;
    float radius;
};
} // namespace omega::physics

#endif // OMEGA_PHYSICS_BODY_H