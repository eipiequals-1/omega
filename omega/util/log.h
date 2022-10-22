#ifndef OMEGA_UTIL_LOG_H
#define OMEGA_UTIL_LOG_H

#include <iostream>

namespace omega::util {

namespace log_color {

const std::string black = "\033[30m";
const std::string red = "\033[31m";
const std::string green = "\033[32m";
const std::string yellow = "\033[33m";
const std::string blue = "\033[34m";
const std::string magenta = "\033[35m";
const std::string cyan = "\033[36m";
const std::string white = "\033[37m";

} // namespace log_color

template <typename F, typename First, typename... Rest>
static inline void do_for(F func, First first, Rest &&...rest) {
    func(first);
    do_for(func, rest...);
}
template <typename F>
static inline void do_for(F f) {
    (void)f;
}
template <typename... Args>
static inline void print(const std::string &color, const std::string &level, Args &&...args) {
    std::cout << color << "[" << level << "]: "
              << "\033[0m";
    do_for([&](auto arg) {
        std::cout << arg << ' ';
    },
           args...);
    std::cout << '\n';
}

/**
 * Output any errors in red
 * @param args any errors to print
 */
template <typename... Args>
inline void error(Args &&...args) {
    print(log_color::red, "ERROR", args...);
}

/**
 * Output any messages in white
 * @param args any logs to print
 */
template <typename... Args>
inline void log(Args &&...args) {
    print(log_color::green, "LOG", args...);
}

} // namespace omega::util

#endif // OMEGA_UTIL_LOG_H