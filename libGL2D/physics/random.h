#ifndef _LIBGL2D_PHYSICS_RANDOM_H_
#define _LIBGL2D_PHYSICS_RANDOM_H_

#include <vector>

namespace libgl {
namespace randlib {

/**
 * @param min inclusive min value
 * @param max exclusive max value
 * @return randint int in [min, max)
 */
int RandInt(int min, int max);

/**
 * @param min inclusive min value
 * @param max exclusive max value
 */
float RandFloat(float min, float max);

/**
 * Seeds the random function with the time
 * for truly random numbers
 */
void SeedTime();

/**
 * Chooses a random element from the given list
 * @param arr a pointer to the beginning of the array
 * @param length the number of elements to choose randomly from -> typically the length of the array
 * @return reference to the random element
 */
template <typename T>
T &RandChoice(T *arr, size_t length) {
	return arr[RandInt(0, length)];
}

/**
 * Chooses a random element from the given vector
 * @param vec the vector
 * @return reference to the random element
 */
template <typename T>
T &RandChoice(const std::vector<T> &vec) {
	return vec[RandInt(0, vec.size())];
}
}  // namespace randlib
}  // namespace libgl

#endif  // _LIBGL2D_PHYSICS_RANDOM_H_
