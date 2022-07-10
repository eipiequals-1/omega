#ifndef OMEGA_PHYSICS_PHYSICS_H
#define OMEGA_PHYSICS_PHYSICS_H

#include <Box2D/Box2D.h>

namespace omega {

enum class ShapeType {
	kCircle = b2Shape::e_circle,
	kEdge = b2Shape::e_edge,
	kPolygon = b2Shape::e_polygon,
	kChain = b2Shape::e_chain,
	kTypeCount = b2Shape::e_typeCount
};

enum class BodyType {
	kStatic = b2_staticBody,
	kKinematic = b2_kinematicBody,
	kDynamic = b2_dynamicBody
};

}  // namespace omega

#endif  // OMEGA_PHYSICS_PHYSICS_H