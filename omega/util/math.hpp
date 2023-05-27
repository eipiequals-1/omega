#ifndef OMEGA_UTIL_MATH_HPP
#define OMEGA_UTIL_MATH_HPP

// enable glm hash
#define GLM_ENABLE_EXPERIMENTAL

#ifndef EMSCRIPTEN
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/norm.hpp>

#else

#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"
#include "lib/glm/gtc/type_ptr.hpp"
#include "lib/glm/gtx/hash.hpp"
#include "lib/glm/gtx/string_cast.hpp"
#include "lib/glm/gtx/norm.hpp"

#endif

#include <iostream>
#include <optional>
#include <tuple>
#include <functional>

namespace omega::util {
/**
 * Abstraction of Direction for game logic
 */
enum class Direction {
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3,
    FORWARDS = 4,
    BACKWARDS = 5
};

inline glm::vec3 intbound(glm::vec3 s, glm::vec3 ds) {
    glm::vec3 res;
    for (size_t i = 0; i < 3; i++) {
        res[i] =
            (ds[i] > 0 ?
             (glm::ceil(s[i]) - s[i])
             : (s[i] - glm::floor(s[i])))
            / glm::abs(ds[i]);
    }
    return res;
}

// Direct copy of 
// https://github.com/jdah/minecraft-again/blob/master/src/util/ray.hpp
struct Ray {
    glm::vec3 origin{0.0f};
    glm::vec3 direction{0.0f};

    Ray(const glm::vec3& origin,
        const glm::vec3 &direction) : origin(origin),
                                      direction(direction) {}

    std::optional<std::tuple<glm::ivec3, glm::vec3>>
        intersect_block(std::function<bool(glm::ivec3)> f,
                        float max_distance) {

        glm::ivec3 d{0};
        glm::ivec3 p, step;
        glm::vec3 t_max, t_delta;
        float radius;

        p = glm::floor(origin);
        step = glm::sign(direction);
        t_max = util::intbound(origin, direction);
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
};

/**
 * Checks collisions between two circles and returns if there is one
 * @param center1 circle1 center
 * @param radius1 circle1 radius
 * @param center2 circle2 center
 * @param radius2 circle2 radius
 * @return if they intersect
 */
bool circle_vs_circle(const glm::vec2 &center1, float radius1,
                      const glm::vec2 &center2, float radius2);

/**
 * Returns the distance squared between two points to avoid sqrts
 * @param p1 point1
 * @param p2 point2
 * @return the distance squared
 */
float distance_sq(const glm::vec2 &p1, const glm::vec2 &p2);

float distance_sq(const glm::vec3 &p1, const glm::vec3 &p2);

template <typename T>
T lerp(const T& min, const T& max, float t) {
    return min + (max - min) * t;
}

/**
 * Maps the a value from range 1 to range 2
 * @param min1 the lower bound of the initial range
 * @param max1 the upper bound of the initial range
 * @param min2 the lower bound of the final range
 * @param max2 the upper bound of the final range
 * @param p the point mapped in the initial range
 */
template <typename T>
T map_range(const T& min1, const T& max1,
            const T& min2, const T& max2,
            const T& p) {
    T t = (p - min1) / (max1 - min1);
    return min2 + (max2 - min2) * t;
}

template <typename T>
T quadratic_bezier(const T& p0, const T& p1, const T& p2, float t) {
    float one_minus_t = 1.0f - t;
    return p1 + one_minus_t * one_minus_t * (p0 - p1) + t * t * (p2 - p1);
}

template <typename T>
T cubic_bezier(const T &p0, const T &p1, const T& p2, const T& p3, float t) {
    float one_minus_t = 1.0f - t;
    return (one_minus_t * one_minus_t * one_minus_t * p0 +
            3.0f * one_minus_t * one_minus_t * t * p1 +
            3.0f * one_minus_t * t * t * p2 +
            t * t * t * p3);
}

} // namespace omega::util

namespace glm {

/**
 * Rectangle struct storing x, y, w (width), h (height)
 */
template <typename T>
struct rect {
  public:
    T x, y, w, h;

    rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}
    rect() : x(0.0f), y(0.0f), w(0.0f), h(0.0f) {}

    /**
     * Shifts the rectangle by the given vector
     * @param a the amount to shift
     */
    void translate(const glm::vec2 &a) {
        x += a.x;
        y += a.y;
    }

    /**
     * @return the center of the rectangle
     */
    glm::vec2 center() const {
        return glm::vec2(x + w / 2.0f, y + h / 2.0f);
    }
    void set_center_x(T centerx) {
        x = centerx - w / 2.0f;
    }
    void set_center_y(T centery) {
        y = centery - h / 2.0f;
    }

    /**
     * Returns if two rectangles overlap using AABB logic
     * @param a the other rect
     * @return if they overlap
     */
    bool overlaps(const rect<T> &a) const {
        return x < a.x + a.w && x + w > a.x && y < a.y + a.h && y + h > a.y;
    }

    /**
     * Returns if a point is contained in the rectangle
     * @param p a vec2 representing the point
     * @return if the point is contained
     */
    bool point_in_rect(const vec2 &p) const {
        return x < p.x && p.x < x + w && y < p.y && p.y < y + h;
    }

    /**
     * Returns the {string} rectangle data for debugging purposes
     */
    std::string to_string() const {
        return std::string("rect(") +
               std::to_string(x) +
               ", " +
               std::to_string(y) +
               ", " +
               std::to_string(w) +
               ", " +
               std::to_string(h) +
               ")";
    }

    /**
     * @param a another rect
     * @return if the position and sizes are exactly the same
     */
    bool operator==(const rect<T> &a) const {
        return a.x == x && a.y == y && a.w == w && a.h == h;
    }

    /**
     * @param a another rect
     * @return if the rectangles are not equal
     */
    bool operator!=(const rect<T> &a) const {
        return !(a == *this);
    }

    template <typename C>
    rect<C> convert_type() const {
        return rect<C>(static_cast<C>(x),
                       static_cast<C>(y),
                       static_cast<C>(w),
                       static_cast<C>(h));
    }
};

using rectf = rect<float>;
using recti = rect<int>;
using rectl = rect<i64>;
using rectd = rect<f64>;



} // namespace glm

#endif // OMEGA_UTIL_MATH_HPP
