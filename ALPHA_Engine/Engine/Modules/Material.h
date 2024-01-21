#pragma once
#include "Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ShaderProgram.h"

class Material
{
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

	friend class Render;

public:	
	Material();
	~Material();

	bool LoadMaterial(const aiScene& scene, unsigned int matIndex);

private:
	std::shared_ptr<ShaderProgram> _shader = std::make_shared<ShaderProgram>();
};
