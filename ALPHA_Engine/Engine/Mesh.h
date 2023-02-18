#pragma once

#include "Geometry.h"

class Mesh : public Geometry {
private:
	bool _isShifted = false;

private:
	friend class Object;

public:
	Mesh();
	~Mesh();

	bool Create(std::string linkToFBX) override;

	//bool Create(std::string linkToFBX) override;
	//void DeleteMesh() override;
};