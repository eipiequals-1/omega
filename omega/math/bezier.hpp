#ifndef OMEGA_MATH_BEZIER_HPP
#define OMEGA_MATH_BEZIER_HPP

#include "omega/util/types.hpp"

namespace glm {

template <typename T>
T lerp(const T &min, const T &max, f32 t) {
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
T map_range(const T &min1,
            const T &max1,
            const T &min2,
            const T &max2,
            const T &p) {
    T t = (p - min1) / (max1 - min1);
    return min2 + (max2 - min2) * t;
}

template <typename T>
T quadratic_bezier(const T &p0, const T &p1, const T &p2, f32 t) {
    f32 ot = 1.0f - t;
    return p1 + ot * ot * (p0 - p1) + t * t * (p2 - p1);
}

template <typename T>
T cubic_bezier(const T &p0, const T &p1, const T &p2, const T &p3, f32 t) {
    f32 ot = 1.0f - t;
    return (ot * ot * ot * p0 + 3.0f * ot * ot * t * p1 +
            3.0f * ot * t * t * p2 + t * t * t * p3);
}

template <typename T>
T quartic_bezier(const T &p0,
                 const T &p1,
                 const T &p2,
                 const T &p3,
                 const T &p4,
                 f32 t) {
    f32 ot = 1.0f - t;
    return (ot * ot * ot * ot * p0 + 4.0f * ot * ot * ot * t * p1 +
            6.0f * ot * ot * t * t * p2 + 4.0f * ot * t * t * t * p3 +
            t * t * t * t * p4);
}
} // namespace glm

#endif // OMEGA_MATH_BEZIER_HPP
