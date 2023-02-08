#include "Collision.h"

inline bool Collision::CreateCollision(std::string link) {
    Assimp::Importer importer;
    std::string path = std::filesystem::current_path().string() + link.c_str();

    //TODO: Check if fbx
    const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate);
    aiMesh* mesh = s->mMeshes[0];

    GeneralCollider->Points.clear();
    GeneralCollider->Normals.clear();

    for (std::uint32_t it = 0; it < mesh->mNumVertices; it++) {
        Vector3 point;
        Vector3 normal;

        if (mesh->HasPositions()) {
            point.X = mesh->mVertices[it].x;
            point.Y = mesh->mVertices[it].y;
            point.Z = mesh->mVertices[it].z;
        }

        if (mesh->HasNormals()) {
            normal.X = mesh->mNormals[it].x;
            normal.Y = mesh->mNormals[it].y;
            normal.Z = mesh->mNormals[it].z;
        }

        GeneralCollider->Points.push_back(point);
        GeneralCollider->Normals.push_back(normal);
    }

    return true;
}

inline bool Collision::CreateConvexFrom—oncave(std::string link) {

}