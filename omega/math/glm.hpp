#ifndef OMEGA_MATH_GLM_HPP
#define OMEGA_MATH_GLM_HPP

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

#include <optional>
#include <functional>

#include "omega/util/types.hpp"

// some more util functions
namespace glm {

template <typename T>
T factorial(const T& a) {
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


} // namespace glm


#endif // OMEGA_MATH_GLM_HPP
