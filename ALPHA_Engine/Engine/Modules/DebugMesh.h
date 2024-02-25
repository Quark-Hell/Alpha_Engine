#pragma once

#include "Mesh.h"

class DebugMesh : public Mesh {
public:
	DebugMesh();
	virtual ~DebugMesh();


public:
	ModulesList GetType() override;

	bool Create(std::string linkToFBX) override;
	bool Create(Geometry& geometry, bool copyIndices = true);

	bool BindMesh() override;
};