#ifndef OMEGA_UTIL_MATH_H
#define OMEGA_UTIL_MATH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace omega::util {
/**
 * Abstraction of Direction for game logic
 */
enum class Direction {
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3
};
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
    virtual void translate(const glm::vec2 &a) {
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
    virtual bool overlaps(const rect<T> &a) const {
        return x < a.x + a.w && x + w > a.x && y < a.y + a.h && y + h > a.y;
    }

    /**
     * Returns if a point is contained in the rectangle
     * @param p a vec2 representing the point
     * @return if the point is contained
     */
    virtual bool point_in_rect(const vec2 &p) const {
        return x < p.x && p.x < x + w && y < p.y && p.y < y + h;
    }

    /**
     * Prints the rectangle data for debugging purposes
     */
    virtual void print() const {
        std::cout << "x=" << x << ", y=" << y << ", w=" << w << ", h=" << h << '\n';
    }

    /**
     * @param a another rect
     * @return if the position and sizes are exactly the same
     */
    virtual bool operator==(const rect<T> &a) const {
        return a.x == x && a.y == y && a.w == w && a.h == h;
    }

    /**
     * @param a another rect
     * @return if the rectangles are not equal
     */
    virtual bool operator!=(const rect<T> &a) const {
        return !(a == *this);
    }

    template <typename C>
    rect<C> convert_type() const {
        return rect<C>(static_cast<C>(x), static_cast<C>(y), static_cast<C>(w), static_cast<C>(h));
    }
};

using rectf = rect<f32>;
using recti = rect<i32>;
using rectl = rect<i64>;
using rectd = rect<f64>;

/**
 * Checks collisions between two circles and returns if there is one
 * @param center1 circle1 center
 * @param radius1 circle1 radius
 * @param center2 circle2 center
 * @param radius2 circle2 radius
 * @return if they intersect
 */
bool circleVsCircle(const glm::vec2 &center1, f32 radius1, const glm::vec2 &center2, f32 radius2);

/**
 * Returns the distance squared between two points to avoid unnecessary and slow sqrts
 * @param p1 point1
 * @param p2 point2
 * @return the distance squared
 */
f32 distanceSq(const glm::vec2 &p1, const glm::vec2 &p2);

} // namespace glm

#endif // OMEGA_UTIL_MATH_H