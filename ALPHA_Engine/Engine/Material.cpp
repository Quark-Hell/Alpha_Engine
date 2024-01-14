#include "materi"

Material::Material()
{
}

Material::~Material()
{
}

bool Material::LoadTextureCoord(std::string pathToCoords) {
    return false;
}

bool Material::LoadMaterial(const aiScene& scene, unsigned int matIndex) {
    Material::LoadTextureCoord(scene, matIndex);

    Texture text;
    text.CreateTexture("\\Textures\\Logo.png");
}

bool Material::LoadTextureCoord(const aiScene& scene, unsigned int matIndex) {
    //TODO: Check if fbx
    aiMesh* mesh = scene.mMeshes[0];
    if (!mesh->HasTextureCoords(0))
        return false;

    Material::_texCoords.get()->clear();
    Material::_texCoords.get()->resize(mesh->mNumVertices * 3);

    aiMaterial* material = scene.mMaterials[matIndex];

    aiString path;
    if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
        Material::_diffuse._texturePath = path.C_Str();
    }

    for (std::uint32_t it = 0; it < Material::Material::_texCoords.get()->size(); it++) {
        Material::_texCoords.get()->push_back(mesh->mTextureCoords[0][it].x);
        Material::_texCoords.get()->push_back(mesh->mTextureCoords[0][it].y);
    }
}