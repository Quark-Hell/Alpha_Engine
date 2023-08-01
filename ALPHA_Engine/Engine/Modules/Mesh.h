#pragma once
#include "Geometry.h"

class Mesh : public Geometry {
private:
	friend class Object;

public:
	Mesh();
	~Mesh();

	ModulesList GetType() override;

	void SetParentObject(const Object& parent) override;

	//bool Create(std::string linkToFBX) override;
	//void DeleteMesh() override;
};