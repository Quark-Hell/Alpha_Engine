#include "Material.h"

Material::Material()
{
    _shader->_parentMaterial = this;

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
    Material::_diffuse.CreateTexture("\\Textures\\crate.jpg");

    glGenTextures(1, &Material::_diffuse.textureId);
    glBindTexture(GL_TEXTURE_2D, Material::_diffuse.textureId);

    unsigned char* data = Material::_diffuse._texture.get();

    glTexImage2D(GL_TEXTURE_2D,
        0,
        GL_RGB,
        Material::_diffuse._width,
        Material::_diffuse._height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        data);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glBindTexture(GL_TEXTURE_2D, 0);
    
    return false;
}

void Material::ApplyMaterialSettings(std::shared_ptr<Camera> camera)
{
    Material::_shader->ApplyShadersSettings(camera);

    //int v = 0;

    //Material::_shader->SetValue(ShadersType::FragmentShader, "diffuseMap", &v);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _diffuse.textureId);
}
