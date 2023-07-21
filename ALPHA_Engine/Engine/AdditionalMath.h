#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <gtx/string_cast.hpp>

class Vector3;

class Math
{
public:
	Math();
	~Math();

	static bool ApproximatelyEqual(float a, float b, float epsilon);
	static void RemoveError(Vector3& vector);
	static void RemoveError(float& num);

private:

};

