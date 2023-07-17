#include "AdditionalMath.h"
#include <cmath>
#include "Vectors.h"

bool Math::ApproximatelyEqual(float a, float b, float epsilon) {
	if (abs(a - b) < epsilon) {
		return true;
	}

	return false;
}

void Math::RemoveError(Vector3& vector) {
	if (Math::ApproximatelyEqual(vector.X, 0, 4.76837130e-06)) {
		vector.X = 0;
	}
	if (Math::ApproximatelyEqual(vector.Y, 0, 4.76837130e-06)) {
		vector.Y = 0;
	}
	if (Math::ApproximatelyEqual(vector.Z, 0, 4.76837130e-06)) {
		vector.Z = 0;
	}
}

void Math::RemoveError(float& num) {
	if (Math::ApproximatelyEqual(num, 0, 4.76837130e-06)) {
		num = 0;
	}
}