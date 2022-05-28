#include "math.h"

namespace glm {
rect::rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {
}

rect::rect() : x(0.0f), y(0.0f), w(0.0f), h(0.0f) {
}

bool circleVsCircle(const glm::vec2 &center1, float radius1, const glm::vec2 &center2, float radius2) {
	auto square = [](float v) -> float { return v * v; };
	float dist_sq = square(center1.x - center2.x) + square(center1.y - center2.y);
	return dist_sq < square(radius1 + radius2);
}

float distanceSq(const glm::vec2 &p1, const glm::vec2 &p2) {
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

}  // namespace glm