#pragma once

#include "Basical_Type.h"

//Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Mesh : public Module {
private:
	std::vector <Vector3> _points;
	std::vector <Vector3> _normals;

private:
	friend class Render;

public:
	Mesh();
	~Mesh();

	bool CreateMesh(std::string linkToFBX);
	void DeleteMesh();

	std::vector<Mesh*> SeparateMesh();
};