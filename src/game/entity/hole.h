#ifndef _GAME_ENTITY_HOLE_H_
#define _GAME_ENTITY_HOLE_H_

#include "libGL2D/physics/math.h"

class Hole {
   public:
	Hole(float centerX, float centerY, float radius);

	bool IsBallIn(const glm::vec2 &center, float radius);
	const glm::vec2 &GetCenter() const { return center; }
	float GetRadius() const { return radius; }

   protected:
	glm::vec2 center;
	float radius;
};

#endif  // _GAME_ENTITY_HOLE_H_