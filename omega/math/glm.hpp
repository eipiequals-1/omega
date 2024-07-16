#ifndef OMEGA_MATH_GLM_HPP
#define OMEGA_MATH_GLM_HPP

// enable glm hash
#define GLM_ENABLE_EXPERIMENTAL

#ifndef EMSCRIPTEN
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/string_cast.hpp>

#else

#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"
#include "lib/glm/gtc/type_ptr.hpp"
#include "lib/glm/gtx/hash.hpp"
#include "lib/glm/gtx/norm.hpp"
#include "lib/glm/gtx/string_cast.hpp"

#endif

#include <functional>
#include <optional>

#include "omega/util/types.hpp"

// some more util functions
namespace glm {

template <typename T>
T factorial(const T &a) {
    T result = 1.0;
    for (i32 i = 2; i <= a; ++i) {
        result *= i;
    }
    return result;
}

/**
 * Represents a min and max value range
 */
template <typename T>
struct Range {
    T min;
    T max;
};

inline vec3 get_normal(const vec3 &p0, const vec3 &p1, const vec3 &p2) {
    auto tan1 = p1 - p0;
    auto tan2 = p2 - p0;
    return normalize(cross(tan1, tan2));
}

} // namespace glm

#endif // OMEGA_MATH_GLM_HPP
