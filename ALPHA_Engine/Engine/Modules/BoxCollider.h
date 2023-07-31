#pragma once
#include "ColliderPresets.h"

class BoxCollider : public ColliderPresets {
public:
	float* _points = new float[24];

private:
	void InitCollider();
	Vector3 CalculateCoverScale();

public:
	/*Expanded automatically*/
	BoxCollider();
	~BoxCollider();

	void ReExpandedCollider();

	void ApplyTransformation() override;

	ModulesList GetType() override;

	Vector3 FindFurthestPoint(Vector3 direction) override;
};


