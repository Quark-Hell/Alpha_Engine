#pragma once
#include "Basical_Type.h"

class Object;

enum ModulesList {
	ModuleType = 0,
	CameraType = 1,
	RigidBodyType = 2,
	GeometryType = 3,
	ColliderType = 4,
	MeshType = 5
};

class Module
{
public:
	std::string Name = "Undefined";

protected:
	Object* ParentObject = nullptr;

private:
	friend class Render;
	friend class Collision;
	friend class Object;

public:
	virtual ModulesList GetType();
	Object* GetParentObject();

	virtual void SetParentObject(const Object& parent);
	
	Module();
	~Module();

private:
	virtual void Test();
};
