#pragma once

#include "Basical_Type.h"

//Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Mesh : public Module {
private:
	std::vector <Vector3> _vertex;
	std::vector <Vector3> _normals;
	std::vector <unsigned int> _indices;
	bool _isShifted = false;

private:
	friend class Object;
	friend class Render;
	friend class Collider;
	friend class Collision;

public:
	Mesh();
	~Mesh();

	bool CreateMesh(std::string linkToFBX);
	void DeleteMesh();

	Vector3 FindFurthestPoint(Vector3 direction);

	std::vector<Mesh*> SeparateMesh();

	void ApplyTransformation();

	static inline void MakeUnique(std::vector<Vector3>* data);
};