#include "hole.h"

Hole::Hole(float centerX, float centerY, float radius) : center(centerX, centerY), radius(radius) {
}

bool Hole::IsBallIn(const glm::vec2 &center, float radius) {
	return glm::circleVsCircle(this->center, this->radius, center, radius);
}
