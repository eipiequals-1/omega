#include "random.h"

#include <stdlib.h>
#include <time.h>

namespace omega {
int RandInt(int min, int max) {
	return rand() % (max - min) + min;
}

float RandFloat(float min, float max) {
	return min + ((float)rand()) / ((float)RAND_MAX / (max - min));
}

void SeedTime() {
	srand(time(nullptr));
}

}  // namespace omega
