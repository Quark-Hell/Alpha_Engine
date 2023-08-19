#pragma once
#include "Basical_Type.h"

class Render;

class AABB {
public:
	float MinX = 0, MinY = 0, MinZ = 0;
	float MaxX = 0, MaxY = 0, MaxZ = 0;

private:
	Vector3 _position;
	Vector3 _scale{0,0,0};

public:
	AABB(
		float minX = 0, float maxX = 0, 
		float minY = 0, float maxY = 0,
		float minZ = 0, float maxZ = 0);
	virtual ~AABB();

	void SetSize(
		float minX = 0, float maxX = 0,
		float minY = 0, float maxY = 0,
		float minZ = 0, float maxZ = 0);

	friend Render;

#ifdef _DEBUG
	friend Render;

protected:
	void CreateAABB();
	void UpdateAABB(const float* vertex, float vertexCount);
	void UpdateAABB(float radius);

protected:
	std::vector<float> _AABBvertex;
	std::vector<unsigned int> _AABBindices;
#endif // _DEBUG

};
