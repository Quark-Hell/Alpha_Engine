#pragma once
#include "Modules/ColliderPresets.h"

class MeshCollider : public ColliderPresets {
public:
	MeshCollider();
	~MeshCollider();

	ModulesList GetType();

	bool CreateConvexFromConcave(std::string link);

	//bool Create(std::string linkToFBX) override;

private:
	friend class Collision;
};