#pragma once

#include "Basical_Type.h"

//Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Geometry : public Module {
private:
	Object* _parentObject;

	float* _vertex;
	float* _normals;
	float* _indices;

	unsigned int _vertexCount;
	unsigned int _normalsCount;
	unsigned int _indicesCount;

private:
	friend class Object;
	friend class Render;
	friend class Collision;
	friend class Mesh;
	friend class Collider;

public:
	Geometry();
	~Geometry();

	virtual bool Create(std::string linkToFBX);
	//virtual void Delete();

	Vector3 FindFurthestPoint(Vector3 direction);

	std::vector<Mesh*> SeparateByLooseParts();

	/*Recommended not use now. Work so slow*/
	void MakeUnique();
	void ApplyTransformation();
};