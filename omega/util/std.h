#ifndef OMEGA_UTIL_STD_H
#define OMEGA_UTIL_STD_H

#include <array>
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

} // namespace omega::util

#endif // OMEGA_UTIL_STD_H