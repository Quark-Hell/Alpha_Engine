#pragma once
#include "Modules/Module.h"
#include "Modules/Geometry.h"

class ColliderPresets : public Geometry {
protected:
	//position relative to parent
	Vector3 _position{ 0,0,0 };
	glm::mat4x4 _transformMatrix = glm::mat4x4(1.0f);

protected:
	void ApplyTransformation();
	bool Create(std::string linkToFBX) override;
	virtual void InitCollider(bool isExpand = true);

private:
	friend class Render;

public:
	ColliderPresets();
	~ColliderPresets();

	Vector3 GetPosition();
	void SetPosition(Vector3 newPosition);
};