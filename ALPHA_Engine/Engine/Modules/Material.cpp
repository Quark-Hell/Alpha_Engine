#include "Material.h"

Material::Material()
{
    _shader->CreateShader("\\Shaders\\BaseVertexShaders\\VertexShader.txt", ShadersType::VertexShader);
    _shader->CreateShader("\\Shaders\\BaseFragmentShaders\\FragmentShader.txt", ShadersType::FragmentShader);

    _shader->CompileShader();

    if (_shader->GetCompiledStatus()) {
        _shader->AttachShader();
        _shader->DeleteShader();
    }
    else {
        _shader->DeleteShader();
    }
}

Material::~Material()
{
    _shader->DeleteShader();
}

bool Material::LoadMaterial(const aiScene& scene, unsigned int matIndex) {
    Material::_diffuse.CreateTexture("\\Textures\\Logo.png");

    glGenTextures(1, &Material::_diffuse.textureId);
    glBindTexture(GL_TEXTURE_2D, Material::_diffuse.textureId);

    glTexImage2D(GL_TEXTURE_2D,
        0,
        GL_RGB,
        Material::_diffuse._width,
        Material::_diffuse._height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        Material::_diffuse._texture.get());

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glBindTexture(GL_TEXTURE_2D, 0);
    
    return false;
}