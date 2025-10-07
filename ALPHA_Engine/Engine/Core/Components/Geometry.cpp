#include "Core/Components/Geometry.h"
#include "Core/Objects/GameObject.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <filesystem>
#include <unordered_set>
#include <array>

namespace Core {
    Geometry::Geometry() {

    }
    Geometry::~Geometry() {

    }

    bool Geometry::Create() {
        return true;
    }

    bool Geometry::Create(const std::string& linkToFBX,
        const bool initIndices,
        const bool initVertex,
        const bool initNormals,
        const bool initTexCoord)
    {
        _vertices->clear();
        _indices->clear();
        _normals->clear();

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
            Geometry::_vertices->resize(mesh->mNumVertices * 3);
            for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

                (*Geometry::_vertices)[it] = mesh->mVertices[it / 3].x;
                (*Geometry::_vertices)[it + 1] = mesh->mVertices[it / 3].y;
                (*Geometry::_vertices)[it + 2] = mesh->mVertices[it / 3].z;
            }
        }


        if (mesh->HasNormals() && initNormals) {
            Geometry::_normals->resize(Geometry::_vertices->size());

            for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

                (*Geometry::_normals)[it] = mesh->mNormals[it / 3].x;
                (*Geometry::_normals)[it + 1] = mesh->mNormals[it / 3].y;
                (*Geometry::_normals)[it + 2] = mesh->mNormals[it / 3].z;
            }
        }

        return true;
    }

    glm::vec3 Geometry::FindFurthestPoint(glm::vec3 direction) const {
        glm::vec3 maxPoint{ 0.0f };
        float maxDistance = -FLT_MAX;

        for (size_t i = 0; i + 2 < _vertices->size(); i += 3) {
            glm::vec3 vertex{ (*_vertices)[i], (*_vertices)[i + 1], (*_vertices)[i + 2] };

            float distance = glm::dot(vertex, direction);
            if (distance > maxDistance) {
                maxDistance = distance;
                maxPoint = vertex;
            }
        }

        return maxPoint;
    }

    void Geometry::MakeUnique() {
        constexpr size_t arr_len = 3;
        std::array<float, arr_len> buffer;

        struct Vec3Hash {
            std::size_t operator()(const std::array<float, arr_len>& v) const noexcept {
                std::size_t h1 = std::hash<float>{}(v[0]);
                std::size_t h2 = std::hash<float>{}(v[1]);
                std::size_t h3 = std::hash<float>{}(v[2]);
                // Combine hashes
                return h1 ^ (h2 << 1) ^ (h3 << 2);
            }
        };

        struct Vec3Equal {
            bool operator()(const std::array<float, arr_len>& a, const std::array<float, arr_len>& b) const noexcept {
                return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
            }
        };

        std::unordered_set<std::array<float, arr_len>, Vec3Hash, Vec3Equal> uniqueSet;
        uniqueSet.reserve(Geometry::_vertices->size() / 3);

        for (size_t i = 0; i < Geometry::_vertices->size(); i += 3) {
            buffer[0] = (*Geometry::_vertices)[i];
            buffer[1] = (*Geometry::_vertices)[i + 1];
            buffer[2] = (*Geometry::_vertices)[i + 2];
            uniqueSet.insert(buffer);
        }

        Geometry::_vertices->clear();
        Geometry::_vertices->reserve(uniqueSet.size() * 3);

        for (const auto& v : uniqueSet) {
            Geometry::_vertices->push_back(v[0]);
            Geometry::_vertices->push_back(v[1]);
            Geometry::_vertices->push_back(v[2]);
        }

        Logger::Logger::LogInfo("Removed duplicate vertices. New count: " + std::to_string(uniqueSet.size()));
    }

    std::shared_ptr<std::vector<float>> Geometry::GetVertices() const noexcept {
        return _vertices;
    }
}