#ifndef OMEGA_PHYSICS_PHYSICSDEFINES_HPP
#define OMEGA_PHYSICS_PHYSICSDEFINES_HPP

#include <box2d/box2d.h>

namespace omega::physics {

/**
 * Represents the different Box2D shapes
 */
enum class ShapeType {
    circle = b2Shape::e_circle,
    edge = b2Shape::e_edge,
    polygon = b2Shape::e_polygon,
    chain = b2Shape::e_chain,
    typeCount = b2Shape::e_typeCount
};

/**
 * Represents the different Box2D movement types
 */
enum class BodyType {
    static_body = b2_staticBody,
    kinematic_body = b2_kinematicBody,
    dynamic_body = b2_dynamicBody
};

} // namespace omega::physics

#endif // OMEGA_PHYSICS_PHYSICSDEFINES_HPP
