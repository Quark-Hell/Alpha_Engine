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

	static inline bool ApproximatelyEqual(float a, float b, float epsilon);
	static inline void RemoveError(Vector3& vector);
	static inline void RemoveError(float& num);

private:

};

