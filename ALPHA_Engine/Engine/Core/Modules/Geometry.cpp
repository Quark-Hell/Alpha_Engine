#include "Core/Modules/Geometry.h"

Geometry::Geometry() {

}
Geometry::~Geometry() {

}

Object* Geometry::GetParentObject() {
    return ParentObject;
}
void Geometry::SetParentObject(const Object& parent) {
    ParentObject = const_cast<Object*>(&parent);
}

ModulesList Geometry::GetType() {
    return GeometryType;
}

bool Geometry::Create(std::string linkToFBX) {
    Geometry::_vertex->clear();
    Geometry::_indices->clear();
    Geometry::_normals->clear();

    Assimp::Importer importer;
    std::string path = std::filesystem::current_path().string() + linkToFBX.c_str();

    //TODO: Check if fbx
    const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
    aiMesh* mesh = s->mMeshes[0];

    Geometry::_indices->resize(mesh->mNumFaces * 3);

    for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
        for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
        {
            (*Geometry::_indices)[(it * 3) + jt] = mesh->mFaces[it].mIndices[jt];
        }
    }

    Geometry::_vertex->resize(mesh->mNumVertices * 3);

    for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {
        if (mesh->HasPositions()) {
            (*Geometry::_vertex)[it] = mesh->mVertices[it / 3].x;
            (*Geometry::_vertex)[it + 1] = mesh->mVertices[it / 3].y;
            (*Geometry::_vertex)[it + 2] = mesh->mVertices[it / 3].z;
        }
    }

    Geometry::_normals->resize(Geometry::_vertex->size());

    for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {
        if (mesh->HasNormals()) {
            (*Geometry::_normals)[it] = mesh->mNormals[it / 3].x;
            (*Geometry::_normals)[it + 1] = mesh->mNormals[it / 3].y;
            (*Geometry::_normals)[it + 2] = mesh->mNormals[it / 3].z;
        }
    }


    Geometry::_isIndexed = true;

    return true;
}

bool Geometry::Create(std::string linkToFBX,
    bool initIndices,
    bool initVertex,
    bool initNormals,
    bool initTexCoord,
    bool initMaterial)
{
    Geometry::_vertex->clear();
    Geometry::_indices->clear();
    Geometry::_normals->clear();

    Assimp::Importer importer;
    std::string path = std::filesystem::current_path().string() + linkToFBX.c_str();

    //TODO: Check if fbx
    const aiScene* s;
    aiMesh* mesh;

    if (initIndices) {
        s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
        mesh = s->mMeshes[0];

        Geometry::_indices->resize(mesh->mNumFaces * 3);

        for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
            for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
            {
                (*Geometry::_indices)[(it * 3) + jt] = mesh->mFaces[it].mIndices[jt];
            }
        }

        Geometry::_isIndexed = true;
    }
    else
    {
        s = importer.ReadFile(path, aiProcess_Triangulate);
        mesh = s->mMeshes[0];

        Geometry::_isIndexed = false;
    }

    if (mesh->HasPositions() && initVertex) {
        Geometry::_vertex->resize(mesh->mNumVertices * 3);
        for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

            (*Geometry::_vertex)[it] = mesh->mVertices[it / 3].x;
            (*Geometry::_vertex)[it + 1] = mesh->mVertices[it / 3].y;
            (*Geometry::_vertex)[it + 2] = mesh->mVertices[it / 3].z;
        }
    }


    if (mesh->HasNormals() && initNormals) {
        Geometry::_normals->resize(Geometry::_vertex->size());

        for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

            (*Geometry::_normals)[it] = mesh->mNormals[it / 3].x;
            (*Geometry::_normals)[it + 1] = mesh->mNormals[it / 3].y;
            (*Geometry::_normals)[it + 2] = mesh->mNormals[it / 3].z;
        }
    }

    return true;
}

bool Geometry::ShiftVertexArray(int shiftCount)
{
    if (shiftCount == 0)
        return false;

    if (Geometry::_vertex->size() + shiftCount < 0)
        return false;

    if (abs(shiftCount) >= Geometry::_vertex->size())
        return false;

    float* data = Geometry::_vertex->data();
    if (data == nullptr)
        return false;

    shiftCount *= -1;
    memmove(data, data + (shiftCount * 3), Geometry::_vertex->size() * sizeof(float));

    if (shiftCount < 0) {
        Geometry::_vertex->erase(Geometry::_vertex->begin(), Geometry::_vertex->begin() + (shiftCount * 3));
    }
    else
    {
        Geometry::_vertex->erase(Geometry::_vertex->end() - (shiftCount * 3), Geometry::_vertex->end());
    }

    return true;
}

Vector3 Geometry::FindFurthestPoint(Vector3 direction) {
    Vector3 maxPoint = { 0,0,0 };
    float maxDistance = -FLT_MAX;
    Vector3 vertexPos = { 0,0,0 };

    for (size_t it = 0; it < Geometry::_vertex->size(); it += 3) {

        vertexPos.X = (*Geometry::_vertex)[it];
        vertexPos.Y = (*Geometry::_vertex)[it + 1];
        vertexPos.Z = (*Geometry::_vertex)[it + 2];

        float distance = Vector3::DotProduct(vertexPos, direction);
        if (distance > maxDistance) {
            maxDistance = distance;
            maxPoint = vertexPos;
        }
    }

    return maxPoint + Geometry::GetParentObject()->GetPosition();
}