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

	ModulesList GetType() override;

	virtual bool Create(std::string linkToFBX);
	//virtual void Delete();

	Vector3 FindFurthestPoint(Vector3 direction);

	std::vector<Mesh*> SeparateByLooseParts();

	/*Recommended not use now. Work so slow*/
	void MakeUnique();
	void ApplyTransformation();
};