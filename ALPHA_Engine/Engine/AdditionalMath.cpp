#include "AdditionalMath.h"
#include <cmath>
#include <string>
#include "Vectors.h"

inline bool Math::ApproximatelyEqual(float a, float b, float epsilon) {
	if (abs(a - b) < epsilon) {
		return true;
	}

	return false;
}

inline void Math::RemoveError(Vector3& vector, float epsilon) {
	if (Math::ApproximatelyEqual(vector.X, 0, epsilon)) {
		vector.X = round(vector.X);
	}
	if (Math::ApproximatelyEqual(vector.Y, 0, epsilon)) {
		vector.Y = round(vector.Y);
	}
	if (Math::ApproximatelyEqual(vector.Z, 0, epsilon)) {
		vector.Z = round(vector.Z);
	}
}

inline void Math::RemoveError(float& num, float epsilon) {
	if (Math::ApproximatelyEqual(num, 0, epsilon)) {
		num = round(num);
	}
}

inline std::string Math::Karatsuba(std::string num1, std::string num2) {

}