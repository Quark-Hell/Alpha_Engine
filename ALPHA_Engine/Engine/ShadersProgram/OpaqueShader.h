#pragma once
#include "ShaderProgram.h"

class OpaqueShader : public ShaderProgram {
public:
	Texture _diffuse;
	Texture _metallic;
	Texture _specular;
	Texture _roughness;
	Texture _anisotropic;
	Texture _emission;
	Texture _normalsMap;
	Texture _opacityMap;
	Texture _occlusionMap;

public:
	OpaqueShader();
	~OpaqueShader();

	bool LoadTexture(TypeOfTextuere typeOfTexture, std::string pathToTexture) override;
	void ApplyShadersSettings(std::shared_ptr<Camera> camera) override;
};