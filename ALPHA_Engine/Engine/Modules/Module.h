#pragma once
#include "Basical_Type.h"

class Object;

enum ModulesList {
	ModuleType = 0,
	CameraType = 1,
	RigidBodyType = 2,
	GeometryType = 3,
	MeshColliderType = 4,
	MeshType = 5,
	BoxColliderType = 6,
	LightType = 7,
	AmbientLightType = 8,
	DirectLightType = 9,
	PointLightType = 10,
	SpotLightType = 11,
	DebugMeshType = 12
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
	Module();
	~Module();

	virtual void Delete();
	
	virtual ModulesList GetType() = 0;

	virtual Object* GetParentObject();
	virtual void SetParentObject(const Object& parent);
};
