#ifndef LIBGL2D_PHYSICS_PHYSICS_H
#define LIBGL2D_PHYSICS_PHYSICS_H

#include <Box2D/Box2D.h>

namespace libgl {

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

}  // namespace libgl

#endif  // LIBGL2D_PHYSICS_PHYSICS_H