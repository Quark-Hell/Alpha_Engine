#include "Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <GLEW/glew.h>
#include <GL/gl.h>

namespace AnomalyEngine::Render {
    Mesh::Mesh() {

    }
    Mesh::~Mesh() {

    }


    bool Mesh::Create(const std::string &linkToFBX) {
        std::cout << "Mesh load process started" << std::endl;

        Mesh::_vertex->clear();
        Mesh::_indices->clear();
        Mesh::_normals->clear();
        Mesh::_texCoords->clear();
        std::cout << "Mesh data has been cleared" << std::endl;

        Assimp::Importer importer;
        const std::string path = std::filesystem::current_path().string() + linkToFBX;

        //TODO: Check if fbx
        const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
        if (s == nullptr) {
            std::cout << "ERROR: Cannot read the file by path: " << path << std::endl;
            return  false;
        }

        const aiMesh* mesh = s->mMeshes[0];

        Mesh::_indices->resize(mesh->mNumFaces * 3);


        for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
            for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
            {
                (*Mesh::_indices)[(it * 3) + jt] = mesh->mFaces[it].mIndices[jt];
            }
        }
        std::cout << "Indices step successfully" << std::endl;

        if (mesh->HasPositions()) {
            Geometry::_vertex->resize(mesh->mNumVertices * 3);

            for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

                (*Geometry::_vertex)[it] = mesh->mVertices[it / 3].x;
                (*Geometry::_vertex)[it + 1] = mesh->mVertices[it / 3].y;
                (*Geometry::_vertex)[it + 2] = mesh->mVertices[it / 3].z;
            }
        }
        std::cout << "Vertex step successfully" << std::endl;

        if (mesh->HasNormals()) {
            Mesh::_normals->resize(Geometry::_vertex->size());

            for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {
                (*Mesh::_normals)[it] = mesh->mNormals[it / 3].x;
                (*Mesh::_normals)[it + 1] = mesh->mNormals[it / 3].y;
                (*Mesh::_normals)[it + 2] = mesh->mNormals[it / 3].z;
            }
        }
        std::cout << "Normals step successfully" << std::endl;

        if (mesh->HasTextureCoords(0)) {
            Mesh::_texCoords->resize((Geometry::_vertex->size() / 3) * 2);

            for (std::uint32_t it = 0; it < Mesh::_texCoords->size(); it += 2) {
                (*Mesh::_texCoords)[it] = mesh->mTextureCoords[0][it / 2].x;
                (*Mesh::_texCoords)[it + 1] = mesh->mTextureCoords[0][it / 2].y;
            }
        }
        std::cout << "Texture coords step successfully" << std::endl;

        Mesh::_isIndexed = true;
        std::cout << "Mesh has been load" << std::endl;

        Mesh::BindMesh();
        return true;
    }

    bool Mesh::Create(
        const std::string &linkToFBX,
        const bool initIndices,
        const bool initVertex,
        const bool initNormals,
        const bool initTexCoord,
        const bool initMaterial) {
        std::cout << "Mesh load process started" << std::endl;

        Mesh::_vertex->clear();
        Mesh::_indices->clear();
        Mesh::_normals->clear();
        Mesh::_texCoords->clear();
        std::cout << "Mesh data has been cleared" << std::endl;

        Assimp::Importer importer;
        const std::string path = std::filesystem::current_path().string() + linkToFBX;

        //TODO: Check if fbx
        const aiScene* s;
        aiMesh* mesh;

        if (initIndices) {
            s = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
            mesh = s->mMeshes[0];

            Geometry::_indices->resize(mesh->mNumFaces * 3);

            for (std::uint32_t it = 0; it < mesh->mNumFaces; it++) {
                for (size_t jt = 0; jt < mesh->mFaces[it].mNumIndices; jt++)
                {
                    (*Geometry::_indices)[(it * 3) + jt] = mesh->mFaces[it].mIndices[jt];
                }
            }

            Geometry::_isIndexed = true;
        }
        else
        {
            s = importer.ReadFile(path, aiProcess_Triangulate);
            mesh = s->mMeshes[0];
            Geometry::_isIndexed = false;
        }
        std::cout << "Indices step successfully" << std::endl;

        if (mesh->HasPositions() && initVertex) {
            Geometry::_vertex->resize(mesh->mNumVertices * 3);
            for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

                (*Geometry::_vertex)[it] = mesh->mVertices[it / 3].x;
                (*Geometry::_vertex)[it + 1] = mesh->mVertices[it / 3].y;
                (*Geometry::_vertex)[it + 2] = mesh->mVertices[it / 3].z;
            }
        }
        std::cout << "Vertex step successfully" << std::endl;

        if (mesh->HasNormals() && initNormals) {
            Geometry::_normals->resize(Geometry::_vertex->size());

            for (std::uint32_t it = 0; it < mesh->mNumVertices * 3; it += 3) {

                (*Geometry::_normals)[it] = mesh->mNormals[it / 3].x;
                (*Geometry::_normals)[it + 1] = mesh->mNormals[it / 3].y;
                (*Geometry::_normals)[it + 2] = mesh->mNormals[it / 3].z;
            }
        }
        std::cout << "Normals step successfully" << std::endl;

        if (mesh->HasTextureCoords(0) && initTexCoord) {
            Mesh::_texCoords->resize((Geometry::_vertex->size() / 3) * 2);

            for (std::uint32_t it = 0; it < Mesh::_texCoords->size(); it += 2) {
                (*Mesh::_texCoords)[it] = mesh->mTextureCoords[0][it / 2].x;
                (*Mesh::_texCoords)[it + 1] = mesh->mTextureCoords[0][it / 2].y;
            }
        }
        std::cout << "Texture coords step successfully" << std::endl;

        Mesh::_isIndexed = true;
        std::cout << "Mesh has been load" << std::endl;

        Mesh::BindMesh();
        return true;
    }

    bool Mesh::BindMesh() {
        if (Mesh::_vertexVbo != 0)
            glDeleteBuffers(1, &_vertexVbo);

        if (Mesh::_colorsVbo != 0)
            glDeleteBuffers(1, &_colorsVbo);

        if (Mesh::_normalsVbo != 0)
            glDeleteBuffers(1, &_normalsVbo);

        if (Mesh::_texCoordsVbo != 0) {
            glDeleteBuffers(1, &_texCoordsVbo);
        }

        if (Mesh::_vao != 0)
            glDeleteBuffers(1, &_vao);

        std::cout << "Old buffers deleted" << std::endl;

        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        std::cout << "VAO generated" << std::endl;

        if (Mesh::_vertex != nullptr) {
            glGenBuffers(1, &_vertexVbo);
            glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
            glBufferData(GL_ARRAY_BUFFER, Mesh::_vertex->size() * sizeof(float), Mesh::_vertex->data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

            std::cout << "Vertex binded" << std::endl;
        }

        if (Mesh::_normals->data() != nullptr) {
            glGenBuffers(1, &_normalsVbo);
            glBindBuffer(GL_ARRAY_BUFFER, Mesh::_normalsVbo);
            glBufferData(GL_ARRAY_BUFFER, Mesh::_normals->size() * sizeof(float), Mesh::_normals->data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, _normalsVbo);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

            std::cout << "Normals binded" << std::endl;
        }

        if (Mesh::_vertexColors->data() != nullptr) {
            glGenBuffers(1, &_colorsVbo);
            glBindBuffer(GL_ARRAY_BUFFER, Mesh::_colorsVbo);
            glBufferData(GL_ARRAY_BUFFER, Mesh::_vertexColors->size() * sizeof(float), Mesh::_vertexColors->data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(2);
            glBindBuffer(GL_ARRAY_BUFFER, _colorsVbo);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

            std::cout << "Vertex colors binded" << std::endl;
        }

        if (Mesh::_texCoords->data() != nullptr) {

            glGenBuffers(1, &_texCoordsVbo);
            glBindBuffer(GL_ARRAY_BUFFER, Mesh::_texCoordsVbo);
            glBufferData(GL_ARRAY_BUFFER, Mesh::_texCoords->size() * sizeof(float), Mesh::_texCoords->data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(3);
            glBindBuffer(GL_ARRAY_BUFFER, _texCoordsVbo);
            glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

            std::cout << "Texture coordinate binded" << std::endl;
        }

        std::cout << "Mesh has been bind to OpenGL" << std::endl;
        return true;
    }


}
