#include "Binder.h"

#include <GLEW/glew.h>
#include <GL/gl.h>

#include "Core/Logger/Logger.h"

#include "Components/Mesh.h"

namespace Render::WindowsManager::AnomalyEngine {
     bool Binder::BindMesh(Mesh* mesh) {

        if (mesh == nullptr) {
            Core::Logger::LogError("Mesh pointer is null: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return false;
        }

        if (mesh->_vertexVbo != 0) {
            glDeleteBuffers(1, &mesh->_vertexVbo);
            mesh->_vertexVbo = 0;

        }
        if (mesh->_colorsVbo != 0) {
            glDeleteBuffers(1, &mesh->_colorsVbo);
            mesh->_colorsVbo = 0;
        }
        if (mesh->_normalsVbo != 0) {
            glDeleteBuffers(1, &mesh->_normalsVbo);
            mesh->_normalsVbo = 0;
        }
        if (mesh->_texCoordsVbo != 0) {
            glDeleteBuffers(1, &mesh->_texCoordsVbo);
            mesh->_texCoordsVbo = 0;
        }

        if (mesh->_vao != 0)
            glDeleteVertexArrays(1, &mesh->_vao);

        Core::Logger::Logger::LogInfo("Old buffers deleted");

        if (mesh->_vertex != nullptr) {
            glGenBuffers(1, &mesh->_vertexVbo);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->_vertexVbo);
            glBufferData(GL_ARRAY_BUFFER, mesh->_vertex->size() * sizeof(float), mesh->_vertex->data(), GL_STATIC_DRAW);

            Core::Logger::Logger::LogInfo("Vertex binded");
        }

        if (mesh->_normals->data() != nullptr) {
            glGenBuffers(1, &mesh->_normalsVbo);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->_normalsVbo);
            glBufferData(GL_ARRAY_BUFFER, mesh->_normals->size() * sizeof(float), mesh->_normals->data(), GL_STATIC_DRAW);

            Core::Logger::Logger::LogInfo("Normals binded");
        }

        if (mesh->_vertexColors->data() != nullptr) {
            glGenBuffers(1, &mesh->_colorsVbo);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->_colorsVbo);
            glBufferData(GL_ARRAY_BUFFER, mesh->_vertexColors->size() * sizeof(float), mesh->_vertexColors->data(), GL_STATIC_DRAW);

            Core::Logger::Logger::LogInfo("Vertex colors binded");
        }

        if (mesh->_texCoords->data() != nullptr) {
            glGenBuffers(1, &mesh->_texCoordsVbo);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->_texCoordsVbo);
            glBufferData(GL_ARRAY_BUFFER, mesh->_texCoords->size() * sizeof(float), mesh->_texCoords->data(), GL_STATIC_DRAW);

            Core::Logger::Logger::LogInfo("Texture coordinate binded");
        }

         Core::Logger::Logger::LogInfo("Mesh has been bind to OpenGL");
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
