#include "Material.h"

GraphicsEngine::Material::Material()
{
}

GraphicsEngine::Material::~Material()
{
}

bool GraphicsEngine::Material::InitShader()
{
    if (!Shader->InitShader())
        return false;

    return true;
}

Mesh* GraphicsEngine::Material::GetParentMesh()
{
    return Material::_parentMesh;
}
