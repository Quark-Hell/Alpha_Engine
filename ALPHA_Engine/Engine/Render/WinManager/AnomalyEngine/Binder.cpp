#include "Binder.h"

#include <GLEW/glew.h>
#include <GL/gl.h>

#include <iostream>

#include "Components/Mesh.h"

namespace Render::AnomalyEngine {
     bool Binder::BindMesh(Components::Mesh* mesh) {

        if (mesh == nullptr) {
            std::cout << "Error: Mesh pointer is null" << std::endl;
            return false;
        }

        if (mesh->_vertexVbo != 0)
            glDeleteBuffers(1, &mesh->_vertexVbo);

        if (mesh->_colorsVbo != 0)
            glDeleteBuffers(1, &mesh->_colorsVbo);

        if (mesh->_normalsVbo != 0)
            glDeleteBuffers(1, &mesh->_normalsVbo);

        if (mesh->_texCoordsVbo != 0) {
            glDeleteBuffers(1, &mesh->_texCoordsVbo);
        }

        if (mesh->_vao != 0)
            glDeleteBuffers(1, &mesh->_vao);

        std::cout << "Info: Old buffers deleted" << std::endl;

        glGenVertexArrays(1, &mesh->_vao);
        glBindVertexArray(mesh->_vao);

        std::cout << "Info: VAO generated" << std::endl;

        if (mesh->_vertex != nullptr) {
            glGenBuffers(1, &mesh->_vertexVbo);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->_vertexVbo);
            glBufferData(GL_ARRAY_BUFFER, mesh->_vertex->size() * sizeof(float), mesh->_vertex->data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->_vertexVbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

            std::cout << "Info: Vertex binded" << std::endl;
        }

        if (mesh->_normals->data() != nullptr) {
            glGenBuffers(1, &mesh->_normalsVbo);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->_normalsVbo);
            glBufferData(GL_ARRAY_BUFFER, mesh->_normals->size() * sizeof(float), mesh->_normals->data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->_normalsVbo);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

            std::cout << "Info: Normals binded" << std::endl;
        }

        if (mesh->_vertexColors->data() != nullptr) {
            glGenBuffers(1, &mesh->_colorsVbo);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->_colorsVbo);
            glBufferData(GL_ARRAY_BUFFER, mesh->_vertexColors->size() * sizeof(float), mesh->_vertexColors->data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(2);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->_colorsVbo);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

            std::cout << "Info: Vertex colors binded" << std::endl;
        }

        if (mesh->_texCoords->data() != nullptr) {

            glGenBuffers(1, &mesh->_texCoordsVbo);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->_texCoordsVbo);
            glBufferData(GL_ARRAY_BUFFER, mesh->_texCoords->size() * sizeof(float), mesh->_texCoords->data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(3);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->_texCoordsVbo);
            glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

            std::cout << "Info: Texture coordinate binded" << std::endl;
        }

        std::cout << "Info: Mesh has been bind to OpenGL" << std::endl;
        return true;

      return true;
    }
}
