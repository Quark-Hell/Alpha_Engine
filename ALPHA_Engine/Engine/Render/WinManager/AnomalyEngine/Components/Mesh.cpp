#include "Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "../Binder.h"

#include "Logger/Logger.h"

namespace Render::AnomalyEngine::Components {
    Mesh::Mesh() = default;
    Mesh::~Mesh() {

    }

    bool Mesh::Create(const std::string &linkToFBX) {
        Logger::Logger::LogInfo("Mesh load process started");

        Mesh::_vertex->clear();
        Mesh::_indices->clear();
        Mesh::_normals->clear();
        Mesh::_texCoords->clear();
        Logger::Logger::LogInfo("Mesh data has been cleared");

        Assimp::Importer importer;
        const std::string path = std::filesystem::current_path().string() + linkToFBX;

        //TODO: Check if fbx
        const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
        if (s == nullptr) {
            Logger::Logger::LogError("Cannot read the file by path: : " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return false;
        }

        Logger::Logger::LogInfo("Read .fbx by ",path);
        const aiMesh* mesh = s->mMeshes[0];

        Mesh::_indices->resize(mesh->mNumFaces * 3);


        for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
            for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
            {
                (*Mesh::_indices)[(it * 3) + jt] = mesh->mFaces[it].mIndices[jt];
            }
        }

        if (mesh->HasPositions()) {
            Geometry::_vertex->resize(mesh->mNumVertices * 3);

            for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

                (*Geometry::_vertex)[it] = mesh->mVertices[it / 3].x;
                (*Geometry::_vertex)[it + 1] = mesh->mVertices[it / 3].y;
                (*Geometry::_vertex)[it + 2] = mesh->mVertices[it / 3].z;
            }
        }

        if (mesh->HasNormals()) {
            Mesh::_normals->resize(Geometry::_vertex->size());

            for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {
                (*Mesh::_normals)[it] = mesh->mNormals[it / 3].x;
                (*Mesh::_normals)[it + 1] = mesh->mNormals[it / 3].y;
                (*Mesh::_normals)[it + 2] = mesh->mNormals[it / 3].z;
            }
        }

        if (mesh->HasTextureCoords(0)) {
            Mesh::_texCoords->resize((Geometry::_vertex->size() / 3) * 2);

            for (std::uint32_t it = 0; it < Mesh::_texCoords->size(); it += 2) {
                (*Mesh::_texCoords)[it] = mesh->mTextureCoords[0][it / 2].x;
                (*Mesh::_texCoords)[it + 1] = mesh->mTextureCoords[0][it / 2].y;
            }
        }

        Mesh::_isIndexed = true;
        Logger::Logger::LogInfo("Mesh has been loaded");

        Binder::BindMesh(this);
        return true;
    }

    bool Mesh::Create(
        const std::string &linkToFBX,
        const bool initIndices,
        const bool initVertex,
        const bool initNormals,
        const bool initTexCoord,
        const bool initMaterial) {
        Logger::Logger::LogInfo("Mesh load process started");

        Mesh::_vertex->clear();
        Mesh::_indices->clear();
        Mesh::_normals->clear();
        Mesh::_texCoords->clear();
        Logger::Logger::LogInfo("Mesh data has been cleared");

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

        if (mesh->HasTextureCoords(0) && initTexCoord) {
            Mesh::_texCoords->resize((Geometry::_vertex->size() / 3) * 2);

            for (std::uint32_t it = 0; it < Mesh::_texCoords->size(); it += 2) {
                (*Mesh::_texCoords)[it] = mesh->mTextureCoords[0][it / 2].x;
                (*Mesh::_texCoords)[it + 1] = mesh->mTextureCoords[0][it / 2].y;
            }
        }

        Mesh::_isIndexed = true;
        Logger::Logger::LogInfo("Mesh has been loaded");

        Binder::BindMesh(this);
        return true;
    }
}
