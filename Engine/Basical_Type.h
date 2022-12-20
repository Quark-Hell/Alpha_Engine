#pragma once
#ifndef BasicalType_H
#define BasicalType_H

#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

struct Vector3 {

public:
	float X;
	float Y;
	float Z;

	Vector3(float x = 1, float y = 1, float z = 1) {
		Vector3::X = x;
		Vector3::Y = y;
		Vector3::Z = z;
	}

public:
	float GetMagnitude(Vector3 vector) {
		return sqrtf(powf(vector.X, 2) + powf(vector.Y, 2) + powf(vector.Z, 2));
	}

	float GetNonSqrtMagnitude(Vector3 vector) {
		return powf(vector.X, 2) + powf(vector.Y, 2) + powf(vector.Z, 2);
	}

	Vector3 Normilize(Vector3 vector) {
		float locLength = GetMagnitude(vector);
		float inv_length = (1 / locLength);

		vector.X *= inv_length;
		vector.Y *= inv_length;
		vector.Z *= inv_length;

		return vector;
	}

#pragma region Operators
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

	Vector3 operator+(const Vector3 value) const {
		return Vector3(X + value.X, Y + value.Y, Z + value.Z);
	}

	Vector3 operator+(const Vector3* value) const {
		return Vector3(X + value->X, Y + value->Y, Z + value->Z);
	}

	Vector3 operator-(const Vector3 value) const {
		return Vector3(X - value.X, Y - value.Y, Z - value.Z);
	}

	Vector3 operator-(const Vector3* value) const {
		return Vector3(X - value->X, Y - value->Y, Z - value->Z);
	}

	Vector3 operator*(const Vector3 value) const {
		return Vector3(X * value.X, Y * value.Y, Z * value.Z);
	}

	Vector3 operator*(const Vector3* value) const {
		return Vector3(X * value->X, Y * value->Y, Z * value->Z);
	}

	Vector3 operator/(const Vector3 value) const {
		return Vector3(X / value.X, Y / value.Y, Z / value.Z);
	}

	Vector3 operator/(const Vector3* value) const {
		return Vector3(X / value->X, Y / value->Y, Z / value->Z);
	}

	bool operator!=(const Vector3 value) const {
		if (X != value.X && Y != value.Y && Z != value.Z)
		{
			return true;
		}
		return false;
	}

	bool operator!=(const Vector3* value) const {
		if (X != value->X && Y != value->Y && Z != value->Z)
		{
			return true;
		}
		return false;
	}

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

	bool operator>(const Vector3 value) {
		if (GetNonSqrtMagnitude(Vector3{ X,Y,Z }) > GetNonSqrtMagnitude(value))
		{
			return true;
		}
		return false;
	}

	bool operator>(const Vector3* value) {
		if (GetNonSqrtMagnitude(Vector3{ X,Y,Z }) > GetNonSqrtMagnitude(*value))
		{
			return true;
		}
		return false;
	}

	bool operator<(const Vector3 value) {
		if (GetNonSqrtMagnitude(Vector3{ X,Y,Z }) < GetNonSqrtMagnitude(value))
		{
			return true;
		}
		return false;
	}

	bool operator<(const Vector3* value) {
		if (GetNonSqrtMagnitude(Vector3{ X,Y,Z }) < GetNonSqrtMagnitude(*value))
		{
			return true;
		}
		return false;
	}
#pragma endregion
};

#pragma region Modules

class Module
{
private:
	std::string Name;

public:
	bool Rename(std::string name);

public:
	std::string GetName();

	//TODO:
	Module() {
		Name = "";
	}
};

class Mesh : public Module {
private:
	std::vector <Vector3> Points;
private:
	std::vector <Vector3> Triangles;

public:
	bool CreateMesh(std::vector<Vector3> points, std::vector<Vector3> triangles);

public:
	void DeleteMesh();
};

class Physics : public Module {

};

#pragma endregion

class Object
{
private:
	Vector3 Position;

private:
	std::vector<Module> Modules;

public:
	Vector3 GetPosition();

public:
	void SetPosition(float X, float Y, float Z);

public:
	bool AddModule(class Module some_module);

public:
	bool DeleteModuleByName(std::string name);

public:
	bool DeleteModuleByIndex(int index);

public:
	Module* GetModuleByName(std::string name);

public:
	Module* GetModuleByIndex(int index);

public:
	int GetCountOfModules();
};


#endif
