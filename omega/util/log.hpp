#ifndef OMEGA_UTIL_LOG_HPP
#define OMEGA_UTIL_LOG_HPP

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
static inline void print_(
    const std::string &color,
    const std::string &level,
    const char* file,
    int line,
    Args &&...args) {
    std::cout << color << "[" << level << "]" << "\033[0m";
    std::cout << "[" << file << ":" << line << "]: ";
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
static inline void error_(const char *file, int line, Args &&...args) {
    print_(log_color::red, "ERROR", file, line, args...);
}

/**
 * Output any messages in white
 * @param args any logs to print
 */
template <typename... Args>
static inline void log_(const char *file, int line, Args &&...args) {
    print_(log_color::green, "LOG", file, line, args...);
}

/**
 * Output any debugging values in yellow
 * @param args any debug values to print
 */
template <typename... Args>
static inline void debug_(const char *file, int line, Args &&...args) {
    print_(log_color::yellow, "DEBUG", file, line, args...);
}

#define error(...) error_(__FILE__, __LINE__, __VA_ARGS__)
#define print(...) log_(__FILE__, __LINE__, __VA_ARGS__)
#define debug(...) debug_(__FILE__, __LINE__, __VA_ARGS__)

} // namespace omega::util

#endif // OMEGA_UTIL_LOG_HPP
