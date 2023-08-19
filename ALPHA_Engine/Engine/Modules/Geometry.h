#pragma once
#include "Module.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Modules/MovableModule.h"

class Object;
class Mesh;

class Geometry : public virtual MovableModule {
protected:
	bool _isIndexed = false;

	Object* _parentObject;

	float* _vertex;
	float* _normals;
	unsigned int* _indices;

	unsigned int _vertexCount = 0;
	unsigned int _normalsCount = 0;
	unsigned int _indicesCount = 0;

protected:
	friend class Object;
	friend class Render;
	friend class Collision;
	friend class Physics;
	friend class RigidBody;
	friend class AABB;

public:
	Geometry();
	virtual ~Geometry();

	ModulesList GetType() override;

	void ApplyTransformation() override;

	virtual bool Create(std::string linkToFBX);
	//virtual void Delete();

	virtual Vector3 FindFurthestPoint(Vector3 direction);

	std::vector<Mesh*> SeparateByLooseParts();

	/*Recommended not use now. Work so slow*/
	void MakeUnique();

};