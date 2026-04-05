#include "Binder.h"

#include <glad/glad.h>

#include "Core/Logger/Logger.h"

#include "AnomalyEngine/Components/Mesh.h"

namespace AnomalyEngine {
     bool Binder::BindMesh(const Mesh& mesh) {
        if (_vertexVbo != 0) {
            glDeleteBuffers(1, &_vertexVbo);
            _vertexVbo = 0;
        }
        if (_colorsVbo != 0) {
            glDeleteBuffers(1, &_colorsVbo);
            _colorsVbo = 0;
        }
        if (_normalsVbo != 0) {
            glDeleteBuffers(1, &_normalsVbo);
            _normalsVbo = 0;
        }
        if (_texCoordsVbo != 0) {
            glDeleteBuffers(1, &_texCoordsVbo);
            _texCoordsVbo = 0;
        }

        Core::Logger::LogInfo("Old buffers deleted");

        if (mesh._geometry->Vertices != nullptr) {
            glGenBuffers(1, &_vertexVbo);
            glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
            glBufferData(GL_ARRAY_BUFFER, mesh._geometry->Vertices->size() * sizeof(float), mesh._geometry->Vertices->data(), GL_STATIC_DRAW);

            Core::Logger::LogInfo("Vertex binded");
        }

        if (mesh._geometry->Normals->data() != nullptr) {
            glGenBuffers(1, &_normalsVbo);
            glBindBuffer(GL_ARRAY_BUFFER, _normalsVbo);
            glBufferData(GL_ARRAY_BUFFER, mesh._geometry->Normals->size() * sizeof(float), mesh._geometry->Normals->data(), GL_STATIC_DRAW);

            Core::Logger::LogInfo("Normals binded");
        }

        if (mesh._geometry->VertexColors->data() != nullptr) {
            glGenBuffers(1, &_colorsVbo);
            glBindBuffer(GL_ARRAY_BUFFER, _colorsVbo);
            glBufferData(GL_ARRAY_BUFFER, mesh._geometry->VertexColors->size() * sizeof(float), mesh._geometry->VertexColors->data(), GL_STATIC_DRAW);

            Core::Logger::LogInfo("Vertex colors binded");
        }

        if (mesh._geometry->TexCoords->data() != nullptr) {
            glGenBuffers(1, &_texCoordsVbo);
            glBindBuffer(GL_ARRAY_BUFFER, _texCoordsVbo);
            glBufferData(GL_ARRAY_BUFFER, mesh._geometry->TexCoords->size() * sizeof(float), mesh._geometry->TexCoords->data(), GL_STATIC_DRAW);

            Core::Logger::LogInfo("Texture coordinate binded");
        }

         Core::Logger::LogInfo("Mesh has been bind to OpenGL");
         return true;
     }

    //ool Binder::SharedBindMesh(Components::Mesh* mesh) {

    //    glGenVertexArrays(1, &mesh->_vao);
    //    glBindVertexArray(mesh->_vao);

    //    if (mesh->_vertexVbo != 0) {
    //       glEnableVertexAttribArray(0);
    //       glBindBuffer(GL_ARRAY_BUFFER, mesh->_vertexVbo);
    //       glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    //       std::cout << "Vertex binded" << std::endl;
    //    }

    //    if (mesh->_normalsVbo != 0) {
    //        glEnableVertexAttribArray(1);
    //        glBindBuffer(GL_ARRAY_BUFFER, mesh->_normalsVbo);
    //        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    //        std::cout << "Normals binded" << std::endl;
    //    }

    //    if (mesh->_colorsVbo != 0) {
    //        glEnableVertexAttribArray(2);
    //        glBindBuffer(GL_ARRAY_BUFFER, mesh->_colorsVbo);
    //        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    //        std::cout << "Vertex colors binded" << std::endl;
    //    }

    //    if (mesh->_texCoordsVbo != 0) {
    //        glEnableVertexAttribArray(3);
    //        glBindBuffer(GL_ARRAY_BUFFER, mesh->_texCoordsVbo);
    //        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    //        std::cout << "Texture coordinate binded" << std::endl;
    //    }

    //    glBindVertexArray(0);
    //    return  true;
    //}
}
