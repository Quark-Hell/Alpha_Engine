#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

//Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
	std::string _name;

private:
	friend class Render;

public:
	void Rename(std::string name);
	std::string GetName();

private:
	virtual void Test();
};

class Mesh : public Module {
private:
	std::vector <Vector3> Points;
	std::vector <Vector3> Normals;
	std::vector <unsigned int> Indices;
	//std::vector <Vector3> VertexColors;
	//std::vector <Vector3> TextureCoords;

private:
	friend class Render;

public:
	Mesh();
	~Mesh();

	bool CreateMesh(std::string linkToFBX);
	void DeleteMesh();
};

class Physics : public Module {


public:
	Physics();
	~Physics();
};

#pragma endregion

class Object {

private:
	Vector3 Position{ 0,0,0 };
	Vector3 Rotation{ 0,0,0 };
	Vector3 Scale{ 1,1,1 };
	std::vector<Module*> Modules;

public:
	Object();
	~Object();

	Vector3 GetPosition();
	void SetPosition(float X, float Y, float Z);
	void SetPosition(Vector3 Position);

	Vector3 GetRotation();
	void SetRotation(float X, float Y, float Z);
	void SetRotation(Vector3 Rotation);

	Vector3 GetScale();
	void SetScale(float X, float Y, float Z);
	void SetScale(Vector3 Scale);

	bool AddModule(class Module* some_module);

	bool DeleteModuleByName(std::string name);
	bool DeleteModuleByIndex(int index);

	Module* GetModuleByName(std::string name);
	Module* GetModuleByIndex(int index);

	int GetCountOfModules();

	void DeleteObject();
};

class World {

private:
	static inline std::vector<Object*> ObjectsOnScene;

private:
	friend class Object;
	friend class Render;

	World();
};
