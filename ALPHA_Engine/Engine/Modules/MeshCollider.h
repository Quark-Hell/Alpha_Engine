#pragma once
#include "Modules/Geometry.h"

class CollisionInfo {
public:
	Vector3 Normal;
	float PenetrationDepth;
	bool HasCollision;

	//std::shared_ptr<std::vector<float>> CollisionPoints;
};

class MeshCollider : public Geometry {
public:
	MeshCollider();
	~MeshCollider();

	ModulesList GetType();

	bool CreateConvexFromConcave(std::string link);

	bool Create(std::string linkToFBX) override;

private:
	friend class Collision;

	CollisionInfo collisionInfo;
};