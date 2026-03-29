#include "Core/Resources/Geometry.h"
#include "Core/Objects/GameObject.h"
#include "Core/Factory.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <filesystem>
#include <unordered_set>
#include <array>
#include <limits.h>

namespace Core {
    void Geometry::LoadMesh(const std::string& linkToFBX, GeometryLoadSettings loadSettings)
    {
        Core::Logger::LogInfo("Mesh load process started");

        _loadSettings = loadSettings;

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

        if (HasFlag(GeometryLoadSettings::InitIndices, _loadSettings)) {
            meshFile = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
            if (meshFile == nullptr) {
                Core::Logger::LogError("Failed to load Mesh from", path, ":" + __LOGERROR__);
                return;
            }
            mesh = meshFile->mMeshes[0];

            // Загружаем индексы
            Geometry::Indices->resize(mesh->mNumFaces * 3);
            for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
                for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++) {
                    (*Geometry::Indices)[(it * 3) + jt] = mesh->mFaces[it].mIndices[jt];
                }
            }
        }
        else {
            meshFile = importer.ReadFile(path, aiProcess_Triangulate);
            if (meshFile == nullptr) {
                Core::Logger::LogError("Failed to load Mesh from", path, ":" + __LOGERROR__);
                return;
            }
            mesh = meshFile->mMeshes[0];
        }

        if (mesh->HasPositions() && HasFlag(GeometryLoadSettings::InitVertex, _loadSettings)) {
            if (HasFlag(GeometryLoadSettings::InitIndices, _loadSettings)) {
                Geometry::Vertices->resize(mesh->mNumVertices * 3);
                for (std::uint32_t i = 0; i < mesh->mNumVertices; ++i) {
                    const aiVector3D& v = mesh->mVertices[i];
                    (*Geometry::Vertices)[i * 3 + 0] = v.x;
                    (*Geometry::Vertices)[i * 3 + 1] = v.y;
                    (*Geometry::Vertices)[i * 3 + 2] = v.z;
                }
            }
            else {
                if (mesh->HasFaces()) {
                    Geometry::Vertices->clear();
                    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
                        const aiFace& face = mesh->mFaces[i];
                        if (face.mNumIndices == 3) {
                            for (unsigned int j = 0; j < 3; ++j) {
                                unsigned int index = face.mIndices[j];
                                const aiVector3D& v = mesh->mVertices[index];
                                Geometry::Vertices->emplace_back(v.x);
                                Geometry::Vertices->emplace_back(v.y);
                                Geometry::Vertices->emplace_back(v.z);
                            }
                        }
                    }
                }
                else {
                    Geometry::Vertices->resize(mesh->mNumVertices * 3);
                    for (std::uint32_t i = 0; i < mesh->mNumVertices; ++i) {
                        const aiVector3D& v = mesh->mVertices[i];
                        (*Geometry::Vertices)[i * 3 + 0] = v.x;
                        (*Geometry::Vertices)[i * 3 + 1] = v.y;
                        (*Geometry::Vertices)[i * 3 + 2] = v.z;
                    }
                }
            }
        }


        if (mesh->HasNormals() && HasFlag(GeometryLoadSettings::InitNormals, _loadSettings)) {
            Geometry::Normals->resize(Geometry::Vertices->size());

            for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

                (*Geometry::Normals)[it] = mesh->mNormals[it / 3].x;
                (*Geometry::Normals)[it + 1] = mesh->mNormals[it / 3].y;
                (*Geometry::Normals)[it + 2] = mesh->mNormals[it / 3].z;
            }
        }


        if (mesh->HasTextureCoords(0) && HasFlag(GeometryLoadSettings::InitTexCoord, _loadSettings)) {
            Geometry::TexCoords->resize((Geometry::Vertices->size() / 3) * 2);

            for (std::uint32_t it = 0; it < Geometry::TexCoords->size(); it += 2) {
                (*Geometry::TexCoords)[it]     = mesh->mTextureCoords[0][it / 2].x;
                (*Geometry::TexCoords)[it + 1] = mesh->mTextureCoords[0][it / 2].y;
            }
        }

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

    std::pair<std::vector<unsigned int>, unsigned int> Geometry::GetUniqueIndices(const Geometry& geometry) {
        Core::ScopedTimer timer{ "Uniq" };

        constexpr size_t arr_len = 3;
        std::array<float, arr_len> buffer;

        std::vector<unsigned int> relations;
        relations.reserve(geometry.Vertices->size() / 3);
        unsigned int nextIndex = 0;

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

        std::unordered_map<std::array<float, arr_len>, unsigned int, Vec3Hash, Vec3Equal> uniqueMap;
        uniqueMap.reserve(geometry.Vertices->size() / 3);

        for (size_t i = 0; i < geometry.Vertices->size(); i += 3) {
            buffer[0] = (*geometry.Vertices)[i];
            buffer[1] = (*geometry.Vertices)[i + 1];
            buffer[2] = (*geometry.Vertices)[i + 2];

            auto [it, inserted] = uniqueMap.emplace(buffer, nextIndex);
            if (inserted) {
                relations.emplace_back(nextIndex);
                nextIndex++;
            }
            else {
                relations.emplace_back(it->second);
            }
        }

        return { relations, nextIndex };
    }

    const std::vector<float>& Geometry::GetVertices() const noexcept {
        return *Vertices.get();
    }

    std::optional<std::vector<Geometry*>> Geometry::SeparateByLooseParts(const Geometry& geometry) {
        std::vector<unsigned int>& indices = *geometry.Indices.get();
        std::vector<float>& vertices = *geometry.Vertices.get();
        std::vector<float>& normals = *geometry.Normals.get();

        std::vector<float>& verticesColors = *geometry.VertexColors.get();
        std::vector<float>& texCoords = *geometry.TexCoords.get();

        if (vertices.size() == 0) {
            Core::Logger::LogError("Geometry doesn't have vertices");
            return {};
        }

        if (HasFlag(GeometryLoadSettings::InitIndices,geometry._loadSettings)) {
            //TODO: this information could be restore if use indices from assimp?
            Core::Logger::LogError("Geometry doesn't have enough information for separating");
        }

        auto ind = Geometry::GetUniqueIndices(geometry);

        Core::ScopedTimer timer{ "Separate" };

        if (ind.first.size() % 3 != 0) {
            //TODO: maybe this information could be restored if use indices from assimp?
            Core::Logger::LogError("Geometry doesn't have enough information for separating");
        }

        //Creating buffers
        std::vector<unsigned int> geometryIndices; //complete mesh
        geometryIndices.reserve(ind.first.size());

        std::vector<unsigned int> buffer;
        buffer = ind.first;

        std::vector<bool> relations;
        relations.resize(ind.second);

        //used as free value of buffer
        constexpr unsigned int max = std::numeric_limits<unsigned int>::max();

        std::vector<Geometry*> result;

        while (true)
        {
            //copying first triangle
            {
                int start = -1;
                for (int i = 0; i < buffer.size(); i++) {
                    if (buffer[i] != max) {
                        start = i;
                        break;
                    }
                }

                if (start == -1) {
                    break;
                }
                else
                {
                    //clear buffers
                    geometryIndices.clear();
                    std::fill(relations.begin(), relations.end(), false);
                }

                geometryIndices.emplace_back(buffer[start]);
                geometryIndices.emplace_back(buffer[start + 1]);
                geometryIndices.emplace_back(buffer[start + 2]);


                relations[buffer[start]] = true;
                relations[buffer[start + 1]] = true;
                relations[buffer[start + 2]] = true;


                buffer[start] = max;
                buffer[start + 1] = max;
                buffer[start + 2] = max;

            }

            for (unsigned int i = 0; i < buffer.size(); i+=3) {
                unsigned int first  = buffer[i];
                unsigned int second = buffer[i + 1];
                unsigned int third  = buffer[i + 2];

                //check if triangle exist
                if (first == max || second == max || third == max) {
                    continue;
                }

                //find relations
                if (relations[first] || relations[second] || relations[third]) {
                    geometryIndices.emplace_back(first);
                    geometryIndices.emplace_back(second);
                    geometryIndices.emplace_back(third);


                    relations[buffer[i]] = true;
                    relations[buffer[i + 1]] = true;
                    relations[buffer[i + 2]] = true;


                    buffer[i] = max;
                    buffer[i + 1] = max;
                    buffer[i + 2] = max;

                    //we finding relatins, so we should run cycle again
                    i = 0;
                }
            }

            auto& gem = *result.emplace_back(&Core::Factory::CreateResource<Geometry>());

            //fill geometry
            for (auto ind : geometryIndices) {
                {
                    auto pointX = vertices[ind];
                    auto pointY = vertices[ind + 1];
                    auto pointZ = vertices[ind + 2];

                    gem.Vertices->emplace_back(pointX);
                    gem.Vertices->emplace_back(pointY);
                    gem.Vertices->emplace_back(pointZ);
                }

                if (indices.size() != 0) {
                    //TODO
                }

                if (normals.size() != 0) {
                    auto normalX = normals[ind];
                    auto normalY = normals[ind + 1];
                    auto normalZ = normals[ind + 2];

                    gem.Normals->emplace_back(normalX);
                    gem.Normals->emplace_back(normalY);
                    gem.Normals->emplace_back(normalZ);
                }

                if (verticesColors.size() != 0) {
                    auto pointX = verticesColors[ind];
                    auto pointY = verticesColors[ind + 1];
                    auto pointZ = verticesColors[ind + 2];

                    gem.VertexColors->emplace_back(pointX);
                    gem.VertexColors->emplace_back(pointY);
                    gem.VertexColors->emplace_back(pointZ);
                }

                if (texCoords.size() != 0)
                {
                    auto texX = texCoords[ind];
                    auto texY = texCoords[ind + 1];
                    auto texZ = texCoords[ind + 2];

                    gem.TexCoords->emplace_back(texX);
                    gem.TexCoords->emplace_back(texY);
                    gem.TexCoords->emplace_back(texZ);
                }
            }
        } 

        return result;
    }
}