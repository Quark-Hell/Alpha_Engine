#include "MeshCollider.h"
#include "Object.h"

MeshCollider::MeshCollider(std::string linkToFBX) {
    MeshCollider::Create(linkToFBX);

#ifdef _DEBUG
    MeshCollider::DebugMesh->SetParentObject(*MeshCollider::ParentObject);
#endif
}
MeshCollider::MeshCollider() {
#ifdef _DEBUG
    MeshCollider::DebugMesh->SetParentObject(*MeshCollider::ParentObject);
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
    MeshCollider::CreateDebugShell(*s);
#endif

    AABB::UpdateAABB(Geometry::_vertex, Geometry::_vertexCount);

    Geometry::_isIndexed = true;
    Geometry::MakeUnique();
    //Mesh::_isShifted = true;

    return true;
}

#ifdef _DEBUG
void MeshCollider::CreateDebugShell(const aiScene& scene) {
    //TODO: Check if fbx
    if (MeshCollider::DebugMesh->_vertexCount != 0) {
        free(MeshCollider::DebugMesh->_vertex);
        MeshCollider::DebugMesh->_vertexCount = 0;
    }

    MeshCollider::DebugMesh->_indices->clear();

    aiMesh* mesh = scene.mMeshes[0];

    MeshCollider::DebugMesh->_indices->reserve(mesh->mNumFaces * 3);

    for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
        for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
        {
            MeshCollider::DebugMesh->_indices->push_back(mesh->mFaces[it].mIndices[jt]);
        }
    }

    if (mesh->HasPositions()) {
        MeshCollider::DebugMesh->_vertexCount = mesh->mNumVertices;
        MeshCollider::DebugMesh->_vertex = new float[MeshCollider::DebugMesh->_vertexCount * 3];

        for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

            MeshCollider::DebugMesh->_vertex[it] = mesh->mVertices[it / 3].x;
            MeshCollider::DebugMesh->_vertex[it + 1] = mesh->mVertices[it / 3].y;
            MeshCollider::DebugMesh->_vertex[it + 2] = mesh->mVertices[it / 3].z;
        }
    }

    MeshCollider::DebugMesh->BindMesh();
}

void MeshCollider::BindDebugMesh()
{
    if (MeshCollider::DebugMesh->_vertexVbo != 0)
        glDeleteBuffers(1, &MeshCollider::DebugMesh->_vertexVbo);

    if (MeshCollider::DebugMesh->_colorsVbo != 0)
        glDeleteBuffers(1, &MeshCollider::DebugMesh->_colorsVbo);

    if (MeshCollider::DebugMesh->_vao != 0)
        glDeleteBuffers(1, &MeshCollider::DebugMesh->_vao);



    glGenVertexArrays(1, &MeshCollider::DebugMesh->_vao);
    glBindVertexArray(MeshCollider::DebugMesh->_vao);



    if (MeshCollider::_vertex != nullptr) {
        glGenBuffers(1, &MeshCollider::DebugMesh->_vertexVbo);
        glBindBuffer(GL_ARRAY_BUFFER, DebugMesh->_vertexVbo);
        glBufferData(GL_ARRAY_BUFFER, MeshCollider::DebugMesh->_vertexCount * 3 * sizeof(float), MeshCollider::DebugMesh->_vertex, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, DebugMesh->_vertexVbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    if (MeshCollider::DebugMesh->_vertexColors->data() != nullptr) {
        glGenBuffers(1, &MeshCollider::DebugMesh->_colorsVbo);
        glBindBuffer(GL_ARRAY_BUFFER, MeshCollider::DebugMesh->_colorsVbo);
        glBufferData(GL_ARRAY_BUFFER, MeshCollider::DebugMesh->_vertexColors->size() * sizeof(float), MeshCollider::DebugMesh->_vertexColors->data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, MeshCollider::DebugMesh->_colorsVbo);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }
}
#endif

void MeshCollider::AddPosition(float X, float Y, float Z) {
    Geometry::AddPosition(X, Y, Z);
    MeshCollider::DebugMesh->AddPosition(X, Y, Z);
}

void MeshCollider::AddPosition(Vector3 position) {
    Geometry::AddPosition(position);
    MeshCollider::DebugMesh->AddPosition(position);
}
void MeshCollider::SetPosition(float X, float Y, float Z) {
    Geometry::SetPosition(X, Y, Z);
    MeshCollider::DebugMesh->SetPosition(X, Y, Z);
}
void MeshCollider::SetPosition(Vector3 position) {
    Geometry::SetPosition(position);
    MeshCollider::DebugMesh->SetPosition(position);
}

void MeshCollider::AddOriginPosition(float X, float Y, float Z) {
    Geometry::AddOriginPosition(X, Y, Z);
    MeshCollider::DebugMesh->AddOriginPosition(X, Y, Z);
}
void MeshCollider::AddOriginPosition(Vector3 position) {
    Geometry::AddOriginPosition(position);
    MeshCollider::DebugMesh->AddOriginPosition(position);
}

void MeshCollider::SetOriginPosition(float X, float Y, float Z) {
    Geometry::SetOriginPosition(X, Y, Z);
    MeshCollider::DebugMesh->SetOriginPosition(X, Y, Z);
}
void MeshCollider::SetOriginPosition(Vector3 position) {
    Geometry::SetOriginPosition(position);
    MeshCollider::DebugMesh->SetOriginPosition(position);
}


void MeshCollider::AddRotation(float X, float Y, float Z) {
    Geometry::AddRotation(X, Y, Z);
    MeshCollider::DebugMesh->AddRotation(X, Y, Z);
}
void MeshCollider::AddRotation(Vector3 rotation) {
    Geometry::AddRotation(rotation);
    MeshCollider::DebugMesh->AddRotation(rotation);
}

void MeshCollider::SetRotation(float X, float Y, float Z) {
    Geometry::SetRotation(X, Y, Z);
    MeshCollider::DebugMesh->SetRotation(X, Y, Z);
}
void MeshCollider::SetRotation(Vector3 rotation) {
    Geometry::SetRotation(rotation);
    MeshCollider::DebugMesh->SetRotation(rotation);
}


void MeshCollider::SetScale(float X, float Y, float Z) {
    Geometry::SetScale(X, Y, Z);
    MeshCollider::DebugMesh->SetScale(X, Y, Z);
}
void MeshCollider::SetScale(Vector3 scale) {
    Geometry::SetScale(scale);
    MeshCollider::DebugMesh->SetScale(scale);
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
    MeshCollider::DebugMesh->ApplyTransformation();
#endif

    AABB::UpdateAABB(MeshCollider::_vertex, MeshCollider::_vertexCount);
    MeshCollider::_transformMatrix = glm::mat4x4(1.0f);
}

void MeshCollider::ModuleAdded()
{
    Geometry::ModuleAdded();

#ifdef _DEBUG
    MeshCollider::DebugMesh->SetParentObject(*MeshCollider::ParentObject);
    MeshCollider::DebugMesh->ModuleAdded();
#endif

    //TODO: Add copy origin
    //Geometry::_origin = ParentObject->geto();
}


ModulesList MeshCollider::GetType() {
    return ModulesList::MeshColliderType;
}
