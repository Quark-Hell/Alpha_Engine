#include "MeshCollider.h"
#include "Object.h"

MeshCollider::MeshCollider(std::string linkToFBX) {
    MeshCollider::Create(linkToFBX);

#ifdef _DEBUG
    MeshCollider::_debugMesh->SetParentObject(*MeshCollider::ParentObject);
#endif
}
MeshCollider::MeshCollider() {
#ifdef _DEBUG
    MeshCollider::_debugMesh->SetParentObject(*MeshCollider::ParentObject);
#endif
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
    MeshCollider::_debugMesh->Create(linkToFBX);
#endif

    AABB::UpdateAABB(Geometry::_vertex, Geometry::_vertexCount);

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


    MeshCollider::_vertexCount = mesh->_vertexCount;
    MeshCollider::_vertex = new float[MeshCollider::_vertexCount * 3];
    
    for (std::uint32_t it = 0; it < mesh->_vertexCount * 3; it++)
    {
        MeshCollider::_vertex[it] = mesh->_vertex[it];
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

void MeshCollider::AddPosition(float X, float Y, float Z) {
    Geometry::AddPosition(X, Y, Z);
#ifdef _DEBUG
    MeshCollider::_debugMesh->AddPosition(X, Y, Z);
#endif
}

void MeshCollider::AddPosition(Vector3 position) {
    Geometry::AddPosition(position);
#ifdef _DEBUG
    MeshCollider::_debugMesh->AddPosition(position);
#endif
}
void MeshCollider::SetPosition(float X, float Y, float Z) {
    Geometry::SetPosition(X, Y, Z);
#ifdef _DEBUG
    MeshCollider::_debugMesh->SetPosition(X, Y, Z);
#endif
}
void MeshCollider::SetPosition(Vector3 position) {
    Geometry::SetPosition(position);
#ifdef _DEBUG
    MeshCollider::_debugMesh->SetPosition(position);
#endif
}

void MeshCollider::AddOriginPosition(float X, float Y, float Z) {
    Geometry::AddOriginPosition(X, Y, Z);
#ifdef _DEBUG
    MeshCollider::_debugMesh->AddOriginPosition(X, Y, Z);
#endif
}
void MeshCollider::AddOriginPosition(Vector3 position) {
    Geometry::AddOriginPosition(position);
#ifdef _DEBUG
    MeshCollider::_debugMesh->AddOriginPosition(position);
#endif
}

void MeshCollider::SetOriginPosition(float X, float Y, float Z) {
    Geometry::SetOriginPosition(X, Y, Z);
#ifdef _DEBUG
    MeshCollider::_debugMesh->SetOriginPosition(X, Y, Z);
#endif
}
void MeshCollider::SetOriginPosition(Vector3 position) {
    Geometry::SetOriginPosition(position);
#ifdef _DEBUG
    MeshCollider::_debugMesh->SetOriginPosition(position);
#endif
}


void MeshCollider::AddRotation(float X, float Y, float Z) {
    Geometry::AddRotation(X, Y, Z);
#ifdef _DEBUG
    MeshCollider::_debugMesh->AddRotation(X, Y, Z);
#endif
}
void MeshCollider::AddRotation(Vector3 rotation) {
    Geometry::AddRotation(rotation);
#ifdef _DEBUG
    MeshCollider::_debugMesh->AddRotation(rotation);
#endif
}

void MeshCollider::SetRotation(float X, float Y, float Z) {
    Geometry::SetRotation(X, Y, Z);
#ifdef _DEBUG
    MeshCollider::_debugMesh->SetRotation(X, Y, Z);
#endif
}
void MeshCollider::SetRotation(Vector3 rotation) {
    Geometry::SetRotation(rotation);
#ifdef _DEBUG
    MeshCollider::_debugMesh->SetRotation(rotation);
#endif
}


void MeshCollider::SetScale(float X, float Y, float Z) {
    Geometry::SetScale(X, Y, Z);
#ifdef _DEBUG
    MeshCollider::_debugMesh->SetScale(X, Y, Z);
#endif
}
void MeshCollider::SetScale(Vector3 scale) {
    Geometry::SetScale(scale);
#ifdef _DEBUG
    MeshCollider::_debugMesh->SetScale(scale);
#endif
}


void MeshCollider::ApplyTransformation() {
    if (MeshCollider::GetParentObject() != nullptr) {

        MeshCollider::_transformMatrix = MeshCollider::GetParentObject()->GetTransformationMatrix() * MeshCollider::_transformMatrix;
    }
    else
    {
        return;
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
    MeshCollider::_debugMesh->ApplyTransformation();
#endif

    AABB::UpdateAABB(MeshCollider::_vertex, MeshCollider::_vertexCount);
    MeshCollider::_transformMatrix = glm::mat4x4(1.0f);
}

void MeshCollider::ModuleAdded()
{
    Geometry::ModuleAdded();
    MeshCollider::Create();

#ifdef _DEBUG
    MeshCollider::_debugMesh->SetParentObject(*MeshCollider::ParentObject);
    MeshCollider::_debugMesh->ModuleAdded();
#endif

    Geometry::_isShifted = true;
    //TODO: Add copy origin
    //Geometry::_origin = ParentObject->geto();
}


ModulesList MeshCollider::GetType() {
    return ModulesList::MeshColliderType;
}
