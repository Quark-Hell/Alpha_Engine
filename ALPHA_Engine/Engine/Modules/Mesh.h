#pragma once
#include "Geometry.h"

class Mesh : public Geometry {
private:
	friend class Object;

public:
	ModulesList GetType() override;

	Mesh();
	~Mesh();

	bool Create(std::string linkToFBX) override;

	//bool Create(std::string linkToFBX) override;
	//void DeleteMesh() override;
};