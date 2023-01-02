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
	float GetMagnitude() {
		return sqrtf(powf(X, 2) + powf(Y, 2) + powf(Z, 2));
	}

	float GetNonSqrtMagnitude() {
		return powf(X, 2) + powf(Y, 2) + powf(Z, 2);
	}

	Vector3 Normilize() {
		float locLength = GetMagnitude();
		float inv_length = (1 / locLength);

		X *= inv_length;
		Y *= inv_length;
		Z *= inv_length;

		return { Z,Y,Z };
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

	Vector3 operator+(const float value) const {
		return Vector3(X + value, Y + value, Z + value);
	}
	Vector3 operator+(const float* value) const {
		return Vector3(X + *value, Y + *value, Z + *value);
	}

	//-----------------------------------------------------------//

	Vector3 operator-(const Vector3 value) const {
		return Vector3(X - value.X, Y - value.Y, Z - value.Z);
	}
	Vector3 operator-(const Vector3* value) const {
		return Vector3(X - value->X, Y - value->Y, Z - value->Z);
	}

	Vector3 operator-(const float value) const {
		return Vector3(X - value, Y - value, Z - value);
	}
	Vector3 operator-(const float* value) const {
		return Vector3(X - *value, Y - *value, Z - *value);
	}

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

	bool operator>(const Vector3 value) {
		if (GetNonSqrtMagnitude() > GetNonSqrtMagnitude())
		{
			return true;
		}
		return false;
	}
	bool operator>(const Vector3* value) {
		if (GetNonSqrtMagnitude() > GetNonSqrtMagnitude())
		{
			return true;
		}
		return false;
	}

	//-----------------------------------------------------------//

	bool operator<(const Vector3 value) {
		if (GetNonSqrtMagnitude() < GetNonSqrtMagnitude())
		{
			return true;
		}
		return false;
	}
	bool operator<(const Vector3* value) {
		if (GetNonSqrtMagnitude() < GetNonSqrtMagnitude())
		{
			return true;
		}
		return false;
	}
#pragma endregion
};

class Object;

class Module
{
private:
	std::string _name;
	Object* ParentObject;

private:
	friend class Render;
	friend class Object;


public:
	void Rename(std::string name);
	std::string GetName();
	Object* GetParentObject();


private:
	virtual void Test();
};

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
	Module* GetModuleByIndex(size_t index);

	int GetCountOfModules();

	void DeleteObject();
};


static class World {

private:
	static inline std::vector<Object*> ObjectsOnScene;

private:
	static inline bool IsCloseGame = false;

public:
	static inline void CloseGame();
	/// <summary>
	/// Return bool IsCloseGame
	/// </summary>
	static inline bool GetStateOfGame();

private:
	friend class Object;
	friend class Render;

	World();
};
