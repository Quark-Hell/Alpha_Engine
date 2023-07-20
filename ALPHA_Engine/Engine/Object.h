#pragma once
#include "Basical_Type.h"
#include "Matrix.h"

class Matrix4x4;
class Module;
class Vector4;
class Vector3;

class Object {

private:
	Vector3 Position{ 0,0,0 };
	Vector4 Rotation{ 0,0,0,1 };
	Vector3 Scale{ 1,1,1 };

	glm::mat4x4 _transformMatrix{};

	std::vector<Module*> Modules;

private:
	friend class Geometry;

public:
	Object();
	~Object();

	Vector3 GetPosition();
	void AddPosition(float X, float Y, float Z);
	void AddPosition(Vector3 position);

	void SetPosition(float X, float Y, float Z);
	void SetPosition(Vector3 position);


	Vector3 GetRotation();
	void AddRotation(float X, float Y, float Z);
	void AddRotation(Vector3 rotation);

	void SetRotation(float X, float Y, float Z);
	void SetRotation(Vector3 rotation);


	Vector3 GetScale();
	void SetScale(float X, float Y, float Z);
	void SetScale(Vector3 scale);

	/*SetPosition, SetRotation and SetScale functions only change matrix of _transformMatrix.
	So this function apply transformation to object and recalculate vertex relative position;
	*/
	void ApplyTransform();

	bool AddModule(class Module* someModule);
	bool AddModule(ModulesList moduleType, Module& outputModule);

	bool DeleteModuleByType(ModulesList type);
	bool DeleteModuleByIndex(int index);

	Module* GetModuleByType(ModulesList type);
	Module* GetModuleByIndex(size_t index);

	int GetCountOfModules();

	void DeleteObject();

	unsigned long GetGeometryHeaviness();
};