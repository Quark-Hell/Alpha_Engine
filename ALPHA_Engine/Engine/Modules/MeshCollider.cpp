#include "MeshCollider.h"
#include "Object.h"

MeshCollider::MeshCollider(std::string linkToFBX) {
    MeshCollider::Create(linkToFBX);
}
MeshCollider::MeshCollider() {

}
MeshCollider::~MeshCollider() {

}

bool MeshCollider::CreateConvexFromConcave(std::string link) {
    return false;
}

bool MeshCollider::Create(std::string linkToFBX) {
    Assimp::Importer importer;
    std::string path = std::filesystem::current_path().string() + linkToFBX.c_str();

    //TODO: Check if fbx
    const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
    aiMesh* mesh = s->mMeshes[0];

    Geometry::_vertexCount = mesh->mNumVertices;
    Geometry::_vertex = new float[Geometry::_vertexCount * 3];

    for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {
        if (mesh->HasPositions()) {
            Geometry::_vertex[it] = mesh->mVertices[it / 3].x;
            Geometry::_vertex[it + 1] = mesh->mVertices[it / 3].y;
            Geometry::_vertex[it + 2] = mesh->mVertices[it / 3].z;
        }
    }

    Geometry::_normals->clear();

#ifdef _DEBUG
    Collider::CreateDebugShell(*s);
#endif

    AABB::UpdateAABB(Geometry::_vertex, Geometry::_vertexCount);

    Geometry::_isIndexed = true;
    Geometry::MakeUnique();
    //Mesh::_isShifted = true;

    return true;
}

void MeshCollider::ApplyTransformation() {
    if (MeshCollider::GetParentObject() != nullptr) {
        MeshCollider::_transformMatrix = MeshCollider::GetParentObject()->GetTransformationMatrix() * MeshCollider::_transformMatrix;
    }

    for (size_t jt = 0; jt < MeshCollider::_vertexCount * 3; jt += 3)
    {
        glm::vec4 buf(MeshCollider::_vertex[jt], MeshCollider::_vertex[jt + 1], MeshCollider::_vertex[jt + 2], 1);

        glm::vec4 res;
        res = MeshCollider::_transformMatrix * buf;
        MeshCollider::_vertex[jt + 0] = res.x;
        MeshCollider::_vertex[jt + 1] = res.y;
        MeshCollider::_vertex[jt + 2] = res.z;
    }

#ifdef _DEBUG
    for (size_t jt = 0; jt < _debugVertex.size(); jt += 3)
    {
        glm::vec4 buf(Collider::_debugVertex[jt], Collider::_debugVertex[jt + 1], Collider::_debugVertex[jt + 2], 1);

        glm::vec4 res;
        res = MeshCollider::_transformMatrix * buf;
        Collider::_debugVertex[jt + 0] = res.x;
        Collider::_debugVertex[jt + 1] = res.y;
        Collider::_debugVertex[jt + 2] = res.z;
    }
#endif

    AABB::UpdateAABB(MeshCollider::_vertex, MeshCollider::_vertexCount);
    MeshCollider::_transformMatrix = glm::mat4x4(1.0f);
}


ModulesList MeshCollider::GetType() {
    return ModulesList::MeshColliderType;
}
