#pragma once
#include "Geometry.h"

class SubModule;

class Mesh : public Geometry {
private:
	friend class Object;

public:
	Mesh();
	~Mesh();

	ModulesList GetType() override;

	void SetParentObject(const Object& parent) override;

	bool AddSubModule(std::shared_ptr<SubModule> subModule) override;
	bool AddSubModule(SubModulesList type) override;

	bool Create(std::string linkToFBX) override;

	//bool Create(std::string linkToFBX) override;
	//void DeleteMesh() override;
};