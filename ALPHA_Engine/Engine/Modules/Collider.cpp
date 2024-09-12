#include "Collider.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Object.h"
#include "World.h"

Collider::Collider()
{
    bool isHave = false;
    for (size_t i = 0; i < World::CollidersOnScene.size(); i++) {
        if (this == World::CollidersOnScene[i]) {
            isHave = true;
        }
    }

    if (isHave == true)
        return;

    World::CollidersOnScene.push_back(this);


}

Collider::~Collider()
{
    for (size_t i = 0; i < World::CollidersOnScene.size(); i++) {
        if (this == World::CollidersOnScene[i]) {
            World::CollidersOnScene.erase(World::CollidersOnScene.begin() + i);
            return;
        }
    }
}

ModulesList Collider::GetType() {
    return ModulesList::GeometryType;
}

void Collider::InitCollider(bool isExpand) {

}

void Collider::ApplyTransformation() {
    if (Collider::GetParentObject() != nullptr) {
        Collider::_transformMatrix = Collider::GetParentObject()->GetTransformationMatrix() * Collider::_transformMatrix;
    }

#ifdef _DEBUG
    //Collider::ApplyTransformationToDebugShell();
#endif

    Collider::_transformMatrix = glm::mat4x4(1.0f);
}

#ifdef _DEBUG
//void Collider::CreateDebugShell(const aiScene& scene) {
//    //TODO: Check if fbx
//    Collider::_debugVertex.clear();
//    Collider::_debugIndices.clear();
//
//    aiMesh* mesh = scene.mMeshes[0];
//
//    Collider::_debugIndices.reserve(mesh->mNumFaces * 3);
//
//    for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
//        for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
//        {
//            Collider::_debugIndices.push_back(mesh->mFaces[it].mIndices[jt]);
//        }
//    }
//
//    Collider::_debugVertex.reserve(mesh->mNumVertices * 3);
//
//    for (std::uint32_t it = 0; it < mesh->mNumVertices; it++) {
//        if (mesh->HasPositions()) {
//            Collider::_debugVertex.push_back(mesh->mVertices[it].x);
//            Collider::_debugVertex.push_back(mesh->mVertices[it].y);
//            Collider::_debugVertex.push_back(mesh->mVertices[it].z);
//        }
//    }
//}
#endif