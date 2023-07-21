#pragma once
#include "ColliderPresets.h"

class BoxCollider : public ColliderPresets {
private:
	float _height = 1;
	float _width = 1;
	float _lenght = 1;

private:
	void CreateMeshModel() override;

public:
	BoxCollider(float height = 1, float width = 1, float length = 1);
	~BoxCollider();

	inline float GetHeight();
	void SetHeight(float heigth);

	float GetWidth();
	void SetWidth(float width);

	float GetLength();
	void SetLength(float length);
};


