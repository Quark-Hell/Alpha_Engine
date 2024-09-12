#pragma once 
#include "Basical_Type.h"
#include "Modules/MovableModule.h"
#include "AABB.h"
#include "Material.h"

class Object;
struct aiScene;

class Collider : public virtual MovableModule
{
protected:
	std::unique_ptr<AABB> _AABB = std::make_unique<AABB>();

	friend Render;

protected:
	void ApplyTransformation() override;
	virtual void InitCollider(bool isExpand = true);

public:
	Collider();
	~Collider();

	ModulesList GetType() override;
};

