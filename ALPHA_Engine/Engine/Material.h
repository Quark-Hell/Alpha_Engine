#pragma once
#include "Basical_Type.h"
#include "Texture.h"

class Material
{
public:
	float Metallic;
	float Specular;
	float Roughness;
	float Anisotropic;
	float EmissionColor[3] = {0,0,0};
	float EmissionStrength;

	Texture Texture;

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