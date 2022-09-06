#ifndef OMEGA_UTIL_LOG_H
#define OMEGA_UTIL_LOG_H

#include <iostream>

namespace omega::util {

inline void log() {
    std::cout << '\n';
}

/**
 * The official omega logging function for proper formatting and ease of use
 * @param args any arguments to print
 */
template <typename T, typename... Args>
void log(T &t, Args &&...args) {
    std::cout << t << ' ';
    log(args...);
}
} // namespace omega::util

#endif // OMEGA_UTIL_LOG_H