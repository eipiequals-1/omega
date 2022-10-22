#ifndef OMEGA_UTIL_STD_H
#define OMEGA_UTIL_STD_H

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
 * @param del the delimeter to split the string with
 * @return vector<string> of the split string
 */
inline std::vector<std::string> split(std::string str, const std::string &del) {
    std::vector<std::string> ret_vec;
    char *s = &str[0]; // get pointer to string
    // start splitting string
    char *piece = strtok(s, del.c_str());
    while (piece != nullptr) {
        ret_vec.push_back(std::string(piece));
        // get next string token
        piece = strtok(nullptr, del.c_str());
    }
    return ret_vec;
}

} // namespace omega::util

#endif // OMEGA_UTIL_STD_H