#ifndef OMEGA_PHYSICS_PHYSICSDEFINES_H
#define OMEGA_PHYSICS_PHYSICSDEFINES_H

#include <Box2D/Box2D.h>

namespace omega::physics {

enum class ShapeType {
    k_circle = b2Shape::e_circle,
    k_edge = b2Shape::e_edge,
    k_polygon = b2Shape::e_polygon,
    k_chain = b2Shape::e_chain,
    k_typeCount = b2Shape::e_typeCount
};

enum class BodyType {
    k_static = b2_staticBody,
    k_kinematic = b2_kinematicBody,
    k_dynamic = b2_dynamicBody
};

} // namespace omega::physics

#endif // OMEGA_PHYSICS_PHYSICSDEFINES_H