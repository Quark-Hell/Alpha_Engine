#include "MeshCollider.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Core/Components/Geometry.h"

namespace AxisEngine {
    MeshCollider::MeshCollider() {

    }
    MeshCollider::MeshCollider(const std::string& linkToFBX) {
        MeshCollider::Create(linkToFBX);
    }

    bool MeshCollider::Create(const std::string& linkToFBX) {
        Assimp::Importer importer;
        std::string path = std::filesystem::current_path().string() + linkToFBX.c_str();

        //TODO: Check if fbx
        const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
        aiMesh* mesh = s->mMeshes[0];

        Core::Geometry::_vertices->resize(mesh->mNumVertices * 3);

        for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {
            if (mesh->HasPositions()) {
                (*Core::Geometry::_vertices)[it] = mesh->mVertices[it / 3].x;
                (*Core::Geometry::_vertices)[it + 1] = mesh->mVertices[it / 3].y;
                (*Core::Geometry::_vertices)[it + 2] = mesh->mVertices[it / 3].z;
            }
        }

        Core::Geometry::_normals->clear();

        Core::Geometry::_isIndexed = true;
        Core::Geometry::MakeUnique();

        return true;
    }

    bool MeshCollider::Create() {
        if (GetParentObject() == nullptr)
            return false;

        Core::Geometry* geometry = GetParentObject()->GetComponentByType<Core::Geometry>();
        if (geometry == nullptr)
            return false;

        _vertices = geometry->GetVertices();

        //MeshCollider::_isIndexed = true;
        Core::Geometry::MakeUnique();

        return true;
    }
}