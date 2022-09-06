#ifndef OMEGA_UTIL_RANDOM_H
#define OMEGA_UTIL_RANDOM_H
#include <vector>

namespace omega::util {

/**
 * @param min inclusive min value
 * @param max exclusive max value
 * @return randint int in [min, max)
 */
int rand_int(int min, int max);

/**
 * @param min inclusive min value
 * @param max exclusive max value
 */
float rand_float(float min, float max);

/**
 * Seeds the random function with the time
 * for truly random numbers
 */
void seed_time();

/**
 * Chooses a random element from the given list
 * @param arr a pointer to the beginning of the array
 * @param length the number of elements to choose randomly from -> typically the
 * length of the array
 * @return reference to the random element
 */
template <typename T>
T &rand_choice(T *arr, size_t length) {
    return arr[rand_int(0, length)];
}

/**
 * Chooses a random element from the given vector
 * @param vec the vector
 * @return reference to the random element
 */
template <typename T>
T &rand_choice(const std::vector<T> &vec) {
    return vec[rand_int(0, vec.size())];
}
} // namespace omega::util

#endif // OMEGA_UTIL_RANDOM_H