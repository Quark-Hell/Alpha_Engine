#pragma once
#include "ShaderProgram.h"

class ColliderWireframeShader : public ShaderProgram {
public:
	ColliderWireframeShader(Material* parentMat);
	~ColliderWireframeShader();

	void ApplyShadersSettings(std::shared_ptr<Camera> camera) override;
};