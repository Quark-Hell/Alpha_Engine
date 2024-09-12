#pragma once
#include "ShaderProgram.h"

class ColliderWireframeShader : public ShaderProgram {
public:
	ColliderWireframeShader(Material* parentMat);
	~ColliderWireframeShader();

	void ApplyShadersSettings(std::shared_ptr<Camera> camera) override;

	Vector3 color = Vector3(0.322, 0.98, 0.125);
};