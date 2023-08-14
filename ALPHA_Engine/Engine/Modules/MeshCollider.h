#pragma once
#include "Modules/ColliderPresets.h"

class MeshCollider : public ColliderPresets {
public:
	MeshCollider(std::string linkToFBX);
	MeshCollider();


	~MeshCollider();

	ModulesList GetType();

	bool CreateConvexFromConcave(std::string link);

private:
	friend class Collision;
};