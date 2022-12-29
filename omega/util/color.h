#ifndef OMEGA_UTIL_COLOR_H
#define OMEGA_UTIL_COLOR_H

#include <glm/glm.hpp>

namespace omega::util::color {

/**
 * Converts a 32 bit representation of a color to a normalized rgba color vector
 * @param a the 32 bit color
 * @return the rgba color vector
 */
inline glm::vec4 to_vec4(glm::uint32_t a) {
    unsigned char *vals = (unsigned char *)&a;
    return glm::vec4(vals[0] / 0xff, vals[1] / 0xff, vals[2] / 0xff, vals[3] / 0xff);
}

/**
 * Converts a normalized rgba color vector to a 32 bit representation of it
 * @param a the normalized color vector
 * @return 32 bit representation of color
 */
inline glm::uint32_t to_uint32_t(const glm::vec4 &a) {
    glm::uint32_t b;
    glm::u8 *ptr = (glm::u8 *)&b;
    ptr[0] = (glm::u8)(a.r * 0xff);
    ptr[1] = (glm::u8)(a.g * 0xff);
    ptr[2] = (glm::u8)(a.b * 0xff);
    ptr[3] = (glm::u8)(a.a * 0xff);
    return b;
}

/**
 * Color constants for easier use
 */
const glm::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);
const glm::vec4 black(0.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 red(1.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 green(0.0f, 1.0f, 0.0f, 1.0f);
const glm::vec4 blue(0.0f, 0.0f, 1.0f, 1.0f);
const glm::vec4 yellow(1.0f, 1.0f, 0.0f, 1.0f);

} // namespace omega::util::color

#endif // OMEGA_UTIL_COLOR_H