#include "collisions.hpp"

namespace glm {

bool circle_vs_circle(const glm::vec2 &center1, float radius1,
                      const glm::vec2 &center2, float radius2) {
    auto square = [](float v) -> float { return v * v; };
    float dist_sq =
        square(center1.x - center2.x) + square(center1.y - center2.y);
    return dist_sq < square(radius1 + radius2);
}

float distance_sq(const glm::vec2 &p1, const glm::vec2 &p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

float distance_sq(const glm::vec3 &p1, const glm::vec3 &p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y) +
           (p1.z - p2.z) * (p1.z - p2.z);
}

} // namespace glm
