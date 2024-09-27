#ifndef OMEGA_MATH_COLLISIONS_HPP
#define OMEGA_MATH_COLLISIONS_HPP

#include <functional>

#include "omega/math/glm.hpp"
#include "omega/util/types.hpp"

namespace glm {
/**
 * Abstraction of Direction for game logic
 */
enum class Direction : u32 {
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3,
    FORWARDS = 4,
    BACKWARDS = 5
};

inline glm::vec3 new_intbound(glm::vec3 s, glm::vec3 ds) {
    glm::vec3 res;
    for (size_t i = 0; i < 3; i++) {
        res[i] =
            (ds[i] > 0 ? (glm::ceil(s[i]) - s[i]) : (s[i] - glm::floor(s[i]))) /
            glm::abs(ds[i]);
    }
    return res;
}

// Direct copy of
// https://github.com/jdah/minecraft-again/blob/master/src/util/ray.hpp
struct Ray {
    glm::vec3 origin{0.0f};
    glm::vec3 direction{0.0f};

    Ray(const glm::vec3 &origin, const glm::vec3 &direction)
        : origin(origin), direction(direction) {}

    std::optional<std::tuple<glm::ivec3, glm::vec3>> intersect_block(
        std::function<bool(glm::ivec3)> f,
        float max_distance) {
        glm::ivec3 d{0};
        glm::ivec3 p, step;
        glm::vec3 t_max, t_delta;
        float radius;

        p = glm::floor(origin);
        step = glm::sign(direction);
        t_max = glm::new_intbound(origin, direction);
        t_delta = glm::vec3(step) / this->direction;
        radius = max_distance / glm::l2Norm(direction);

        while (true) {
            if (f(p)) {
                return std::make_optional(std::make_tuple(p, d));
            }

            if (t_max.x < t_max.y) {
                if (t_max.x < t_max.z) {
                    if (t_max.x > radius) {
                        break;
                    }

                    p.x += step.x;
                    t_max.x += t_delta.x;
                    d = glm::ivec3(-step.x, 0, 0);
                } else {
                    if (t_max.z > radius) {
                        break;
                    }

                    p.z += step.z;
                    t_max.z += t_delta.z;
                    d = glm::ivec3(0, 0, -step.z);
                }
            } else {
                if (t_max.y < t_max.z) {
                    if (t_max.y > radius) {
                        break;
                    }

                    p.y += step.y;
                    t_max.y += t_delta.y;
                    d = glm::ivec3(0, -step.y, 0);
                } else {
                    if (t_max.z > radius) {
                        break;
                    }

                    p.z += step.z;
                    t_max.z += t_delta.z;
                    d = glm::ivec3(0, 0, -step.z);
                }
            }
        }

        return std::nullopt;
    }

    vec3 march(std::function<bool(const glm::vec3 &)> sdf,
               f32 dt = 0.01f,
               f32 epsilon = 0.01f,
               i32 max_t = 10000.0f) {
        vec3 p = origin;
        vec3 dir = normalize(direction);
        f32 t = 0.0f;

        while (t < max_t) {
            if (sdf(p) < epsilon) {
                return p;
            }
            t += dt;
            p = origin + t * dir;
        }
        return {};
    }
};

/**
 * Checks collisions between two circles and returns if there is one
 * @param center1 circle1 center
 * @param radius1 circle1 radius
 * @param center2 circle2 center
 * @param radius2 circle2 radius
 * @return if they intersect
 */
bool circle_vs_circle(const glm::vec2 &center1,
                      f32 radius1,
                      const glm::vec2 &center2,
                      f32 radius2);

/**
 * Returns the distance squared between two points to avoid sqrts
 * @param p1 point1
 * @param p2 point2
 * @return the distance squared
 */
f32 distance_sq(const glm::vec2 &p1, const glm::vec2 &p2);

f32 distance_sq(const glm::vec3 &p1, const glm::vec3 &p2);

} // namespace glm

#endif // OMEGA_MATH_COLLISIONS_HPP
