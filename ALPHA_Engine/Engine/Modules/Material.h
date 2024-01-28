#pragma once
#include "Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ShaderProgram.h"
#include "Modules/Mesh.h"

enum TypeOfTextuere {
	Diffuse = 0,
	Metallic = 1,
	Specular = 2,
	Roughness = 3,
	Anisotropic = 4,
	Emission = 5,
	NormalsMap = 6,
	OpacityMap = 7,
	OcclusionMap = 8
};

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

public:
	bool LoadMaterial(TypeOfTextuere typeOfTexture, std::string pathToTexture);
private:
	bool LoadMaterial(const aiScene& scene, unsigned int matIndex);

private:
	std::shared_ptr<ShaderProgram> _shader = std::make_shared<ShaderProgram>();
	Mesh* _parentMesh;

	void ApplyMaterialSettings(std::shared_ptr<Camera> camera);

	bool DeleteTexture(TypeOfTextuere typeOfTexture);
	void DeleteTextures();

	friend class Mesh;
	friend class ShaderProgram;
};
