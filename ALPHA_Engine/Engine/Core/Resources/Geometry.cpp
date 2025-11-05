#include "Core/Resources/Geometry.h"
#include "Core/Objects/GameObject.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <filesystem>
#include <unordered_set>
#include <array>

namespace Core {
    void Geometry::LoadMesh(const std::string& linkToFBX,
        bool initVertex,
        bool initIndices,
        bool initNormals,
        bool initVertexColors,
        bool initTexCoord)
    {
        Core::Logger::LogInfo("Mesh load process started");

        Vertices->clear();
        Indices->clear();
        Normals->clear();

        VertexColors->clear();
        TexCoords->clear();
        Core::Logger::LogInfo("Mesh data has been cleared");

        Assimp::Importer importer;
        const std::string path = std::filesystem::current_path().string() + linkToFBX;

        //TODO: Check if fbx
        const aiScene* meshFile;
        aiMesh* mesh;

        if (initIndices) {
            meshFile = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
            if (meshFile == nullptr) {
                Core::Logger::LogError("Failed to load Mesh from", path, ":" + __LOGERROR__);
                return;
            }

            mesh = meshFile->mMeshes[0];
            Geometry::Indices->resize(mesh->mNumFaces * 3);

            for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
                for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
                {
                    (*Geometry::Indices)[(it * 3) + jt] = mesh->mFaces[it].mIndices[jt];
                }
            }

            Geometry::IsIndexed = true;
        }
        else
        {
            meshFile = importer.ReadFile(path, aiProcess_Triangulate);
            if (meshFile == nullptr) {
                Core::Logger::LogError("Failed to load Mesh from", path, ":" + __LOGERROR__);
                return;
            }
            mesh = meshFile->mMeshes[0];

            Geometry::IsIndexed = false;
        }

        if (mesh->HasPositions() && initVertex) {
            Geometry::Vertices->resize(mesh->mNumVertices * 3);
            for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

                (*Geometry::Vertices)[it] = mesh->mVertices[it / 3].x;
                (*Geometry::Vertices)[it + 1] = mesh->mVertices[it / 3].y;
                (*Geometry::Vertices)[it + 2] = mesh->mVertices[it / 3].z;
            }
        }


        if (mesh->HasNormals() && initNormals) {
            Geometry::Normals->resize(Geometry::Vertices->size());

            for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

                (*Geometry::Normals)[it] = mesh->mNormals[it / 3].x;
                (*Geometry::Normals)[it + 1] = mesh->mNormals[it / 3].y;
                (*Geometry::Normals)[it + 2] = mesh->mNormals[it / 3].z;
            }
        }


        if (mesh->HasTextureCoords(0) && initTexCoord) {
            Geometry::TexCoords->resize((Geometry::Vertices->size() / 3) * 2);

            for (std::uint32_t it = 0; it < Geometry::TexCoords->size(); it += 2) {
                (*Geometry::TexCoords)[it]     = mesh->mTextureCoords[0][it / 2].x;
                (*Geometry::TexCoords)[it + 1] = mesh->mTextureCoords[0][it / 2].y;
            }
        }

        IsIndexed = initIndices;

        Core::Logger::LogInfo("Mesh has been loaded");

        return;
    }

    glm::vec3 Geometry::FindFurthestPoint(glm::vec3 direction) const {
        glm::vec3 maxPoint{ 0.0f };
        float maxDistance = -FLT_MAX;

        for (size_t i = 0; i + 2 < Vertices->size(); i += 3) {
            glm::vec3 vertex{ (*Vertices)[i], (*Vertices)[i + 1], (*Vertices)[i + 2] };

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
        uniqueSet.reserve(Geometry::Vertices->size() / 3);

        for (size_t i = 0; i < Geometry::Vertices->size(); i += 3) {
            buffer[0] = (*Geometry::Vertices)[i];
            buffer[1] = (*Geometry::Vertices)[i + 1];
            buffer[2] = (*Geometry::Vertices)[i + 2];
            uniqueSet.insert(buffer);
        }

        Geometry::Vertices->clear();
        Geometry::Vertices->reserve(uniqueSet.size() * 3);

        for (const auto& v : uniqueSet) {
            Geometry::Vertices->push_back(v[0]);
            Geometry::Vertices->push_back(v[1]);
            Geometry::Vertices->push_back(v[2]);
        }

        Logger::Logger::LogInfo("Removed duplicate vertices. New count: " + std::to_string(uniqueSet.size()));
    }

    const std::vector<float>& Geometry::GetVertices() const noexcept {
        return *Vertices.get();
    }
}