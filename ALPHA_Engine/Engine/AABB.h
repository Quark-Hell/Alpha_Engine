#pragma once
#include "Basical_Type.h"

class Render;

class AABB {
private:
	float _minX = 0, _minY = 0, _minZ = 0;
	float _maxX = 1, _maxY = 1, _maxZ = 1;

private:
	Vector3 _position;
	Vector3 _scale{0,0,0};

public:
	AABB(
		float minX, float maxX,
		float minY, float maxY,
		float minZ, float maxZ);
	AABB();

	virtual ~AABB();

	void SetSize(
		float minX = 0, float maxX = 0,
		float minY = 0, float maxY = 0,
		float minZ = 0, float maxZ = 0);

	float GetMinX();
	float GetMaxX();
	float GetMinY();
	float GetMaxY();
	float GetMinZ();
	float GetMaxZ();

	void GetSize(float& minX, float& maxX, float& minY, float& maxY, float& minZ, float& maxZ);

	Vector3 GetAABBPosition();

protected:
	void UpdateAABB(const float* vertex, float vertexCount);
	void UpdateAABB(float radius);

	friend Render;

#ifdef _DEBUG
protected:
	std::vector<float> _AABBvertex;
	std::vector<unsigned int> _AABBindices;

protected:
	void CreateAABB();
#endif // _DEBUG

};
