#pragma once
#include "Texture.h"

class Material
{
public:
	Texture _colorMap;
	Texture _metallic;
	Texture _specular;
	Texture _roughness;
	Texture _anisotropic;
	Texture _emission;
	Texture _normalsMap;
	Texture _opacityMap;
	Texture _occlusionMap;

public:	
	Material();
	~Material();

private:

};

Material::Material()
{
}

Material::~Material()
{
}