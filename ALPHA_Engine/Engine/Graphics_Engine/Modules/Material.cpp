#include "Material.h"

Material::Material()
{
}

Material::~Material()
{
}

bool Material::InitShader()
{
    if (!Shader->InitShader())
        return false;

    return true;
}

Mesh* Material::GetParentMesh()
{
    return Material::_parentMesh;
}
