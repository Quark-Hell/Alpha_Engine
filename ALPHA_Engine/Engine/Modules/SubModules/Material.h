#pragma once
#include "Texture.h"

#include "SubModule.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Material : public SubModule
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

	SubModulesList GetType() override;

	bool LoadMaterial(const aiScene& scene, unsigned int matIndex);

	bool LoadTextureCoord(std::string pathToCoords);
	bool LoadTextureCoord(const aiScene& scene, unsigned int matIndex);

private:
	std::shared_ptr<std::vector<float>> _texCoords = std::make_shared<std::vector<float>>(std::vector<float>());
};
