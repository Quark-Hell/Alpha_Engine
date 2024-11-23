#include "Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "../Binder.h"

#include "Core/Logger/Logger.h"

namespace AnomalyEngine {
    Mesh::Mesh() = default;
    Mesh::~Mesh() {
        //TODO: Delete mesh info from VRAM
    }

    bool Mesh::Create(
        const std::string &linkToFBX,
        const bool initIndices,
        const bool initVertex,
        const bool initNormals,
        const bool initTexCoord) {
        Core::Logger::Logger::LogInfo("Mesh load process started");

        _vertex->clear();
        _indices->clear();
        _normals->clear();
        _texCoords->clear();
        Core::Logger::Logger::LogInfo("Mesh data has been cleared");

        Assimp::Importer importer;
        const std::string path = std::filesystem::current_path().string() + linkToFBX;

        //TODO: Check if fbx
        const aiScene* s;
        aiMesh* mesh;

        if (initIndices) {
            s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
            if (s == nullptr) {
                Core::Logger::Logger::LogError("Failed to load Mesh from", path, ":" + __LOGERROR__);
                return false;
            }
            mesh = s->mMeshes[0];

            Geometry::_indices->resize(mesh->mNumFaces * 3);

            for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
                for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
                {
                    (*Geometry::_indices)[(it * 3) + jt] = mesh->mFaces[it].mIndices[jt];
                }
            }
        }
        else
        {
            s = importer.ReadFile(path, aiProcess_Triangulate);
            if (s == nullptr) {
                Core::Logger::Logger::LogError("Failed to load Mesh from", path, ":" + __LOGERROR__);
                return false;
            }
            mesh = s->mMeshes[0];
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

        _isIndexed = initIndices;
        Core::Logger::Logger::LogInfo("Mesh has been loaded");

        Binder::BindMesh(this);
        return true;
    }

    unsigned int Mesh::GetVertexVbo() const {
        return _vertexVbo;
    }
    unsigned int Mesh::GetColorsVbo() const {
        return _colorsVbo;
    }
    unsigned int Mesh::GetNormalsVbo() const {
        return _normalsVbo;
    }
    unsigned int Mesh::GetTexCoordsVbo() const {
        return _texCoordsVbo;
    }
}
