#pragma once
#include <string>

class Vector3;

class Math
{
public:
	Math();
	~Math();

	static inline bool ApproximatelyEqual(float a, float b, float epsilon);
	static inline void RemoveError(Vector3& vector, float epsilon);
	static inline void RemoveError(float& num, float epsilon);

	static inline std::string Karatsuba(std::string num1, std::string num2);

private:

};

