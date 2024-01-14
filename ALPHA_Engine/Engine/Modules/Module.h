#pragma once
#include "Basical_Type.h"
#include "SubModules/SubModule.h"

class Object;

enum ModulesList {
	ModuleType = 0,
	CameraType = 1,
	RigidBodyType = 2,
	GeometryType = 3,
	MeshColliderType = 4,
	MeshType = 5,
	BoxColliderType = 6,
};

class Module
{
public:
	std::string Name = "Undefined";

protected:
	Object* ParentObject = nullptr;
	std::vector<std::shared_ptr<SubModule>> _subModules;

private:
	friend class Render;
	friend class Collision;
	friend class Object;

public:
	Module();
	~Module();
	
	virtual ModulesList GetType() = 0;

	virtual Object* GetParentObject();
	virtual void SetParentObject(const Object& parent);

	virtual bool AddSubModule(std::shared_ptr<SubModule> subModule);
	virtual bool AddSubModule(SubModulesList type);

	std::shared_ptr<SubModule> GetSubModuleByType(SubModulesList type);
};
