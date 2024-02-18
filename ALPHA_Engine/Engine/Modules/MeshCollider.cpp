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

    Geometry::_vertex->resize(mesh->mNumVertices * 3);

    for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {
        if (mesh->HasPositions()) {
            (*Geometry::_vertex)[it] = mesh->mVertices[it / 3].x;
            (*Geometry::_vertex)[it + 1] = mesh->mVertices[it / 3].y;
            (*Geometry::_vertex)[it + 2] = mesh->mVertices[it / 3].z;
        }
    }

    Geometry::_normals->clear();

#ifdef _DEBUG
    MeshCollider::_debugMesh->Create(linkToFBX);
#endif

    //AABB::UpdateAABB(Geometry::_vertex, Geometry::_vertexCount);

    Geometry::_isIndexed = true;
    Geometry::MakeUnique();
    Geometry::_isShifted = true;

    return true;
}

bool MeshCollider::Create()
{
    if (MeshCollider::ParentObject == nullptr)
        return false;

    Mesh* mesh = std::dynamic_pointer_cast<Mesh>(MeshCollider::ParentObject->GetModuleByType(MeshType)).get();
    if (mesh == nullptr)
        return false;

    Geometry::_vertex->resize(mesh->_vertex->size());
    
    for (std::uint32_t it = 0; it < mesh->_vertex->size(); it++)
    {
        (*MeshCollider::_vertex)[it] = (*mesh->_vertex)[it];
    }

#ifdef _DEBUG
    MeshCollider::_debugMesh->Create(*mesh);
#endif

    //AABB::UpdateAABB(Geometry::_vertex, Geometry::_vertexCount);

    //MeshCollider::_isIndexed = true;
    //Geometry::MakeUnique();
    Geometry::_isShifted = true;

    return true;
}

void MeshCollider::SetParentObject(const Object& parent)
{
    if (MeshCollider::ParentObject != nullptr) {
        Object* obj = const_cast<Object*>(&parent);
        MeshCollider::InitTransformatiom(*ParentObject, *obj);
    }

    MeshCollider::ParentObject = const_cast<Object*>(&parent);
#ifdef _DEBUG
    MeshCollider::_debugMesh->SetParentObject(*MeshCollider::ParentObject);
#endif
}

void MeshCollider::ApplyTransformation() {
    if (MeshCollider::GetParentObject() != nullptr) {

        MeshCollider::_transformMatrix = MeshCollider::GetParentObject()->GetTransformationMatrix() * MeshCollider::_transformMatrix;
    }

    for (size_t jt = 0; jt < MeshCollider::_vertex->size(); jt += 3)
    {
        glm::vec4 buf((*MeshCollider::_vertex)[jt], (*MeshCollider::_vertex)[jt + 1], (*MeshCollider::_vertex)[jt + 2], 1);

        glm::vec4 res;
        res = MeshCollider::_transformMatrix * buf;
        (*MeshCollider::_vertex)[jt + 0] = res.x;
        (*MeshCollider::_vertex)[jt + 1] = res.y;
        (*MeshCollider::_vertex)[jt + 2] = res.z;
    }

#ifdef _DEBUG
    MeshCollider::_debugMesh->ApplyTransformation();
#endif

    //AABB::UpdateAABB(MeshCollider::_vertex, MeshCollider::_vertexCount);
    MeshCollider::_transformMatrix = glm::mat4x4(1.0f);
}

void MeshCollider::InitTransformatiom(Object& newParent)
{
    Vector3 posDelta = newParent.GetPosition();
    Vector4 rotDelta = newParent.GetRotation();
    Vector3 scaleDelta = newParent.GetScale();

    glm::mat4x4 rotMat(1.0f);

    const float radX = M_PI / 180 * rotDelta.X;
    const float radY = M_PI / 180 * rotDelta.Y;
    const float radZ = M_PI / 180 * rotDelta.Z;

    rotMat = glm::rotate(rotMat, radX, glm::vec3(1.0f, 0.0f, 0.0f));
    rotMat = glm::rotate(rotMat, radY, glm::vec3(0.0f, 1.0f, 0.0f));
    rotMat = glm::rotate(rotMat, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4x4 transMat(1.0f);
    transMat = glm::translate(glm::vec3(
        posDelta.X,
        posDelta.Y,
        posDelta.Z));

    glm::mat4x4 scaleMat(1.0f);
    scaleMat = glm::scale(scaleMat, glm::vec3(
        scaleDelta.X,
        scaleDelta.Y,
        scaleDelta.Z));

    glm::mat4x4 deltaMat = rotMat * scaleMat;


    MeshCollider::_transformMatrix = deltaMat * MeshCollider::_transformMatrix;

    for (size_t jt = 0; jt < MeshCollider::_vertex->size(); jt += 3)
    {
        glm::vec4 buf((*MeshCollider::_vertex)[jt], (*MeshCollider::_vertex)[jt + 1], (*MeshCollider::_vertex)[jt + 2], 1);

        glm::vec4 res;
        res = MeshCollider::_transformMatrix * buf;
        (*MeshCollider::_vertex)[jt + 0] = res.x;
        (*MeshCollider::_vertex)[jt + 1] = res.y;
        (*MeshCollider::_vertex)[jt + 2] = res.z;
    }

    MeshCollider::_transformMatrix = glm::mat4x4(1.0f);
}

void MeshCollider::InitTransformatiom(Object& oldParent, Object& newParent)
{
    Vector3 posDelta = newParent.GetPosition() - oldParent.GetPosition();
    Vector4 rotDelta = newParent.GetRotation() - oldParent.GetRotation();
    Vector3 scaleDelta = newParent.GetScale() - oldParent.GetScale();

    glm::mat4x4 rotMat(1.0f);

    const float radX = M_PI / 180 * rotDelta.X;
    const float radY = M_PI / 180 * rotDelta.Y;
    const float radZ = M_PI / 180 * rotDelta.Z;

    rotMat = glm::rotate(rotMat, radX, glm::vec3(1.0f, 0.0f, 0.0f));
    rotMat = glm::rotate(rotMat, radY, glm::vec3(0.0f, 1.0f, 0.0f));
    rotMat = glm::rotate(rotMat, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4x4 transMat(1.0f);
    transMat = glm::translate(glm::vec3(
        posDelta.X,
        posDelta.Y,
        posDelta.Z));

    glm::mat4x4 scaleMat(1.0f);
    scaleMat = glm::scale(scaleMat, glm::vec3(
        scaleDelta.X,
        scaleDelta.Y,
        scaleDelta.Z));

    glm::mat4x4 deltaMat = transMat * rotMat * scaleMat;


    MeshCollider::_transformMatrix = deltaMat * MeshCollider::_transformMatrix;

    for (size_t jt = 0; jt < MeshCollider::_vertex->size(); jt += 3)
    {
        glm::vec4 buf((*MeshCollider::_vertex)[jt], (*MeshCollider::_vertex)[jt + 1], (*MeshCollider::_vertex)[jt + 2], 1);

        glm::vec4 res;
        res = MeshCollider::_transformMatrix * buf;
        (*MeshCollider::_vertex)[jt + 0] = res.x;
        (*MeshCollider::_vertex)[jt + 1] = res.y;
        (*MeshCollider::_vertex)[jt + 2] = res.z;
    }

    MeshCollider::_transformMatrix = glm::mat4x4(1.0f);
}

void MeshCollider::ModuleAdded()
{
    MeshCollider::Create();
    MeshCollider::InitTransformatiom(*ParentObject);

#ifdef _DEBUG
    MeshCollider::_debugMesh->SetParentObject(*MeshCollider::ParentObject);
#endif
}


ModulesList MeshCollider::GetType() {
    return ModulesList::MeshColliderType;
}
