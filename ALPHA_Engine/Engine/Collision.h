#pragma once
#include "Basical_Type.h"

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

class Graph {
private:
	int numVertices;

	std::vector<std::vector<int>> adjLists;
	std::vector<bool> visited;

public:
	void AddEdge(int Src, int Dest);
	unsigned int GetAdjListSize();

	void DFS(int StartVertex, std::vector<int>* Output);
	void BFS(int StartVertex, std::vector<int>* Output);

	Graph(unsigned int size = 0);
};