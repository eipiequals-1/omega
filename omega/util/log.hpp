#ifndef OMEGA_UTIL_LOG_HPP
#define OMEGA_UTIL_LOG_HPP

#include <iostream>
#include <sstream>

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

static inline void format(std::stringstream &stream, const std::string &str) {
    stream << str;
}

template <typename T, typename... Args>
static inline void format(std::stringstream &stream,
                          const std::string &str,
                          T t,
                          Args &&...args) {
    size_t first_bracket = str.find("{}", 0);
    if (first_bracket != std::string::npos) {
        stream << str.substr(0, first_bracket);
        stream << t;
        format(stream, str.substr(first_bracket + 2), args...);
        return;
    }
    stream << str;
}

template <typename... Args>
static inline void print_(
        const std::string &color,
        const std::string &level,
        const char* file,
        int line,
        const std::string &str,
        Args &&...args) {
    std::stringstream stream;
#ifndef EMSCRIPTEN
    stream << color << "[" << level << "]" << "\033[0m";
#else
    (void)color;
    stream << "[" << level << "]";
#endif
    stream << "[" << file << ":" << line << "]: ";

    format(stream, str, args...);

    std::cout << stream.str() << '\n';
}

#define error(...) print_(log_color::red, "ERROR", __FILE__, __LINE__,  __VA_ARGS__)
#define print(...) print_(log_color::green, "LOG", __FILE__, __LINE__,  __VA_ARGS__)
#define debug(...) print_(log_color::yellow, "DEBUG", __FILE__, __LINE__, __VA_ARGS__)

} // namespace omega::util

#endif // OMEGA_UTIL_LOG_HPP
