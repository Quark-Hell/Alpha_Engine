#pragma once
#include <cmath>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <gtx/string_cast.hpp>

#include "Vectors.h"

class Math
{
public:
	Math();
	~Math();

	static bool ApproximatelyEqual(float a, float b, float epsilon);
	static void RemoveError(Vector3& vector);
	static void RemoveError(float& num);

	static float Clamp(float min, float max, float value);

private:

};

