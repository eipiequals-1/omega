#ifndef OMEGA_UTIL_COLOR_HPP
#define OMEGA_UTIL_COLOR_HPP

#include "omega/math/math.hpp"

namespace omega::util::color {

/**
 * Converts a 32 bit representation of a color to a float rgba color vector
 * @param a the 32 bit color
 * @return the rgba color vector
 */
inline math::vec4 to_vec4(math::u32 a) {
    unsigned char *vals = (unsigned char *)&a;
    return math::vec4(vals[0] / 0xff,
                     vals[1] / 0xff,
                     vals[2] / 0xff,
                     vals[3] / 0xff);
}

/**
 * Converts a normalized rgba color vector to a 32 bit representation of it
 * @param a the normalized color vector
 * @return 32 bit representation of color
 */
inline math::u32 to_u32(const math::vec4 &a) {
    math::u32 b;
    math::u8 *ptr = (math::u8 *)&b;
    ptr[0] = (math::u8)(a.r * 0xff);
    ptr[1] = (math::u8)(a.g * 0xff);
    ptr[2] = (math::u8)(a.b * 0xff);
    ptr[3] = (math::u8)(a.a * 0xff);
    return b;
}

inline math::vec4 to_vec4(math::u8 r, math::u8 g, math::u8 b, math::u8 a) {
    return math::vec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

/**
 * Color constants for easier use
 */
const math::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);
const math::vec4 black(0.0f, 0.0f, 0.0f, 1.0f);
const math::vec4 red(1.0f, 0.0f, 0.0f, 1.0f);
const math::vec4 green(0.0f, 1.0f, 0.0f, 1.0f);
const math::vec4 blue(0.0f, 0.0f, 1.0f, 1.0f);
const math::vec4 yellow(1.0f, 1.0f, 0.0f, 1.0f);

} // namespace omega::util::color

#endif // OMEGA_UTIL_COLOR_HPP
