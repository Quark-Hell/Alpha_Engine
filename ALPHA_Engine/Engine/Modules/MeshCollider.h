#pragma once
#include "Modules/Geometry.h"
#include "Modules/Collider.h"

class MeshCollider : public Collider, public Geometry {
public:
	MeshCollider(std::string linkToFBX);
	MeshCollider();


	~MeshCollider();

	ModulesList GetType();

	bool CreateConvexFromConcave(std::string link);

	bool Create(std::string linkToFBX) override;
	void ApplyTransformation() override;

private:
	friend class Collision;
};