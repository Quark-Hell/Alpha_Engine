#pragma once
#include "Basical_Type.h"
#include "Alghoritms.h"

//Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Collider {
private:
	std::vector<Vector3> Points;
	std::vector<Vector3> Triangles;
	std::vector<Vector3> Normals;

private:
	friend class Collision;
	friend class Graph;
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
};

