#ifndef OMEGA_UTIL_STD_HPP
#define OMEGA_UTIL_STD_HPP

#include <string.h>

#include <array>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace omega::util {

// a STL unique pointer
template <typename T>
using uptr = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr uptr<T> create_uptr(Args &&...args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

// a STL shared pointer
template <typename T>
using sptr = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr sptr<T> create_sptr(Args &&...args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

/**
 * Splits the string into a vector of substrings using the delimeter
 * @param str the string to split
 * @param ret_vec out vector<string> of the split string
 * @param del the delimeter to split the string with
 */
inline void split(std::string str,
                  std::vector<std::string> &ret_vec,
                  const std::string &del = " ") {
    char *s = &str[0]; // get pointer to string
    // start splitting string
    char *piece = strtok(s, del.c_str());
    while (piece != nullptr) {
        ret_vec.push_back(std::string(piece));
        piece = strtok(nullptr, del.c_str());
    }
}

template <typename T>
void swap_ref(T &a, T &b) {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

// https://stackoverflow.com/questions/26351587/how-to-create-stdarray-with-initialization-list-without-providing-size-directl
template <typename T, typename... Args>
constexpr auto make_array(Args &&...args) -> std::array<T, sizeof...(args)> {
    return {std::forward<Args>(args)...};
}

} // namespace omega::util

#endif // OMEGA_UTIL_STD_HPP
