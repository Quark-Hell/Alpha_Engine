#pragma once
#include "Modules/MeshCollider.h"

class BoxCollider : public MeshCollider {
private:
	friend Render;
	friend Collision;

private:
	void InitCollider();
	Vector3 CalculateCoverScale();

public:
	/*Expanded automatically*/
	BoxCollider();
	~BoxCollider();

	void SetParentObject(const Object& parent) override;

	void ReExpandedCollider();

	ModulesList GetType() override;
};


