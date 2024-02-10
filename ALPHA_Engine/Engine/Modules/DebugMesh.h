#pragma once

#include "Mesh.h"

class DebugMesh : public Mesh{
public:
	DebugMesh();
	virtual ~DebugMesh();

private:
	friend class Object;
	friend class Render;
	friend class MeshCollider;

private:
	unsigned int _vertexVbo = 0;
	unsigned int _vao = 0;

public:
	std::shared_ptr<Material> _material = std::make_shared<Material>();

public:
	ModulesList GetType() override;

	bool Create(std::string linkToFBX) override;
	bool Create(Geometry& geometry);

	bool BindMesh() override;

protected:
	void ApplyMeshSettings(std::shared_ptr<Camera> camera) override;
};