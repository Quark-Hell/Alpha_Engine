#pragma once
//#include <iostream>
//#include "AdditionalMath.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtx/transform.hpp"
#include "gtx/string_cast.hpp"


class Math;

namespace Core {

class Vector2 {

public:
	float X;
	float Y;

	Vector2(float x = 0, float y = 0) {
		Vector2::X = x;
		Vector2::Y = y;
	}

public:
	virtual float GetMagnitude() {
		return sqrtf(powf(X, 2) + powf(Y, 2));
	}
	static float GetMagnitude(Vector2 Vector) {
		return sqrtf(powf(Vector.X, 2) + powf(Vector.Y, 2));
	}

	virtual float GetNonSqrtMagnitude() {
		return powf(X, 2) + powf(Y, 2);
	}
	static float GetNonSqrtMagnitude(Vector2 Vector) {
		return powf(Vector.X, 2) + powf(Vector.Y, 2);
	}

	virtual void NormilizeSelf() {
		float locLength = GetMagnitude();
		if (locLength == 0)
			return;

		float inv_length = (1 / locLength);

		X *= inv_length;
		Y *= inv_length;
	}
	static Vector2 GetNormalize(Vector2 vector) {
		float locLength = Vector2::GetMagnitude(vector);
		if (locLength == 0)
			return vector;

		float inv_length = (1 / locLength);

		vector.X *= inv_length;
		vector.Y *= inv_length;

		return vector;
	}

	static Vector2 LinearInteprolation(Vector2 A, Vector2 B, float T) {
		Vector2 newVector;

		newVector.X = (A.X * (1.0f - T)) + (B.X * T);
		newVector.Y = (A.Y * (1.0f - T)) + (B.Y * T);

		return newVector;
	}

	virtual float DotProduct(Vector2 B) {
		return (X * B.X) + (Y * B.Y);
	}
	static float DotProduct(Vector2 A, Vector2 B) {
		return (A.X * B.X) + (A.Y * B.Y);
	}

	virtual float GetAngle(Vector2 B = { 1,0 }) {
		return cosf(DotProduct(B) / (GetMagnitude() * GetMagnitude(B)));
	}
	static float GetAngle(Vector2 A = { 1,0 }, Vector2 B = { 1,0 }) {
		return cosf(DotProduct(A, B) / (GetMagnitude(A) * GetMagnitude(B)));
	}

	static Vector2 ReflectVector(Vector2 vector, Vector2 normal) {
		normal.NormilizeSelf();
		return normal * Vector2::DotProduct(vector, normal) * 2 - vector;
	}

#pragma region Operators
	//-----------------------------------------------------------//
	void operator=(const Vector2 value) {
		X = value.X;
		Y = value.Y;
	}
	void operator=(const Vector2* value) {
		X = value->X;
		Y = value->Y;
	}

	void operator=(const float value) {
		X = value;
		Y = value;
	}
	void operator=(const float* value) {
		X = *value;
		Y = *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator+=(const Vector2 value) {
		X += value.X;
		Y += value.Y;
	}
	void operator+=(const Vector2* value) {
		X += value->X;
		Y += value->Y;
	}

	void operator+=(const float value) {
		X += value;
		Y += value;
	}
	void operator+=(const float* value) {
		X += *value;
		Y += *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator-=(const Vector2 value) {
		X -= value.X;
		Y -= value.Y;
	}
	void operator-=(const Vector2* value) {
		X -= value->X;
		Y -= value->Y;
	}

	void operator-=(const float value) {
		X -= value;
		Y -= value;
	}
	void operator-=(const float* value) {
		X -= *value;
		Y -= *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator*=(const Vector2 value) {
		X *= value.X;
		Y *= value.Y;
	}
	void operator*=(const Vector2* value) {
		X *= value->X;
		Y *= value->Y;
	}

	void operator*=(const float value) {
		X *= value;
		Y *= value;
	}
	void operator*=(const float* value) {
		X *= *value;
		Y *= *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator/=(const Vector2 value) {
		X /= value.X;
		Y /= value.Y;
	}
	void operator/=(const Vector2* value) {
		X /= value->X;
		Y /= value->Y;
	}

	void operator/=(const float value) {
		X /= value;
		Y /= value;
	}
	void operator/=(const float* value) {
		X /= *value;
		Y /= *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	Vector2 operator+(const Vector2 value) const {
		return Vector2(X + value.X, Y + value.Y);
	}
	Vector2 operator+(const Vector2* value) const {
		return Vector2(X + value->X, Y + value->Y);
	}

	Vector2 operator+(const float value) const {
		return Vector2(X + value, Y + value);
	}
	Vector2 operator+(const float* value) const {
		return Vector2(X + *value, Y + *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	Vector2 operator-(const Vector2 value) const {
		return Vector2(X - value.X, Y - value.Y);
	}
	Vector2 operator-(const Vector2* value) const {
		return Vector2(X - value->X, Y - value->Y);
	}

	Vector2 operator-() const {
		return Vector2(-X, -Y);
	}

	Vector2 operator-(const float value) const {
		return Vector2(X - value, Y - value);
	}
	Vector2 operator-(const float* value) const {
		return Vector2(X - *value, Y - *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	Vector2 operator*(const Vector2 value) const {
		return Vector2(X * value.X, Y * value.Y);
	}
	Vector2 operator*(const Vector2* value) const {
		return Vector2(X * value->X, Y * value->Y);
	}

	Vector2 operator*(const float value) const {
		return Vector2(X * value, Y * value);
	}
	Vector2 operator*(const float* value) const {
		return Vector2(X * *value, Y * *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	Vector2 operator/(const Vector2 value) const {
		return Vector2(X / value.X, Y / value.Y);
	}
	Vector2 operator/(const Vector2* value) const {
		return Vector2(X / value->X, Y / value->Y);
	}

	Vector2 operator/(const float value) const {
		return Vector2(X / value, Y / value);
	}
	Vector2 operator/(const float* value) const {
		return Vector2(X / *value, Y / *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	bool operator!=(const Vector2 value) const {
		if (X != value.X || Y != value.Y)
		{
			return true;
		}
		return false;
	}
	bool operator!=(const Vector2* value) const {
		if (X != value->X || Y != value->Y)
		{
			return true;
		}
		return false;
	}

	bool operator!=(const float value) const {
		if (X != value || Y != value)
		{
			return true;
		}
		return false;
	}
	bool operator!=(const float* value) const {
		if (X != *value || Y != *value)
		{
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	bool operator==(const Vector2 value) const {
		if (X == value.X && Y == value.Y)
		{
			return true;
		}
		return false;
	}
	bool operator==(const Vector2* value) const {
		if (X == value->X && Y == value->Y)
		{
			return true;
		}
		return false;
	}

	bool operator==(const float value) const {
		if (X == value && Y == value)
		{
			return true;
		}
		return false;
	}
	bool operator==(const float* value) const {
		if (X == *value && Y == *value)
		{
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------//	

	//-----------------------------------------------------------//
	bool operator>(const Vector2 value) {
		if (GetNonSqrtMagnitude() > GetNonSqrtMagnitude(value))
		{
			return true;
		}
		return false;
	}
	bool operator>(const Vector2* value) {
		if (GetNonSqrtMagnitude() > GetNonSqrtMagnitude(*value))
		{
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------//

	bool operator<(const Vector2 value) {
		if (GetNonSqrtMagnitude() < GetNonSqrtMagnitude())
		{
			return true;
		}
		return false;
	}
	bool operator<(const Vector2* value) {
		if (GetNonSqrtMagnitude() < GetNonSqrtMagnitude())
		{
			return true;
		}
		return false;
	}
#pragma endregion
};

class Vector3 : public Vector2 {
public:
	float Z;

	Vector3(float x = 0, float y = 0, float z = 0) {
		Vector3::X = x;
		Vector3::Y = y;
		Vector3::Z = z;
	}

	virtual ~Vector3() = default;

public:
	virtual inline float GetMagnitude() override {
		return sqrtf(powf(X, 2) + powf(Y, 2) + powf(Z, 2));
	}
	static inline float GetMagnitude(Vector3 Vector) {
		return sqrtf(powf(Vector.X, 2) + powf(Vector.Y, 2) + powf(Vector.Z, 2));
	}

	virtual inline float GetNonSqrtMagnitude() override {
		return powf(X, 2) + powf(Y, 2) + powf(Z, 2);
	}
	static inline float GetNonSqrtMagnitude(Vector3 Vector) {
		return powf(Vector.X, 2) + powf(Vector.Y, 2) + powf(Vector.Z, 2);
	}

	virtual inline void NormilizeSelf() override {
		float locLength = GetMagnitude();
		if (locLength == 0)
			return;

		float inv_length = (1 / locLength);

		X *= inv_length;
		Y *= inv_length;
		Z *= inv_length;
	}
	static inline Vector3 GetNormalize(Vector3 vector) {
		float locLength = Vector3::GetMagnitude(vector);
		if (locLength == 0)
			return vector;

		float inv_length = (1 / locLength);

		vector.X *= inv_length;
		vector.Y *= inv_length;
		vector.Z *= inv_length;

		return vector;
	}

	static inline Vector3 LinearInteprolation(Vector3 A, Vector3 B, float T) {
		Vector3 newVector;

		newVector.X = (A.X * (1.0f - T)) + (B.X * T);
		newVector.Y = (A.Y * (1.0f - T)) + (B.Y * T);
		newVector.Z = (A.Z * (1.0f - T)) + (B.Z * T);

		return newVector;
	}

	float inline DotProduct(Vector3 B) {
		return (X * B.X) + (Y * B.Y) + (Z * B.Z);
	}
	static inline float DotProduct(Vector3 A, Vector3 B) {
		return (A.X * B.X) + (A.Y * B.Y) + (A.Z * B.Z);
	}

	inline Vector3 CrossProduct(Vector3 B) {
		return Vector3(
			(Y * B.Z - Z * B.Y),
			(Z * B.X - X * B.Z),
			(X * B.Y - Y * B.X));
	}
	static inline Vector3 CrossProduct(Vector3 A, Vector3 B) {
		return Vector3(
			(A.Y * B.Z - A.Z * B.Y),
			(A.Z * B.X - A.X * B.Z),
			(A.X * B.Y - A.Y * B.X));
	}

	float inline GetAngle(Vector3 B) {
		return acosf(DotProduct(B) / (GetMagnitude() * GetMagnitude(B)));
	}
	static inline float GetAngle(Vector3 A, Vector3 B) {
		float cos = DotProduct(A, B) / (GetMagnitude(A) * GetMagnitude(B));
		if (abs(cos) > 1)
			cos = round(cos);

		return acosf(cos);
	}

	static inline Vector3 ReflectVector(Vector3 vector, Vector3 normal) {
		normal.NormilizeSelf();
		return vector - vector * Vector3::DotProduct(vector, normal) * 2;
	}

	static inline bool LineToPlaneIntersection(std::pair<Vector3, Vector3> line, 
		Vector3 pA, Vector3 pB, Vector3 pC,
		Vector3& intersectPoint) {

		line.first.NormilizeSelf();
		line.second.NormilizeSelf();

		Vector3 lineVector = line.second - line.first;

		Vector3 planeVectorA = pB - pA;
		Vector3 planeVectorB = pC - pA;

		Vector3 planeNorm = Vector3::GetNormalize(Vector3::CrossProduct(planeVectorA, planeVectorB));

		float u = Vector3::DotProduct(planeNorm, lineVector);

		//has not contact
		if (fabs(u) < 0.001f)
			return false;

		float t = ((pA.X - line.first.X) * planeNorm.X + (pA.Y - line.first.Y) * planeNorm.Y + (pA.Z - line.first.Z) * planeNorm.Z) /
			(planeNorm.X * (lineVector.X) + planeNorm.Y * (lineVector.Y) + planeNorm.Z * (lineVector.Z));

		intersectPoint = line.first + (lineVector * t);
		return true;
	}

	static inline float GetVertexToPlaneDistance(Vector3 vertex, Vector3 p1, Vector3 normal) {
		normal.NormilizeSelf();

		float numerator = std::abs(
			(vertex.X - p1.X) * normal.X +
			(vertex.Y - p1.Y) * normal.Y +
			(vertex.Z - p1.Z) * normal.Z);

		float denominator = std::sqrt(
			normal.X * normal.X +
			normal.Y * normal.Y +
			normal.Z * normal.Z);

		return numerator / denominator;
	}

	static inline Vector3 ProjectPointOnAxis(Vector3 point, Vector3 axisP1, Vector3 axisP2) {
		Vector3 axisVector = Vector3::GetNormalize(axisP2 - axisP1);
		Vector3 pointVector = point - axisP1;

		float projection = 
			axisVector.X * pointVector.X + 
			axisVector.Y * pointVector.Y + 
			axisVector.Z * pointVector.Z;

		Vector3 projectPoint{axisP1 + axisVector * projection};
		return projectPoint;
	}

	static inline bool ClosetPointBetweenAxis(std::pair<Vector3, Vector3> axis1,std::pair<Vector3, Vector3> axis2, Vector3& point) {
		Vector3 axis1Vector = Vector3::GetNormalize(axis1.second - axis1.first);
		Vector3 axis2Vector = Vector3::GetNormalize(axis2.second - axis2.first);

		float normU = Vector3::DotProduct(axis1Vector, axis2Vector);

		//parallel
		if (fabs(normU) == 1)
			return false;

		Vector3 cn = Vector3::GetNormalize(Vector3::CrossProduct(axis2Vector ,axis1Vector));
		Vector3 rejection = axis2.first - axis1.first - axis1Vector * Vector3::DotProduct(axis2.first - axis1.first, axis1Vector) - cn * Vector3::DotProduct(axis2.first - axis1.first, cn);
		Vector3 closetApproach = axis2.first - axis2Vector * Vector3::GetMagnitude(rejection) / Vector3::DotProduct(axis2Vector, Vector3::GetNormalize(rejection));

		point = closetApproach;
		return true;
	}

	static inline float DistanceBetweenAxis(std::pair<Vector3, Vector3> axis1, std::pair<Vector3, Vector3> axis2) {
		Vector3 axis1Vector = Vector3::GetNormalize(axis1.second - axis1.first);
		
		Vector3 delta = axis2.first - axis1.first;

		Vector3 cross = Vector3::CrossProduct(delta, axis1Vector);
		float distance = Vector3::GetMagnitude(cross);

		return distance;
	}

#pragma region Operators
	//-----------------------------------------------------------//
	void operator=(const Vector3 value) {
		X = value.X;
		Y = value.Y;
		Z = value.Z;
	}
	void operator=(const Vector3* value) {
		X = value->X;
		Y = value->Y;
		Z = value->Z;
	}

	void operator=(const float value) {
		X = value;
		Y = value;
		Z = value;

	}
	void operator=(const float* value) {
		X = *value;
		Y = *value;
		Z = *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator+=(const Vector3 value) {
		X += value.X;
		Y += value.Y;
		Z += value.Z;
	}
	void operator+=(const Vector3* value) {
		X += value->X;
		Y += value->Y;
		Z += value->Z;
	}

	void operator+=(const float value) {
		X += value;
		Y += value;
		Z += value;

	}
	void operator+=(const float* value) {
		X += *value;
		Y += *value;
		Z += *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator-=(const Vector3 value) {
		X -= value.X;
		Y -= value.Y;
		Z -= value.Z;
	}
	void operator-=(const Vector3* value) {
		X -= value->X;
		Y -= value->Y;
		Z -= value->Z;
	}

	void operator-=(const float value) {
		X -= value;
		Y -= value;
		Z -= value;

	}
	void operator-=(const float* value) {
		X -= *value;
		Y -= *value;
		Z -= *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator*=(const Vector3 value) {
		X *= value.X;
		Y *= value.Y;
		Z *= value.Z;
	}
	void operator*=(const Vector3* value) {
		X *= value->X;
		Y *= value->Y;
		Z *= value->Z;
	}

	void operator*=(const float value) {
		X *= value;
		Y *= value;
		Z *= value;

	}
	void operator*=(const float* value) {
		X *= *value;
		Y *= *value;
		Z *= *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator/=(const Vector3 value) {
		X /= value.X;
		Y /= value.Y;
		Z /= value.Z;
	}
	void operator/=(const Vector3* value) {
		X /= value->X;
		Y /= value->Y;
		Z /= value->Z;
	}

	void operator/=(const float value) {
		X /= value;
		Y /= value;
		Z /= value;

	}
	void operator/=(const float* value) {
		X /= *value;
		Y /= *value;
		Z /= *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	Vector3 operator+(const Vector3 value) const {
		return Vector3(X + value.X, Y + value.Y, Z + value.Z);
	}
	Vector3 operator+(const Vector3* value) const {
		return Vector3(X + value->X, Y + value->Y, Z + value->Z);
	}

	Vector3 operator+(const float value) const {
		return Vector3(X + value, Y + value, Z + value);
	}
	Vector3 operator+(const float* value) const {
		return Vector3(X + *value, Y + *value, Z + *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	Vector3 operator-(const Vector3 value) const {
		return Vector3(X - value.X, Y - value.Y, Z - value.Z);
	}
	Vector3 operator-(const Vector3* value) const {
		return Vector3(X - value->X, Y - value->Y, Z - value->Z);
	}

	Vector3 operator-() const {
		return Vector3(-X, -Y, -Z);
	}

	Vector3 operator-(const float value) const {
		return Vector3(X - value, Y - value, Z - value);
	}
	Vector3 operator-(const float* value) const {
		return Vector3(X - *value, Y - *value, Z - *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	Vector3 operator*(const Vector3 value) const {
		return Vector3(X * value.X, Y * value.Y, Z * value.Z);
	}
	Vector3 operator*(const Vector3* value) const {
		return Vector3(X * value->X, Y * value->Y, Z * value->Z);
	}

	Vector3 operator*(const float value) const {
		return Vector3(X * value, Y * value, Z * value);
	}
	Vector3 operator*(const float* value) const {
		return Vector3(X * *value, Y * *value, Z * *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	Vector3 operator/(const Vector3 value) const {
		return Vector3(X / value.X, Y / value.Y, Z / value.Z);
	}
	Vector3 operator/(const Vector3* value) const {
		return Vector3(X / value->X, Y / value->Y, Z / value->Z);
	}

	Vector3 operator/(const float value) const {
		return Vector3(X / value, Y / value, Z / value);
	}
	Vector3 operator/(const float* value) const {
		return Vector3(X / *value, Y / *value, Z / *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	bool operator!=(const Vector3 value) const {
		if (X != value.X || Y != value.Y || Z != value.Z)
		{
			return true;
		}
		return false;
	}
	bool operator!=(const Vector3* value) const {
		if (X != value->X || Y != value->Y || Z != value->Z)
		{
			return true;
		}
		return false;
	}

	bool operator!=(const float value) const {
		if (X != value || Y != value || Z != value)
		{
			return true;
		}
		return false;
	}
	bool operator!=(const float* value) const {
		if (X != *value || Y != *value || Z != *value)
		{
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	bool operator==(const Vector3 value) const {
		if (X == value.X && Y == value.Y && Z == value.Z)
		{
			return true;
		}
		return false;
	}
	bool operator==(const Vector3* value) const {
		if (X == value->X && Y == value->Y && Z == value->Z)
		{
			return true;
		}
		return false;
	}

	bool operator==(const float value) const {
		if (X == value && Y == value && Z == value)
		{
			return true;
		}
		return false;
	}
	bool operator==(const float* value) const {
		if (X == *value && Y == *value && Z == *value)
		{
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------//	

	//-----------------------------------------------------------//
	bool operator>(const Vector3 value) {
		if (GetNonSqrtMagnitude() > GetNonSqrtMagnitude(value))
		{
			return true;
		}
		return false;
	}
	bool operator>(const Vector3* value) {
		if (GetNonSqrtMagnitude() > GetNonSqrtMagnitude(*value))
		{
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------//

	bool operator<(const Vector3 value) {
		if (GetNonSqrtMagnitude() < GetNonSqrtMagnitude(value))
		{
			return true;
		}
		return false;
	}
	bool operator<(const Vector3* value) {
		if (GetNonSqrtMagnitude() < GetNonSqrtMagnitude(*value))
		{
			return true;
		}
		return false;
	}
#pragma endregion
};

class Vector4 : public Vector3 {

public:
	float W;

	Vector4(float x = 0, float y = 0, float z = 0, float w = 1) {
		Vector4::X = x;
		Vector4::Y = y;
		Vector4::Z = z;
		Vector4::W = w;
	}
	virtual ~Vector4() = default;

public:
	virtual inline float GetMagnitude() override {
		return sqrtf(powf(X, 2) + powf(Y, 2) + powf(Z, 2) + powf(Z,2));
	}
	static inline float GetMagnitude(Vector3 Vector) {
		return sqrtf(powf(Vector.X, 2) + powf(Vector.Y, 2) + powf(Vector.Z, 2));
	}

	virtual inline float GetNonSqrtMagnitude() override {
		return powf(X, 2) + powf(Y, 2) + powf(Z, 2);
	}
	static inline float GetNonSqrtMagnitude(Vector3 Vector) {
		return powf(Vector.X, 2) + powf(Vector.Y, 2) + powf(Vector.Z, 2);
	}

	virtual inline void NormilizeSelf() override {
		float locLength = GetMagnitude();
		if (locLength == 0)
			return;

		float inv_length = (1 / locLength);

		X *= inv_length;
		Y *= inv_length;
		Z *= inv_length;
	}
	static inline Vector3 GetNormalize(Vector3 vector) {
		float locLength = Vector3::GetMagnitude(vector);
		if (locLength == 0)
			return vector;

		float inv_length = (1 / locLength);

		vector.X *= inv_length;
		vector.Y *= inv_length;
		vector.Z *= inv_length;

		return vector;
	}

	static inline Vector4 LinearInteprolation(Vector4 A, Vector4 B, float T) {
		Vector4 newVector;

		newVector.X = (A.X * (1.0f - T)) + (B.X * T);
		newVector.Y = (A.Y * (1.0f - T)) + (B.Y * T);
		newVector.Z = (A.Z * (1.0f - T)) + (B.Z * T);
		newVector.W = (A.W * (1.0f - T)) + (B.W * T);

		return newVector;
	}

	float inline DotProduct(Vector4 B) {
		return (X * B.X) + (Y * B.Y) + (Z + B.Z) + (W + B.W);
	}
	static float inline DotProduct(Vector4 A, Vector4 B) {
		return (A.X * B.X) + (A.Y * B.Y) + (A.Z + B.Z) + (A.W + B.W);
	}

	float inline GetAngle(Vector4 B = { 1,0,0 }) {
		return cosf(DotProduct(B) / (GetMagnitude() * GetMagnitude(B)));
	}
	static float inline GetAngle(Vector4 A, Vector4 B = { 1,0,0 }) {
		return cosf(DotProduct(A, B) / (GetMagnitude(A) * GetMagnitude(B)));
	}

	static inline Vector4 ReflectVector(Vector4 vector, Vector4 normal) {
		normal.NormilizeSelf();
		return vector - ((vector * normal * 2) / normal.GetMagnitude()) * normal;
	}

#pragma region Operators
	//-----------------------------------------------------------//
	void operator=(const Vector4 value) {
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		W = value.W;
	}
	void operator=(const Vector4* value) {
		X = value->X;
		Y = value->Y;
		Z = value->Z;
		W = value->W;
	}

	void operator=(const float value) {
		X = value;
		Y = value;
		Z = value;
		W = value;

	}
	void operator=(const float* value) {
		X = *value;
		Y = *value;
		Z = *value;
		W = *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator+=(const Vector4 value) {
		X += value.X;
		Y += value.Y;
		Z += value.Z;
		W += value.W;
	}
	void operator+=(const Vector4* value) {
		X += value->X;
		Y += value->Y;
		Z += value->Z;
		W += value->W;
	}

	void operator+=(const float value) {
		X += value;
		Y += value;
		Z += value;
		W += value;

	}
	void operator+=(const float* value) {
		X += *value;
		Y += *value;
		Z += *value;
		W += *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator-=(const Vector4 value) {
		X -= value.X;
		Y -= value.Y;
		Z -= value.Z;
		W -= value.Z;
	}
	void operator-=(const Vector4* value) {
		X -= value->X;
		Y -= value->Y;
		Z -= value->Z;
		W -= value->W;
	}

	void operator-=(const float value) {
		X -= value;
		Y -= value;
		Z -= value;
		W -= value;

	}
	void operator-=(const float* value) {
		X -= *value;
		Y -= *value;
		Z -= *value;
		W -= *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator*=(const Vector4 value) {
		X *= value.X;
		Y *= value.Y;
		Z *= value.Z;
		W *= value.W;
	}
	void operator*=(const Vector4* value) {
		X *= value->X;
		Y *= value->Y;
		Z *= value->Z;
		W *= value->W;
	}

	void operator*=(const float value) {
		X *= value;
		Y *= value;
		Z *= value;
		W *= value;

	}
	void operator*=(const float* value) {
		X *= *value;
		Y *= *value;
		Z *= *value;
		W *= *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator/=(const Vector4 value) {
		X /= value.X;
		Y /= value.Y;
		Z /= value.Z;
		W /= value.W;
	}
	void operator/=(const Vector4* value) {
		X /= value->X;
		Y /= value->Y;
		Z /= value->Z;
		W /= value->W;
	}

	void operator/=(const float value) {
		X /= value;
		Y /= value;
		Z /= value;
		W /= value;

	}
	void operator/=(const float* value) {
		X /= *value;
		Y /= *value;
		Z /= *value;
		W /= *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	Vector4 operator+(const Vector4 value) const {
		return Vector4(X + value.X, Y + value.Y, Z + value.Z, W + value.W);
	}
	Vector4 operator+(const Vector4* value) const {
		return Vector4(X + value->X, Y + value->Y, Z + value->Z, W + value->W);
	}

	Vector4 operator+(const float value) const {
		return Vector4(X + value, Y + value, Z + value, W + value);
	}
	Vector4 operator+(const float* value) const {
		return Vector4(X + *value, Y + *value, Z + *value, W + *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	Vector4 operator-(const Vector4 value) const {
		return Vector4(X - value.X, Y - value.Y, Z - value.Z, W - value.W);
	}
	Vector4 operator-(const Vector4* value) const {
		return Vector4(X - value->X, Y - value->Y, Z - value->Z, W - value->W);
	}

	Vector4 operator-() const {
		return Vector4(-X, -Y, -Z);
	}

	Vector4 operator-(const float value) const {
		return Vector4(X - value, Y - value, Z - value, W - value);
	}
	Vector4 operator-(const float* value) const {
		return Vector4(X - *value, Y - *value, Z - *value, W - *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	Vector4 operator*(const Vector4 value) const {
		return Vector4(X * value.X, Y * value.Y, Z * value.Z, W * value.W);
	}
	Vector4 operator*(const Vector4* value) const {
		return Vector4(X * value->X, Y * value->Y, Z * value->Z, W * value->W);
	}

	Vector4 operator*(const float value) const {
		return Vector4(X * value, Y * value, Z * value, W * value);
	}
	Vector4 operator*(const float* value) const {
		return Vector4(X * *value, Y * *value, Z * *value, W * *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	Vector4 operator/(const Vector4 value) const {
		return Vector4(X / value.X, Y / value.Y, Z / value.Z, W / value.W);
	}
	Vector4 operator/(const Vector4* value) const {
		return Vector4(X / value->X, Y / value->Y, Z / value->Z, W / value->W);
	}

	Vector4 operator/(const float value) const {
		return Vector4(X / value, Y / value, Z / value, W / value);
	}
	Vector4 operator/(const float* value) const {
		return Vector4(X / *value, Y / *value, Z / *value, W / *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	bool operator!=(const Vector4 value) const {
		if (X != value.X || Y != value.Y || Z != value.Z || W != value.W)
		{
			return true;
		}
		return false;
	}
	bool operator!=(const Vector4* value) const {
		if (X != value->X || Y != value->Y || Z != value->Z || W != value->W)
		{
			return true;
		}
		return false;
	}

	bool operator!=(const float value) const {
		if (X != value || Y != value || Z != value || W != value)
		{
			return true;
		}
		return false;
	}
	bool operator!=(const float* value) const {
		if (X != *value || Y != *value || Z != *value || W != *value)
		{
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	bool operator==(const Vector4 value) const {
		if (X == value.X && Y == value.Y && Z == value.Z && W == value.W)
		{
			return true;
		}
		return false;
	}
	bool operator==(const Vector4* value) const {
		if (X == value->X && Y == value->Y && Z == value->Z && W == value->W)
		{
			return true;
		}
		return false;
	}

	bool operator==(const float value) const {
		if (X == value && Y == value && Z == value && W == value)
		{
			return true;
		}
		return false;
	}
	bool operator==(const float* value) const {
		if (X == *value && Y == *value && Z == *value && W == *value)
		{
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------//	

	//-----------------------------------------------------------//
	bool operator>(const Vector4 value) {
		if (GetNonSqrtMagnitude() > GetNonSqrtMagnitude(value))
		{
			return true;
		}
		return false;
	}
	bool operator>(const Vector4* value) {
		if (GetNonSqrtMagnitude() > GetNonSqrtMagnitude(*value))
		{
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------//

	bool operator<(const Vector4 value) {
		if (GetNonSqrtMagnitude() < GetNonSqrtMagnitude())
		{
			return true;
		}
		return false;
	}
	bool operator<(const Vector4* value) {
		if (GetNonSqrtMagnitude() < GetNonSqrtMagnitude())
		{
			return true;
		}
		return false;
	}
#pragma endregion
};

}