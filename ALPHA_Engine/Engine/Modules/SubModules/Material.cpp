#include "Material.h"

Material::Material()
{
}

Material::~Material()
{
}

SubModulesList Material::GetType() {
    return SubModulesList::MaterialType;
}

bool Material::LoadTextureCoord(std::string pathToCoords) {
    return false;
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

bool Material::LoadTextureCoord(const aiScene& scene, unsigned int matIndex) {
    //TODO: Check if fbx
    aiMesh* mesh = scene.mMeshes[0];
    if (!mesh->HasTextureCoords(0))
        return false;

    Material::_texCoords.get()->clear();
    //Material::_texCoords.get()->resize(mesh->mNumVertices * 2);

    aiMaterial* material = scene.mMaterials[matIndex];

    aiString path;
    if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
        Material::_diffuse._texturePath = path.C_Str();
    }

    for (std::uint32_t it = 0; it < mesh->mNumVertices * 2; it++) {
        Material::_texCoords.get()->push_back(mesh->mTextureCoords[0][it].x);
        Material::_texCoords.get()->push_back(mesh->mTextureCoords[0][it].y);
    }
}