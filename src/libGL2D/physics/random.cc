#include "random.h"

#include <stdlib.h>

namespace libGL2D {
namespace randlib {
int RandInt(int min, int max) {
	return rand() % (max - min) + min;
}

float RandFloat(float min, float max) {
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}
}  // namespace randlib
}  // namespace libGL2D