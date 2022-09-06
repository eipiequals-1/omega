#include "omega/util/random.h"

#include <stdlib.h>
#include <time.h>

namespace omega::util {
int rand_int(int min, int max) {
    return rand() % (max - min) + min;
}

float rand_float(float min, float max) {
    return min + ((float)rand()) / ((float)RAND_MAX / (max - min));
}

void seed_time() {
    srand(time(nullptr));
}

} // namespace omega::util
