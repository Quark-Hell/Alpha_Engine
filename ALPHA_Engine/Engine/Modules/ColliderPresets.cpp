#include "ColliderPresets.h"
#include "Object.h"

ColliderPresets::ColliderPresets() {

}
ColliderPresets::~ColliderPresets() {

}

void ColliderPresets::InitCollider(bool isExpand) {

}

bool ColliderPresets::Create(std::string linkToFBX) {
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

    Geometry::_normalsCount = 0;

#ifdef _DEBUG
    ColliderPresets::_debugIndices.reserve(mesh->mNumFaces * 3);

    for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
        for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
        {
            ColliderPresets::_debugIndices.push_back(mesh->mFaces[it].mIndices[jt]);
        }
    }

    ColliderPresets::_debugVertex.reserve(mesh->mNumVertices * 3);

    for (std::uint32_t it = 0; it < mesh->mNumVertices; it++) {
        if (mesh->HasPositions()) {
            ColliderPresets::_debugVertex.push_back(mesh->mVertices[it].x);
            ColliderPresets::_debugVertex.push_back(mesh->mVertices[it].y);
            ColliderPresets::_debugVertex.push_back(mesh->mVertices[it].z);
        }
    }
#endif 

    Geometry::_isIndexed = true;
    Geometry::MakeUnique();
    //Mesh::_isShifted = true;

    return true;
}

void ColliderPresets::ApplyTransformation() {
    if (ColliderPresets::GetParentObject() != nullptr) {
        ColliderPresets::_transformMatrix = ColliderPresets::GetParentObject()->GetTransformationMatrix() * ColliderPresets::_transformMatrix;
    }

    Vector3 originShift = _origin - _position;

    for (size_t jt = 0; jt < ColliderPresets::_vertexCount * 3; jt += 3)
    {
        glm::vec4 buf(ColliderPresets::_vertex[jt], ColliderPresets::_vertex[jt + 1], ColliderPresets::_vertex[jt + 2], 1);
        glm::mat4 originMat = glm::translate(glm::vec3(-originShift.X, -originShift.Y, -originShift.Z));
        glm::mat4 oldOriginMat = glm::translate(glm::vec3(originShift.X, originShift.Y, originShift.Z));

        buf = originMat * buf;

        glm::vec4 res;
        res = ColliderPresets::_transformMatrix * buf;
        res = oldOriginMat * res;

        ColliderPresets::_vertex[jt + 0] = res.x;
        ColliderPresets::_vertex[jt + 1] = res.y;
        ColliderPresets::_vertex[jt + 2] = res.z;
    }

#ifdef _DEBUG
    for (size_t jt = 0; jt < _debugVertex.size(); jt += 3)
    {
        glm::vec4 buf(ColliderPresets::_debugVertex[jt], ColliderPresets::_debugVertex[jt + 1], ColliderPresets::_debugVertex[jt + 2], 1);
        glm::mat4 originMat = glm::translate(glm::vec3(-originShift.X, -originShift.Y, -originShift.Z));
        glm::mat4 oldOriginMat = glm::translate(glm::vec3(originShift.X, originShift.Y, originShift.Z));

        buf = originMat * buf;

        glm::vec4 res;
        res = ColliderPresets::_transformMatrix * buf;
        res = oldOriginMat * res;

        ColliderPresets::_debugVertex[jt + 0] = res.x;
        ColliderPresets::_debugVertex[jt + 1] = res.y;
        ColliderPresets::_debugVertex[jt + 2] = res.z;
    }
#endif

    ColliderPresets::_transformMatrix = glm::mat4x4(1.0f);
}