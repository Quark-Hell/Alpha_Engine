#pragma once
#include "Modules/Geometry.h"
#include "Modules/Collider.h"
#include "Modules/DebugMesh.h"

class MeshCollider : public Collider, public Geometry {
public:
	MeshCollider(std::string linkToFBX);
	MeshCollider();

	~MeshCollider();

	ModulesList GetType();

	bool CreateConvexFromConcave(std::string link);

	bool Create(std::string linkToFBX) override;
	bool Create();

	void SetParentObject(const Object& parent) override;

#pragma region Redifine from Transfom
	void ApplyTransformation() override;
#pragma endregion
	void InitTransformatiom(Object& newParent);
	void InitTransformatiom(Object& oldParent, Object& newParent);

#ifdef _DEBUG
protected:
	std::unique_ptr<DebugMesh> _debugMesh = std::make_unique<DebugMesh>();
#endif

private:
	friend class Collision;
	friend class Render;
};