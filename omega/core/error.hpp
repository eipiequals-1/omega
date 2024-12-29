#ifndef OMEGA_CORE_ERROR_HPP
#define OMEGA_CORE_ERROR_HPP

#include <cstdlib>

#include "omega/util/log.hpp"
#include "omega/util/std.hpp"

namespace omega::core {

inline void assert_(bool c, const std::string &msg = "", bool critical = true) {
    if (!c) {
        OMEGA_ERROR("ASSERTION FAILED: {}", msg);
        if (critical) {
            std::exit(EXIT_FAILURE);
        }
    }
}

struct Error {
    enum Type {
        OUT_OF_MEMORY,
        OUT_OF_RANGE,
        LOGIC_ERROR,
    };

    enum Level { WARN = 0, ERROR, FATAL };
};
#define OMEGA_ASSERT(c, ...) omega::core::assert_(c, __VA_ARGS__)

} // namespace omega::core

#endif // OMEGA_CORE_ERROR_HPP
