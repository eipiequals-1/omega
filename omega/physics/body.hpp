#ifndef OMEGA_PHYSICS_BODY_HPP
#define OMEGA_PHYSICS_BODY_HPP

#include <box2d/box2d.h>

#include "omega/math/math.hpp"
#include "omega/physics/physics_defines.hpp"
#include "omega/util/types.hpp"

namespace omega::physics {

using Body = b2Body;

/**
 * Abstraction of a Box2D box
 */
class BoxBody {
  public:
    BoxBody(const math::rectf &rect,
            BodyType type,
            b2FixtureDef &fixture_def,
            f32 gravity_scale,
            f32 angle,
            b2World *world);

    virtual ~BoxBody() = default;

    const math::vec2 &get_dimensions() const {
        return dimensions;
    }
    /**
     * @returns the rectangle containing the box
     */
    math::rectf get_rect() const {
        return math::rectf(body->GetPosition().x - dimensions.x / 2.0f,
                           body->GetPosition().y - dimensions.y / 2.0f,
                           dimensions.x,
                           dimensions.y);
    }
    Body *get_body() {
        return body;
    }

  protected:
    Body *body = nullptr;
    math::vec2 dimensions{0.0f};
};

/**
 * Abstraction of a Box2D circle
 */
class CircleBody {
  public:
    CircleBody(const math::vec2 &center,
               f32 radius,
               BodyType type,
               b2FixtureDef &fixture_def,
               f32 gravity_scale,
               b2World *world);

    virtual ~CircleBody() = default;

    const math::vec2 &get_center() const {
        return center;
    }
    f32 get_radius() const {
        return radius;
    }
    Body *get_body() {
        return body;
    }

  protected:
    Body *body = nullptr;
    math::vec2 center{0.0f};
    f32 radius = 0.0f;
};
} // namespace omega::physics

#endif // OMEGA_PHYSICS_BODY_HPP
