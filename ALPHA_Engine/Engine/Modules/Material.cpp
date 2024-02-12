#include "Material.h"

Material::Material()
{
    _shader->_parentMaterial = this;

    Material::LoadTexture(Diffuse, "\\Textures\\EmptyTexture.png");
    Material::LoadTexture(Metallic, "\\Textures\\EmptyTexture.png");
    Material::LoadTexture(Specular, "\\Textures\\EmptyTexture.png");
    Material::LoadTexture(Roughness, "\\Textures\\EmptyTexture.png");
    Material::LoadTexture(Anisotropic, "\\Textures\\EmptyTexture.png");
    Material::LoadTexture(Emission, "\\Textures\\EmptyEmission.png");
    Material::LoadTexture(NormalsMap, "\\Textures\\EmptyTexture.png");
    Material::LoadTexture(OpacityMap, "\\Textures\\EmptyTexture.png");
    Material::LoadTexture(OcclusionMap, "\\Textures\\EmptyTexture.png");

    Material::InitShader("\\Shaders\\BaseVertexShaders\\VertexShader.txt", ShadersType::VertexShader);
    Material::InitShader("\\Shaders\\BaseFragmentShaders\\FragmentShader.txt", ShadersType::FragmentShader);
}

Material::~Material()
{
    if (_shader != nullptr) {
        _shader->DeleteShaders();
    }
}

bool Material::InitShader(std::string pathToShader, ShadersType shaderType)
{
    _shader->CreateShader(pathToShader.c_str(), shaderType);

    _shader->CompileShader();

    if (_shader->GetCompiledStatus()) {
        _shader->AttachShader();
        _shader->DeleteShader(shaderType);
    }
    else {
        _shader->DeleteShader(shaderType);
    }

    return true;
}

bool Material::LoadTexture(TypeOfTextuere typeOfTexture, std::string pathToTexture)
{
    unsigned char* data = nullptr;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int channels = 0;

    switch (typeOfTexture)
    {
    case Diffuse:
        Material::_diffuse.CreateTexture(pathToTexture.c_str());
        glGenTextures(1, &Material::_diffuse.textureId);
        glBindTexture(GL_TEXTURE_2D, Material::_diffuse.textureId);

        data = Material::_diffuse._texture.get();
        width = Material::_diffuse._width;
        height = Material::_diffuse._height;
        channels = Material::_diffuse._channelsCount;
        break;
    case Metallic:
        Material::_metallic.CreateTexture(pathToTexture);
        glGenTextures(1, &Material::_metallic.textureId);
        glBindTexture(GL_TEXTURE_2D, Material::_metallic.textureId);

        data = Material::_metallic._texture.get();
        width = Material::_metallic._width;
        height = Material::_metallic._height;
        channels = Material::_diffuse._channelsCount;
        break;
    case Specular:
        Material::_specular.CreateTexture(pathToTexture);
        glGenTextures(1, &Material::_specular.textureId);
        glBindTexture(GL_TEXTURE_2D, Material::_specular.textureId);

        data = Material::_specular._texture.get();
        width = Material::_specular._width;
        height = Material::_specular._height;
        channels = Material::_diffuse._channelsCount;
        break;
    case Roughness:
        Material::_roughness.CreateTexture(pathToTexture);
        glGenTextures(1, &Material::_roughness.textureId);
        glBindTexture(GL_TEXTURE_2D, Material::_roughness.textureId);

        data = Material::_roughness._texture.get();
        width = Material::_roughness._width;
        height = Material::_roughness._height;
        channels = Material::_diffuse._channelsCount;
        break;
    case Anisotropic:
        Material::_anisotropic.CreateTexture(pathToTexture);
        glGenTextures(1, &Material::_anisotropic.textureId);
        glBindTexture(GL_TEXTURE_2D, Material::_anisotropic.textureId);

        data = Material::_anisotropic._texture.get();
        width = Material::_anisotropic._width;
        height = Material::_anisotropic._height;
        channels = Material::_diffuse._channelsCount;
        break;
    case Emission:
        Material::_emission.CreateTexture(pathToTexture);
        glGenTextures(1, &Material::_emission.textureId);
        glBindTexture(GL_TEXTURE_2D, Material::_emission.textureId);

        data = Material::_emission._texture.get();
        width = Material::_emission._width;
        height = Material::_emission._height;
        channels = Material::_diffuse._channelsCount;
        break;
    case NormalsMap:
        Material::_normalsMap.CreateTexture(pathToTexture);
        glGenTextures(1, &Material::_normalsMap.textureId);
        glBindTexture(GL_TEXTURE_2D, Material::_normalsMap.textureId);

        data = Material::_normalsMap._texture.get();
        width = Material::_normalsMap._width;
        height = Material::_normalsMap._height;
        channels = Material::_diffuse._channelsCount;
        break;
    case OpacityMap:
        Material::_opacityMap.CreateTexture(pathToTexture);
        glGenTextures(1, &Material::_opacityMap.textureId);
        glBindTexture(GL_TEXTURE_2D, Material::_opacityMap.textureId);

        data = Material::_opacityMap._texture.get();
        width = Material::_opacityMap._width;
        height = Material::_opacityMap._height;
        channels = Material::_diffuse._channelsCount;
        break;
    case OcclusionMap:
        Material::_occlusionMap.CreateTexture(pathToTexture);
        glGenTextures(1, &Material::_occlusionMap.textureId);
        glBindTexture(GL_TEXTURE_2D, Material::_occlusionMap.textureId);

        data = Material::_occlusionMap._texture.get();
        width = Material::_occlusionMap._width;
        height = Material::_occlusionMap._height;
        channels = Material::_diffuse._channelsCount;
        break;
    default:
        std::cout << "Error load texture: unknown format of texture\n";
        return false;
    }

    if (data == nullptr) {
        std::cout << "Error load texture: undefined path to texture\n";
        return false;
    }

    if (width == 0 || height == 0 || channels == 0) {
        std::cout << "Error load texture: unknown format of texture\n";
        return false;
    }

    if (channels == 3) {
        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGB,
            width,
            height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            data);
    }
    else if (channels == 4) {
        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGBA,
            width,
            height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            data);
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    Material::DeleteTexture(typeOfTexture);

    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

bool Material::LoadTexture(const aiScene& scene, unsigned int matIndex) {
    Material::_diffuse.CreateTexture("\\Textures\\crate.png");

    glGenTextures(1, &Material::_diffuse.textureId);
    glBindTexture(GL_TEXTURE_2D, Material::_diffuse.textureId);


    glTexImage2D(GL_TEXTURE_2D,
        0,
        GL_RGB,
        Material::_diffuse._width,
        Material::_diffuse._height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        Material::_diffuse._texture.get());

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    Material::_diffuse.DeleteTexture();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return false;
}

bool Material::DeleteTexture(TypeOfTextuere typeOfTexture)
{
    switch (typeOfTexture)
    {
    case Diffuse:
        Material::_diffuse.DeleteTexture();
        break;
    case Metallic:
        Material::_metallic.DeleteTexture();
        break;
    case Specular:
        Material::_specular.DeleteTexture();
        break;
    case Roughness:
        Material::_roughness.DeleteTexture();
        break;
    case Anisotropic:
        Material::_anisotropic.DeleteTexture();
        break;
    case Emission:
        Material::_emission.DeleteTexture();
        break;
    case NormalsMap:
        Material::_normalsMap.DeleteTexture();
        break;
    case OpacityMap:
        Material::_opacityMap.DeleteTexture();
        break;
    case OcclusionMap:
        Material::_occlusionMap.DeleteTexture();
        break;
    default:
        std::cout << "Error load texture: unknown format of texture\n";
        return false;
    }

    return false;
}

void Material::DeleteTextures()
{
    Material::_diffuse.DeleteTexture();
    Material::_metallic.DeleteTexture();
    Material::_specular.DeleteTexture();
    Material::_roughness.DeleteTexture();
    Material::_anisotropic.DeleteTexture();
    Material::_emission.DeleteTexture();
    Material::_normalsMap.DeleteTexture();
    Material::_opacityMap.DeleteTexture();
    Material::_occlusionMap.DeleteTexture();
}

void Material::ApplyMaterialSettings(std::shared_ptr<Camera> camera)
{
    Material::_shader->ApplyShadersSettings(camera);

    if (_diffuse.textureId != 0) {
        glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_2D, _diffuse.textureId);

        _diffuse.textureLocation = glGetUniformLocation(Material::_shader->_programId.value(), "diffuseMap");
        glUniform1i(_diffuse.textureLocation, 0);
    }
    if (_metallic.textureId != 0) {
        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, _metallic.textureId);

        //_metallic.textureLocation = glGetUniformLocation(Material::_shader->_programId.value(), "diffuseMap");
        //glUniform1i(_metallic.textureLocation, 1);
    }
    if (_specular.textureId != 0) {
        glActiveTexture(GL_TEXTURE0 + 2);
        glBindTexture(GL_TEXTURE_2D, _specular.textureId);
    }
    if (_roughness.textureId != 0) {
        glActiveTexture(GL_TEXTURE0 + 3);
        glBindTexture(GL_TEXTURE_2D, _roughness.textureId);
    }
    if (_anisotropic.textureId != 0) {
        glActiveTexture(GL_TEXTURE0 + 4);
        glBindTexture(GL_TEXTURE_2D, _anisotropic.textureId);
    }
    if (_emission.textureId != 0) {
        glActiveTexture(GL_TEXTURE0 + 5);
        glBindTexture(GL_TEXTURE_2D, _emission.textureId);

        _emission.textureLocation = glGetUniformLocation(Material::_shader->_programId.value(), "emissionMap");
        glUniform1i(_emission.textureLocation, 5);
    }
    if (_normalsMap.textureId != 0) {
        glActiveTexture(GL_TEXTURE0 + 6);
        glBindTexture(GL_TEXTURE_2D, _normalsMap.textureId);
    }
    if (_opacityMap.textureId != 0) {
        glActiveTexture(GL_TEXTURE0 + 7);
        glBindTexture(GL_TEXTURE_2D, _opacityMap.textureId);
    }
    if (_occlusionMap.textureId != 0) {
        glActiveTexture(GL_TEXTURE0 + 8);
        glBindTexture(GL_TEXTURE_2D, _occlusionMap.textureId);
    }
}
