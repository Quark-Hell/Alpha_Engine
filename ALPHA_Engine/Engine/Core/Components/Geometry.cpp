#include "Core/Components/Geometry.h"
#include "Core/Object.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <filesystem>

Core::Geometry::Geometry() {

}
Core::Geometry::~Geometry() {

}

bool Core::Geometry::Create(const std::string& linkToFBX) {
    Geometry::_vertex->clear();
    Geometry::_indices->clear();
    Geometry::_normals->clear();

    Assimp::Importer importer;
    const std::string path = std::filesystem::current_path().string() + linkToFBX;

    //TODO: Check if fbx
    const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
    const aiMesh* mesh = s->mMeshes[0];

    Geometry::_indices->resize(mesh->mNumFaces * 3);

    for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
        for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
        {
            (*Geometry::_indices)[(it * 3) + jt] = mesh->mFaces[it].mIndices[jt];
        }
    }

    Geometry::_vertex->resize(mesh->mNumVertices * 3);

    if (mesh->HasPositions()) {
        Geometry::_vertex->resize(mesh->mNumVertices * 3);

        for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

            (*Geometry::_vertex)[it] = mesh->mVertices[it / 3].x;
            (*Geometry::_vertex)[it + 1] = mesh->mVertices[it / 3].y;
            (*Geometry::_vertex)[it + 2] = mesh->mVertices[it / 3].z;
        }
    }


    if (mesh->HasNormals()) {
        Geometry::_normals->resize(Geometry::_vertex->size());

        for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {
            (*Geometry::_normals)[it] = mesh->mNormals[it / 3].x;
            (*Geometry::_normals)[it + 1] = mesh->mNormals[it / 3].y;
            (*Geometry::_normals)[it + 2] = mesh->mNormals[it / 3].z;
        }
    }


    Geometry::_isIndexed = true;
    //Mesh::MakeUnique();
    //Mesh::_isShifted = true;

    return true;
}

bool Core::Geometry::Create(const std::string& linkToFBX,
    const bool initIndices,
    const bool initVertex,
    const bool initNormals,
    const bool initTexCoord,
    const bool initMaterial)
{
    Geometry::_vertex->clear();
    Geometry::_indices->clear();
    Geometry::_normals->clear();

    Assimp::Importer importer;
    const std::string path = std::filesystem::current_path().string() + linkToFBX;

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

    //Mesh::_isShifted = true;

    return true;
}