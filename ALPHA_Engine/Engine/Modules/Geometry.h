#pragma once
#include "Module.h"

class Object;

class Geometry : public Module {
private:
	bool _isShifted = false;
	bool _isIndexed = false;

	Object* _parentObject;

	float* _vertex;
	float* _normals;
	unsigned int* _indices;

	unsigned int _vertexCount = 0;
	unsigned int _normalsCount = 0;
	unsigned int _indicesCount = 0;

private:
	friend class Object;
	friend class Render;
	friend class Collision;
	friend class Mesh;
	friend class Collider;
	friend class Physics;
	friend class RigidBody;

public:
	Geometry();
	~Geometry();

	ModulesList GetType() override;

	virtual bool Create(std::string linkToFBX);
	//virtual void Delete();

	Vector3 FindFurthestPoint(Vector3 direction);

	std::vector<Mesh*> SeparateByLooseParts();

	/*Recommended not use now. Work so slow*/
	void MakeUnique();
	void ApplyTransformation();
};