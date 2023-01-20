#pragma once
#include "Basical_Type.h"

class Collider {
private:
	std::vector<Vector3> Points;
	std::vector<Vector3> Triangles;
	std::vector<Vector3> Normals;

private:
	friend class Collision;
};

class Collision : public Module {
private:
	Collider* GeneralCollider = new Collider;
	std::vector<Collider*> PrimitivesCollider{};

public:
	bool CreateCollision(std::string link);

private:
	bool SeparateCollision();
	bool CreateConvexFrom—oncave(std::string link);

	void SearchFrom(unsigned int from, std::vector<int>* vector);
	void SwapToEndAndDelete(unsigned int from, std::vector<int> *vector);
	void InsertTriangle(unsigned int PrimitiveObjectID, unsigned int TriangleID, unsigned int TriangleNum ,std::vector<int> *AdjacentTriangles);
};