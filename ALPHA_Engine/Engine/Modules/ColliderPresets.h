#pragma once
#include "Modules/Module.h"
#include "Modules/Geometry.h"

class ColliderPresets : public Geometry {
protected:
	std::vector<float> _debugVertex;
	std::vector<unsigned int> _debugIndices;

protected:
	void ApplyTransformation();
	virtual void InitCollider(bool isExpand = true);

public:
	bool Create(std::string linkToFBX) override;

private:
	friend class Render;

public:
	ColliderPresets();
	~ColliderPresets();
};