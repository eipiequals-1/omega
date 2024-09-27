#ifndef OMEGA_UTIL_MEMORY_HPP
#define OMEGA_UTIL_MEMORY_HPP

#include <cstdlib>
#include <cstring>

#include "omega/core/error.hpp"
#include "omega/util/log.hpp"
#include "omega/util/types.hpp"

namespace omega::util {

inline u64 kilobytes(u64 x) {
    return x * 1024;
}

inline u64 megabytes(u64 x) {
    return x * 1024 * 1024;
}

class BumpAllocator {
  public:
    BumpAllocator(u64 bytes) {
        mem = (u8 *)malloc(bytes);
        size = bytes;
        clear();
    }
    ~BumpAllocator() {
        if (mem != nullptr) {
            free(mem);
        }
    }

    u8 *allocate(u64 s) {
        u64 aligned_size = (s + 7) & ~7;
        if (used + aligned_size <= size) {
            used += aligned_size;
            return mem + used;
        }
        omega::core::assert(
            false, "Bump Allocator of size {} bytes ran out of memory");
        return nullptr;
    }

    template <typename T>
    T *allocate(u64 count) {
        return allocate(count * sizeof(T));
    }

    void clear() {
        used = 0;
        memset(mem, 0, size);
    }

  private:
    u8 *mem = nullptr;
    u64 used = 0;
    u64 size = 0;
};

}; // namespace omega::util

#endif // OMEGA_UTIL_MEMORY_HPP
