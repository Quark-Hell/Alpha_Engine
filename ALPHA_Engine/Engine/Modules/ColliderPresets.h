#pragma once
#include "Modules/Module.h"

class ColliderPresets : public Module {
protected:
	//position relative to parent
	Vector3 _position{ 0,0,0 };

	float* _vertex;
	unsigned int _vertexCount;

	glm::mat4x4 _transformMatrix = glm::mat4x4(1.0f);

protected:
	virtual void CreateMeshModel();
	void ApplyTransformation();

private:
	friend class Render;

public:
	ColliderPresets(unsigned int vertexCount);
	~ColliderPresets();

	Vector3 GetPosition();
	void SetPosition(Vector3 newPosition);
};