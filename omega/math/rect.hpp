#ifndef OMEGA_MATH_RECT_HPP
#define OMEGA_MATH_RECT_HPP

#include "omega/math/glm.hpp"
#include "omega/util/types.hpp"

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
        return std::string("rect(") + std::to_string(x) + ", " +
               std::to_string(y) + ", " + std::to_string(w) + ", " +
               std::to_string(h) + ")";
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

using rectf = rect<f32>;
using recti = rect<i32>;
using rectl = rect<i64>;
using rectd = rect<f64>;

} // namespace glm

#endif // OMEGA_MATH_RECT_HPP
