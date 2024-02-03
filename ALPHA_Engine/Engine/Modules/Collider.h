#pragma once 
#include "Basical_Type.h"
#include "Modules/MovableModule.h"
#include "AABB.h"
#include "Material.h"

class Object;
struct aiScene;

class Collider : public virtual MovableModule, public AABB
{
protected:
	std::vector<float> _debugVertex;
	std::vector<unsigned int> _debugIndices;


	friend Render;

protected:
	void ApplyTransformation();
	virtual void InitCollider(bool isExpand = true);

public:
	Collider();
	~Collider();

	ModulesList GetType() override;
};

