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
		if (locLength == 0) { return; }
		float inv_length = (1 / locLength);

		X *= inv_length;
		Y *= inv_length;
	}
	static Vector2 GetNormalize(Vector2 vector) {
		float locLength = Vector2::GetMagnitude(vector);
		if (locLength == 0) { return vector; }
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

	float DotProduct(Vector2 B) {
		return (X * B.X) + (Y * B.Y);
	}
	static float DotProduct(Vector2 A, Vector2 B) {
		return (A.X * B.X) + (A.Y * B.Y);
	}

	float GetAngle(Vector2 B = { 1,0 }) {
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
		if (locLength == 0) { return; }
		float inv_length = (1 / locLength);

		X *= inv_length;
		Y *= inv_length;
		Z *= inv_length;
	}
	static Vector3 GetNormalize(Vector3 vector) {
		float locLength = Vector3::GetMagnitude(vector);

		if (locLength == 0) { return vector; }

		float inv_length = (1 / locLength);

		vector.X *= inv_length;
		vector.Y *= inv_length;
		vector.Z *= inv_length;

		return vector;
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
		return Vector3(
			(Y * B.Z - Z * B.Y),
			(Z * B.X - X * B.Z),
			(X * B.Y - Y * B.X));
	}
	static Vector3 CrossProduct(Vector3 A, Vector3 B) {
		return Vector3(
			(A.Y * B.Z - A.Z * B.Y),
			(A.Z * B.X - A.X * B.Z),
			(A.X * B.Y - A.Y * B.X));
	}

	float GetAngle(Vector3 B) {
		return cosf(DotProduct(B) / (GetMagnitude() * GetMagnitude(B)));
	}
	static float GetAngle(Vector3 A, Vector3 B) {
		return cosf(DotProduct(A, B) / (GetMagnitude(A) * GetMagnitude(B)));
	}

	static Vector3 ReflectVector(Vector3 vector, Vector3 normal) {
		normal.NormilizeSelf();
		return vector - vector * Vector3::DotProduct(vector, normal) * 2;
	}

	static Vector3 GetContactPoint(Vector3 normal, Vector3 planeDot, Vector3 A, Vector3 B)
	{
		Vector3 nAB = Vector3::GetNormalize(B - A);

		return A + nAB * Vector3::DotProduct(normal, planeDot - A) / Vector3::DotProduct(normal, nAB);
	}
	static Vector3 GetIntersection(std::pair<Vector3, Vector3> line1, std::pair<Vector3, Vector3> line2) {
		Vector3 AB = line1.first - line1.second;
		Vector3 CD = line2.first - line2.second;
		Vector3 line = Vector3::CrossProduct(AB, CD);
		Vector3 crossLineAB = Vector3::CrossProduct(line, AB);
		Vector3 crossLineCD = Vector3::CrossProduct(line, CD);

		return (GetContactPoint(crossLineAB, line1.first, line2.first, line2.second), GetContactPoint(crossLineCD, line2.first, line1.first, line1.second));
	}

	static float GetDistanceBetweenPlanes(std::pair<Vector3, Vector3> plane1, std::pair<Vector3, Vector3> plane2) {
		float numerator = 
			abs(plane1.second.X * plane2.second.X + plane1.first.Y * plane2.second.Y + plane1.first.Z * plane2.second.Z - 
			(plane2.first.X * plane2.second.X + plane2.first.Y * plane2.second.Y + plane2.first.Z * plane2.second.Z));

		float denominator = sqrtf(powf(plane2.second.X, 2) + powf(plane2.second.Y, 2) + powf(plane2.second.Z, 2));

		return numerator / denominator;
	}

	static float TriangleIntersection(const Vector3& orig, const Vector3& dir, const Vector3& v0, const Vector3& v1, const Vector3& v2) {
		Vector3 e1 = v1 - v0;
		Vector3 e2 = v2 - v0;
		// Вычисление вектора нормали к плоскости
		Vector3 pvec = Vector3::CrossProduct (dir, e2);
		float det = Vector3::DotProduct(e1, pvec);

		// Ray is parralel
		if (det < 1e-8 && det > -1e-8) {
			return 0;
		}

		float inv_det = 1 / det;
		Vector3 tvec = orig - v0;
		float u = Vector3::DotProduct(tvec, pvec) * inv_det;
		if (u < 0 || u > 1) {
			return 0;
		}

		Vector3 qvec = Vector3::CrossProduct(tvec, e1);
		float v = Vector3::DotProduct(dir, qvec) * inv_det;
		if (v < 0 || u + v > 1) {
			return 0;
		}
		return Vector3::DotProduct(e2, qvec) * inv_det;
	}

	static float GetDotVsPlaneDistance(Vector3 dot, Vector3 a, Vector3 b, Vector3 c) {
		float A = (b.Y - a.Y) * (c.Z - a.Z) - (b.Z - a.Z) * (c.Y - a.Y);
		float B = (b.Z - a.Z) * (c.X - a.X) - (b.X - a.X) * (c.Z - a.Z);
		float C = (b.X - a.X) * (c.Y - a.Y) - (b.Y - a.Y) * (c.X - a.X);
		float D = -A * a.X - B * a.Y - C * a.Z;

		float numerator = abs(A * dot.X + B * dot.Y + C * dot.Z + D);
		float denominator = sqrt(A * A + B * B + C * C);

		return numerator / denominator;
	}

	static Vector3 project(Vector3 a, Vector3 b) {
		float dot = Vector3::DotProduct(a, b);
		float length = Vector3::GetMagnitude(b);
		Vector3 p = { b.X * dot / length, b.Y * dot / length, b.Z * dot / length };
		return p;
	}

	static Vector3 project(Vector3 p, Vector3 a, Vector3 b, Vector3 c) {
		Vector3 norm = Vector3::CrossProduct(b - a, c - a);
		Vector3 v = p - a;
		float dist = Vector3::GetMagnitude(v);
		Vector3 result = p - (norm * dist);
		return result;
	}

	static Vector3 project(Vector3 p, Vector3 a, Vector3 b, Vector3 c, Vector3 projectVector) {
		Vector3 v = p - a;
		float dist = Vector3::GetMagnitude(v);
		Vector3 result = p - (Vector3::GetNormalize(projectVector) * dist);
		return result;
	}

	static Vector3 GetMinVectorToPlane(Vector3 p, Vector3 a, Vector3 b, Vector3 c) {
		Vector3 normal = Vector3::CrossProduct(b - a,c - a);
		Vector3 toPoint = p - a;
		Vector3 projection = project(toPoint, normal);
		Vector3 minVector = toPoint - projection;
		return minVector;
	}

	static Vector3 LineVsPlaneIntersection(std::pair<Vector3, Vector3> line, Vector3 a, Vector3 b, Vector3 c) {
		Vector3 normal = Vector3::CrossProduct(b - a, c - a);

		double t = ((normal.X * (a.X - line.first.X)) + (normal.Y * (a.Y - line.first.Y)) + (normal.Z * (a.Z - line.first.Z))) / ((normal.X * (line.second.X - line.first.X)) + (normal.Y * (line.second.Y - line.first.Y)) + (normal.Z * (line.second.Z - line.first.Z)));

		Vector3 intersection_point;
		intersection_point.X = line.first.X + t * (line.second.X - line.first.X);
		intersection_point.Y = line.first.Y + t * (line.second.Y - line.first.Y);
		intersection_point.Z = line.first.Z + t * (line.second.Z - line.first.Z);

		return intersection_point;
	}

	static std::pair<Vector3, float> XZ(Vector3 dot, Vector3 a, Vector3 b, Vector3 c) {
		Vector3 normalX = { 1,0,0 };
		Vector3 normalY = { 0,1,0 };
		Vector3 normalZ = { 0,0,1 };

		Vector3 toPoint = dot - a;

		Vector3 projectionX = project(toPoint, normalX);
		Vector3 projectionY = project(toPoint, normalY);
		Vector3 projectionZ = project(toPoint, normalZ);

		Vector3 vectorX = toPoint - projectionX;
		Vector3 vectorY = toPoint - projectionY;
		Vector3 vectorZ = toPoint - projectionZ;

		Vector3 dotX = Vector3::TriangleIntersection(dot, normalX, a, b, c);
		Vector3 dotY = Vector3::TriangleIntersection(dot, normalY, a, b, c);
		Vector3 dotZ = Vector3::TriangleIntersection(dot, normalZ, a, b, c);

		float distX = Vector3::GetMagnitude(dot - projectionX);
		float distY = Vector3::GetMagnitude(dot - projectionY);
		float distZ = Vector3::GetMagnitude(dot - projectionZ);

		if (distX <= distY && distX <= distZ) {
			return std::pair<Vector3, float>(Vector3::GetNormalize(normalX), Vector3::GetMagnitude(dotX));
		}
		else if (distY <= distX && distY <= distZ) {
			return std::pair<Vector3, float>(Vector3::GetNormalize(normalY), Vector3::GetMagnitude(dotY));
		}
		else
		{
			return std::pair<Vector3, float>(Vector3::GetNormalize(normalZ), Vector3::GetMagnitude(dotZ));
		}
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
		if (locLength == 0) { return; }
		float inv_length = (1 / locLength);

		X *= inv_length;
		Y *= inv_length;
		Z *= inv_length;
	}
	static Vector4 GetNormalize(Vector4 vector) {
		float locLength = Vector4::GetMagnitude(vector);
		if (locLength == 0) { return vector; }
		float inv_length = (1 / locLength);

		vector.X *= inv_length;
		vector.Y *= inv_length;
		vector.Z *= inv_length;
		vector.W *= inv_length;

		return vector;
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

	float GetAngle(Vector4 B = { 1,0,0 }) {
		return cosf(DotProduct(B) / (GetMagnitude() * GetMagnitude(B)));
	}
	static float GetAngle(Vector4 A, Vector4 B = { 1,0,0 }) {
		return cosf(DotProduct(A, B) / (GetMagnitude(A) * GetMagnitude(B)));
	}

	static Vector4 ReflectVector(Vector4 vector, Vector4 normal) {
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