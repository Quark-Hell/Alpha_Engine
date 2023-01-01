#pragma once

#include "Basical_Type.h"

class Mesh : public Module {
private:
	std::vector <Vector3> Points;
	std::vector <Vector3> Normals;
	std::vector <unsigned int> Indices;
	//std::vector <Vector3> VertexColors;
	//std::vector <Vector3> TextureCoords;

private:
	friend class Render;

public:
	Mesh();
	~Mesh();

	bool CreateMesh(std::string linkToFBX);
	void DeleteMesh();
};