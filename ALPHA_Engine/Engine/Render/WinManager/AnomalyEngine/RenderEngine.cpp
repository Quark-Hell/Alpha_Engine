#include "RenderEngine.h"
#include <GLEW/glew.h>
#include <GL/gl.h>
#include "GLFW/glfw3.h"

#include "Render/WinManager/Window.h"
#include "Logger/Logger.h"
#include "Core/Object.h"

#include "Components/Camera.h"
#include "Components/Mesh.h"
#include "Shaders/ShaderProgram.h"

namespace Render::WindowsManager::AnomalyEngine {
    RenderEngine* RenderEngine::GetInstance() {
        static RenderEngine render;
        return &render;
    }

    void RenderEngine::ClearFrameBuffer() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderEngine::SetWindowMatrix(const int width, const int height) {
        glViewport(0, 0, width, height);
    }

    void RenderEngine::PrepareRender() {
        glClearColor(0.3f, 0.3f, 0.3f, 0.f);

        //TODO: I think I shouldn't do this here
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void RenderEngine::RenderScene(const Render::WindowsManager::Window& window)
    {
        if (window._activeCamera == nullptr) {
            Logger::Logger::LogError("active camera was be null: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return;
        }

        RenderEngine::SetWindowMatrix(window._width, window._height);

        RenderMeshes(window._activeCamera);
    }

    int RenderEngine::GetRenderMode(Render::WindowsManager::AnomalyEngine::ShaderProgram& shader) {
        RenderMode renderMode = shader.GetRenderMode();
        int glRenderMode = 0;

        switch (static_cast<int>(renderMode)) {
            case static_cast<int>(RenderMode::Points):
                glRenderMode = GL_POINTS;
            break;
            case static_cast<int>(RenderMode::Lines):
                glRenderMode = GL_LINES;
            break;
            case static_cast<int>(RenderMode::LineStrip):
                glRenderMode = GL_LINE_STRIP;
            break;
            case static_cast<int>(RenderMode::Triangles):
                glRenderMode = GL_TRIANGLES;
            break;
            default:
                Logger::Logger::LogCritical("Unknown render mode: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            abort();
            break;
        }

        return glRenderMode;
    }

    bool RenderEngine::MeshChecker(const Render::WindowsManager::AnomalyEngine::Mesh *mesh) {
        if (mesh == nullptr) {
            Logger::Logger::LogError("Mesh was null: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return false;
        }
        if (mesh->_material.Shader == nullptr) {
            Logger::Logger::LogError("Shader was be null: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return false;
        }
        if (mesh->_material.Shader->GetCompiledStatus() == false) {
            Logger::Logger::LogError("Shader was not be compiled: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return false;
        }
        if (mesh->_material.Shader->GetProgramId() == 0) {
            Logger::Logger::LogError("Shader program was not be created: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return false;
        }

        return true;
    }

    void RenderEngine::GenerateVao(Render::WindowsManager::AnomalyEngine::Mesh *mesh) {
        glGenVertexArrays(1, &mesh->_vao);
        glBindVertexArray(mesh->_vao);
        if (mesh->_vertexVbo != 0) {
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->_vertexVbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        }
        if (mesh->_normalsVbo != 0) {
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->_normalsVbo);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        }
        if (mesh->_colorsVbo != 0) {
            glEnableVertexAttribArray(2);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->_colorsVbo);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        }
        if (mesh->_texCoordsVbo != 0) {
            glEnableVertexAttribArray(3);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->_texCoordsVbo);
            glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        }
    }

    void RenderEngine::RenderMeshes(Render::WindowsManager::AnomalyEngine::Camera* camera) {
        if (_meshBuffer == nullptr) {
            Logger::Logger::LogError("Mesh buffer was null: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return;
        }
        if (camera == nullptr) {
            Logger::Logger::LogError("Camera was null: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return;
        }

        for (auto& it : *_meshBuffer) {
            auto* mesh = static_cast<Mesh*>(it.get());

            if (!MeshChecker(mesh))
                continue;

            GenerateVao(mesh);

            glUseProgram(mesh->_material.Shader->GetProgramId());
            glBindVertexArray(mesh->_vao);

            mesh->_material.Shader->ApplyShadersSettings(camera);
            const int renderMode = GetRenderMode(*mesh->_material.Shader);

            if (mesh->_isIndexed)
                glDrawElements(renderMode, mesh->_indices->size(), GL_UNSIGNED_INT, mesh->_indices->data());
            else
                glDrawArrays(renderMode, 0, mesh->_vertex->size() / 3);

            //glDepthFunc(GL_NEVER);
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);

            //Delete vao that was created by GenerateVao() function
            glDeleteVertexArrays(1, &mesh->_vao);
        }
    }

    void RenderEngine::LoadMeshArray(std::list<std::unique_ptr<Core::Geometry>>* meshBuffer) {
        _meshBuffer = meshBuffer;
    }

    void RenderEngine::RenderLoop(Render::WindowsManager::Window& windows) {
       RenderEngine::ClearFrameBuffer();
       RenderEngine::PrepareRender();

       RenderEngine::RenderScene(windows);

       glFinish();
    }
}
