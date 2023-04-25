#pragma once
#include <iostream>

struct Vector2 {

public:
	float X;
	float Y;

	Vector2(float x = 0, float y = 0) {
		Vector2::X = x;
		Vector2::Y = y;
	}

public:
	float GetMagnitude() {
		return sqrtf(powf(X, 2) + powf(Y, 2));
	}
	static float GetMagnitude(Vector2 Vector) {
		return sqrtf(powf(Vector.X, 2) + powf(Vector.Y, 2));
	}

	float GetNonSqrtMagnitude() {
		return powf(X, 2) + powf(Y, 2);
	}
	static float GetNonSqrtMagnitude(Vector2 Vector) {
		return powf(Vector.X, 2) + powf(Vector.Y, 2);
	}

	void NormilizeSelf() {
		float locLength = GetMagnitude();
		float inv_length = (1 / locLength);

		X *= inv_length;
		Y *= inv_length;
	}
	static Vector2 GetNormalize(Vector2 vector) {
		Vector2 newVector;
		float locLength = Vector2::GetMagnitude(newVector);
		float inv_length = (1 / locLength);

		newVector.X *= inv_length;
		newVector.Y *= inv_length;

		return newVector;
	}

	static Vector2 LinearInteprolation(Vector2 A, Vector2 B, float T) {
		Vector2 newVector;

		newVector.X = (A.X * (1.0f - T)) + (B.X * T);
		newVector.Y = (A.Y * (1.0f - T)) + (B.Y * T);

		return newVector;
	}

	float DotProduct(Vector2 B) {
		return (X * B.X) + (Y * B.Y);
	}
	static float DotProduct(Vector2 A, Vector2 B) {
		return (A.X * B.X) + (A.Y * B.Y);
	}

	float GetAngle(Vector2 B) {
		return cos(DotProduct(B) / (GetMagnitude() * GetMagnitude(B)));
	}
	static float GetAngle(Vector2 A, Vector2 B) {
		return cos(DotProduct(A, B) / (GetMagnitude(A) * GetMagnitude(B)));
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

struct Vector3 : public Vector2 {
public:
	float Z;

	Vector3(float x = 0, float y = 0, float z = 0) {
		Vector3::X = x;
		Vector3::Y = y;
		Vector3::Z = z;
	}

public:
	float GetMagnitude() {
		return sqrtf(powf(X, 2) + powf(Y, 2) + powf(Z, 2));
	}
	static float GetMagnitude(Vector3 Vector) {
		return sqrtf(powf(Vector.X, 2) + powf(Vector.Y, 2) + powf(Vector.Z, 2));
	}

	float GetNonSqrtMagnitude() {
		return powf(X, 2) + powf(Y, 2) + powf(Z, 2);
	}
	static float GetNonSqrtMagnitude(Vector3 Vector) {
		return powf(Vector.X, 2) + powf(Vector.Y, 2) + powf(Vector.Z, 2);
	}

	void NormilizeSelf() {
		float locLength = GetMagnitude();
		float inv_length = (1 / locLength);

		X *= inv_length;
		Y *= inv_length;
		Z *= inv_length;
	}
	static Vector3 GetNormalize(Vector3 vector) {
		Vector3 newVector;
		float locLength = Vector3::GetMagnitude(newVector);
		float inv_length = (1 / locLength);

		newVector.X *= inv_length;
		newVector.Y *= inv_length;
		newVector.Z *= inv_length;

		return newVector;
	}

	static Vector3 LinearInteprolation(Vector3 A, Vector3 B, float T) {
		Vector3 newVector;

		newVector.X = (A.X * (1.0f - T)) + (B.X * T);
		newVector.Y = (A.Y * (1.0f - T)) + (B.Y * T);
		newVector.Z = (A.Z * (1.0f - T)) + (B.Z * T);

		return newVector;
	}

	float DotProduct(Vector3 B) {
		return (X * B.X) + (Y * B.Y) + (Z * B.Z);
	}
	static float DotProduct(Vector3 A, Vector3 B) {
		return (A.X * B.X) + (A.Y * B.Y) + (A.Z * B.Z);
	}

	Vector3 CrossProduct(Vector3 B) {
		//TODO
		return Vector3(
			(Y * B.Z - Z * B.Y),
			(Z * B.X - X * B.Z),
			(X * B.Y - Y * B.X));
	}
	static Vector3 CrossProduct(Vector3 A, Vector3 B) {
		//TODO
		return Vector3(
			(A.Y * B.Z - A.Z * B.Y),
			(A.Z * B.X - A.X * B.Z),
			(A.X * B.Y - A.Y * B.X));
	}

	float GetAngle(Vector3 B) {
		return cos(DotProduct(B) / (GetMagnitude() * GetMagnitude(B)));
	}
	static float GetAngle(Vector3 A, Vector3 B) {
		return cos(DotProduct(A, B) / (GetMagnitude(A) * GetMagnitude(B)));
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

struct Vector4 : public Vector3 {

public:
	float W;

	Vector4(float x = 0, float y = 0, float z = 0, float w = 1) {
		Vector4::X = x;
		Vector4::Y = y;
		Vector4::Z = z;
		Vector4::W = w;
	}

public:
	float GetMagnitude() {
		return sqrtf(powf(X, 2) + powf(Y, 2) + powf(Z, 2) + powf(Z,2));
	}
	static float GetMagnitude(Vector3 Vector) {
		return sqrtf(powf(Vector.X, 2) + powf(Vector.Y, 2) + powf(Vector.Z, 2));
	}

	float GetNonSqrtMagnitude() {
		return powf(X, 2) + powf(Y, 2) + powf(Z, 2);
	}
	static float GetNonSqrtMagnitude(Vector3 Vector) {
		return powf(Vector.X, 2) + powf(Vector.Y, 2) + powf(Vector.Z, 2);
	}

	void NormilizeSelf() {
		float locLength = GetMagnitude();
		float inv_length = (1 / locLength);

		X *= inv_length;
		Y *= inv_length;
		Z *= inv_length;
	}
	static Vector3 GetNormalize(Vector3 vector) {
		Vector3 newVector;
		float locLength = Vector3::GetMagnitude(newVector);
		float inv_length = (1 / locLength);

		newVector.X *= inv_length;
		newVector.Y *= inv_length;
		newVector.Z *= inv_length;

		return newVector;
	}

	static Vector4 LinearInteprolation(Vector4 A, Vector4 B, float T) {
		Vector4 newVector;

		newVector.X = (A.X * (1.0f - T)) + (B.X * T);
		newVector.Y = (A.Y * (1.0f - T)) + (B.Y * T);
		newVector.Z = (A.Z * (1.0f - T)) + (B.Z * T);
		newVector.W = (A.W * (1.0f - T)) + (B.W * T);

		return newVector;
	}

	float DotProduct(Vector4 B) {
		return (X * B.X) + (Y * B.Y) + (Z + B.Z) + (W + B.W);
	}
	static float DotProduct(Vector4 A, Vector4 B) {
		return (A.X * B.X) + (A.Y * B.Y) + (A.Z + B.Z) + (A.W + B.W);
	}

	float GetAngle(Vector4 B) {
		return cos(DotProduct(B) / (GetMagnitude() * GetMagnitude(B)));
	}
	static float GetAngle(Vector4 A, Vector4 B) {
		return cos(DotProduct(A, B) / (GetMagnitude(A) * GetMagnitude(B)));
	}

	static float GetAverage(std::vector<Vector4> vectorOfPoints) {

	}
	static float GetAverage(std::vector<Vector4>& vectorOfPoints) {

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