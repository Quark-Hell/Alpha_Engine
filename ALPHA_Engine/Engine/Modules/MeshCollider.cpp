#include "MeshCollider.h"

MeshCollider::MeshCollider(std::string linkToFBX) {
    ColliderPresets::Create(linkToFBX);
}
MeshCollider::MeshCollider() {

}
MeshCollider::~MeshCollider() {

}

bool MeshCollider::CreateConvexFromConcave(std::string link) {
    return false;
}

//bool MeshCollider::Create(std::string linkToFBX) {
//    Assimp::Importer importer;
//    std::string path = std::filesystem::current_path().string() + linkToFBX.c_str();
//
//    //TODO: Check if fbx
//    const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
//    aiMesh* mesh = s->mMeshes[0];
//
//    Geometry::_indicesCount = mesh->mNumFaces * 3;
//    Geometry::_indices = new unsigned int[Geometry::_indicesCount];
//
//    for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
//        for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
//        {
//            Geometry::_indices[(it * 3) + jt] = mesh->mFaces[it].mIndices[jt];
//        }
//    }
//
//
//    Geometry::_vertexCount = mesh->mNumVertices;
//    Geometry::_vertex = new float[Geometry::_vertexCount * 3];
//
//    for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {
//        if (mesh->HasPositions()) {
//            Geometry::_vertex[it] = mesh->mVertices[it / 3].x;
//            Geometry::_vertex[it + 1] = mesh->mVertices[it / 3].y;
//            Geometry::_vertex[it + 2] = mesh->mVertices[it / 3].z;
//        }
//    }
//
//    Geometry::_normalsCount = 0;
//
//    Geometry::_isIndexed = true;
//    Geometry::MakeUnique();
//    //Mesh::_isShifted = true;
//
//    return true;
//}

ModulesList MeshCollider::GetType() {
    return ModulesList::MeshColliderType;
}
