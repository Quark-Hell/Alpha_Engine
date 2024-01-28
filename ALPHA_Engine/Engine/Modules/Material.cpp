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

bool Material::LoadMaterial(TypeOfTextuere typeOfTexture, std::string pathToTexture)
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

bool Material::LoadMaterial(const aiScene& scene, unsigned int matIndex) {
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

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _diffuse.textureId);
}
