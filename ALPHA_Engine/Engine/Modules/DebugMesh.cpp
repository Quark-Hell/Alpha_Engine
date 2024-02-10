#include "Modules/DebugMesh.h"
#include "World.h"

DebugMesh::DebugMesh()
{
}

DebugMesh::~DebugMesh()
{
}

ModulesList DebugMesh::GetType()
{
	return DebugMeshType;
}

bool DebugMesh::Create(std::string linkToFBX)
{
    if (DebugMesh::_vertexCount != 0) {
        free(DebugMesh::_vertex);
        DebugMesh::_vertexCount = 0;
    }

    DebugMesh::_indices->clear();

    Assimp::Importer importer;
    std::string path = std::filesystem::current_path().string() + linkToFBX.c_str();

    //TODO: Check if fbx
    const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
    aiMesh* mesh = s->mMeshes[0];

    DebugMesh::_indices->reserve(mesh->mNumFaces * 3);

    for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
        for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
        {
            DebugMesh::_indices->push_back(mesh->mFaces[it].mIndices[jt]);
        }
    }

    if (mesh->HasPositions()) {
        DebugMesh::_vertexCount = mesh->mNumVertices;
        DebugMesh::_vertex = new float[DebugMesh::_vertexCount * 3];

        for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

            DebugMesh::_vertex[it] = mesh->mVertices[it / 3].x;
            DebugMesh::_vertex[it + 1] = mesh->mVertices[it / 3].y;
            DebugMesh::_vertex[it + 2] = mesh->mVertices[it / 3].z;
        }
    }

    DebugMesh::BindMesh();

    DebugMesh::_material->InitShader("\\Shaders\\BaseVertexShaders\\WireframeVertexShader.txt", ShadersType::VertexShader);
    DebugMesh::_material->InitShader("\\Shaders\\BaseFragmentShaders\\WireframeFragmentShader.txt", ShadersType::FragmentShader);

    return true;
}

bool DebugMesh::Create(Geometry& geometry)
{
    _indices = geometry._indices;

    _vertexCount = geometry._vertexCount;
    _vertex = new float[geometry._vertexCount * 3];

    for (std::uint32_t it = 0; it < geometry._vertexCount * 3; it++)
    {
        _vertex[it] = geometry._vertex[it];
    }

    BindMesh();

    _material->InitShader("\\Shaders\\BaseVertexShaders\\WireframeVertexShader.txt", ShadersType::VertexShader);
    _material->InitShader("\\Shaders\\BaseFragmentShaders\\WireframeFragmentShader.txt", ShadersType::FragmentShader);

    return true;
}

bool DebugMesh::BindMesh()
{
    if (DebugMesh::_vertexVbo != 0)
        glDeleteBuffers(1, &_vertexVbo);

    if (DebugMesh::_vao != 0)
        glDeleteBuffers(1, &_vao);


    glGenVertexArrays(1, &_vao);
    glBindVertexArray(DebugMesh::_vao);


    if (DebugMesh::_vertex != nullptr) {
        glGenBuffers(1, &_vertexVbo);
        glBindBuffer(GL_ARRAY_BUFFER, DebugMesh::_vertexVbo);
        glBufferData(GL_ARRAY_BUFFER, DebugMesh::_vertexCount * 3 * sizeof(float), DebugMesh::_vertex, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, DebugMesh::_vertexVbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        return false;
    }

    return true;
}

void DebugMesh::ApplyMeshSettings(std::shared_ptr<Camera> camera)
{
    glm::mat4x4 viewMat = camera->GetProjectionMatrix() * camera->GetTransformMatrix();
    DebugMesh::_material->_shader->SetValue(ShadersType::VertexShader, "view_projection_matrix", &(viewMat));
    
    DebugMesh::_material->_shader->SetValue(ShadersType::VertexShader, "model_matrix", &_transformMatrix);
    
    //DebugMesh::_material->_shader->SetValue(ShadersType::VertexShader, "color", &World::DebugWireframeColor);
}
