#pragma once
#include "Modules/Module.h"
#include "Modules/Geometry.h"

class ColliderPresets : public Geometry {
protected:
	void ApplyTransformation();
	bool Create(std::string linkToFBX) override;
	virtual void InitCollider(bool isExpand = true);

private:
	friend class Render;

public:
	ColliderPresets();
	~ColliderPresets();
};