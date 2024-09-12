#pragma once
#include "Basical_Type.h"
#include "Modules/Mesh.h"
#include "Modules/DebugMesh.h"

class Render;
class MeshCollider;
class Object;

class AABB {
private:
	Vector3 _position;
	Vector3 _originPos;

	Vector3 _scale{0,0,0};

private:
	void UpdateAABB(Object& parentObject);
	void UpdateAABB(float radius);

	void ApplyTransformation(Object& parentObject);

#ifdef _DEBUG
protected:
	std::unique_ptr<DebugMesh> _AABBMesh = std::make_unique<DebugMesh>();
#endif // _DEBUG

public:
	AABB(Object& parentObject);
	AABB();

	virtual ~AABB();

	void SetSize(Vector3 scale);

	Vector3 GetSize();

	Vector3 GetAABBPosition();

	friend Render;
	friend MeshCollider;

#ifdef _DEBUG
protected:
	void CreateAABB();
#endif // _DEBUG


};
