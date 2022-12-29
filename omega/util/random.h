#ifndef OMEGA_UTIL_RANDOM_H
#define OMEGA_UTIL_RANDOM_H

#include <stdlib.h>
#include <vector>

namespace omega::util {

/**
 * @param min inclusive min value
 * @param max exclusive max value
 * @return random<T> number in [min, max)
 */
template <typename T>
T random(T min, T max) {
    return min + (T)((float)rand() / (float)RAND_MAX * (float)(max - min));
}

/**
 * Seeds the random function with the time
 * for truly random numbers
 */
inline void seed_time() {
    srand(time(nullptr));
}

/**
 * Chooses a random element from the given list
 * @param arr a pointer to the beginning of the array
 * @param length the number of elements to choose randomly from -> typically the
 * length of the array
 * @return reference to the random element
 */
template <typename T>
T &random_choice(T *arr, size_t length) {
    return arr[random<int>(0, length)];
}

/**
 * Chooses a random element from the given vector
 * @param vec the vector
 * @return reference to the random element
 */
template <typename T>
T &random_choice(std::vector<T> &vec) {
    return vec[random<int>(0, vec.size())];
}
} // namespace omega::util

#endif // OMEGA_UTIL_RANDOM_H