#include "AdditionalMath.h"
#include <cmath>

inline bool Math::ApproximatelyEqual(float a, float b, float epsilon) {
	if (abs(a - b) < epsilon) {
		return true;
	}

	return false;
}