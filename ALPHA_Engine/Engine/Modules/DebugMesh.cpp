#include "Modules/DebugMesh.h"
#include "World.h"

#include "ShadersProgram/ColliderWireframeShader.h"

DebugMesh::DebugMesh()
{
    DebugMesh::Name = "DebugMesh";

    DebugMesh::_material->Shader = std::make_shared<ColliderWireframeShader>(DebugMesh::_material.get());
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
    DebugMesh::_vertex->clear();  
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
        Geometry::_vertex->resize(mesh->mNumVertices * 3);
    
        for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {
    
            (*DebugMesh::_vertex)[it] = mesh->mVertices[it / 3].x;
            (*DebugMesh::_vertex)[it + 1] = mesh->mVertices[it / 3].y;
            (*DebugMesh::_vertex)[it + 2] = mesh->mVertices[it / 3].z;
        }
    }
    
    if (DebugMesh::_indices->size() != 0) {
        DebugMesh::_isIndexed = true;
    }
    DebugMesh::BindMesh();

    return true;
}

bool DebugMesh::Create(Geometry& geometry, bool copyIndices)
{
    if(copyIndices)
        _indices = geometry._indices;
    _vertex = geometry._vertex;

    DebugMesh::_isIndexed = copyIndices;
    
    BindMesh();
    
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
        glBufferData(GL_ARRAY_BUFFER, DebugMesh::_vertex->size() * sizeof(float), DebugMesh::_vertex->data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, DebugMesh::_vertexVbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        return false;
    }

    return true;
}
