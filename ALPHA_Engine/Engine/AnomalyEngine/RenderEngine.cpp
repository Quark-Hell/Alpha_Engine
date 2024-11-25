#include "RenderEngine.h"
#include <glad/glad.h>

#include <WindowsManager/WindowsBuffer.h>

#include "GLFW/glfw3.h"

#include "Core/Logger/Logger.h"
#include "Core/Object.h"

#include "Buffers/CamerasBuffer.h"
#include "Buffers/MeshesBuffer.h"
#include "Shaders/ShaderProgram.h"

namespace AnomalyEngine {
    RenderEngine::RenderEngine() : System({"MeshBuffer", "CamerasBuffer"}, 5000) {}

    void RenderEngine::ClearFrameBuffer() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderEngine::SetWindowMatrix(const size_t width, const size_t height) {
        glViewport(0, 0, width, height);
    }

    void RenderEngine::PrepareRender() {
        glClearColor(0.3f, 0.3f, 0.3f, 0.f);

        //TODO: I think I shouldn't do this here
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    int RenderEngine::GetRenderMode(const ShaderProgram& shader) {
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
                Core::Logger::Logger::LogCritical("Unknown render mode: " + __LOGERROR__);
            abort();
            break;
        }

        return glRenderMode;
    }

    bool RenderEngine::MeshChecker(const Mesh& mesh) {
        if (mesh._material.Shader == nullptr) {
            Core::Logger::Logger::LogError("Shader was be null: " + __LOGERROR__);
            return false;
        }
        if (mesh._material.Shader->GetCompiledStatus() == false) {
            Core::Logger::Logger::LogError("Shader was not be compiled: " + __LOGERROR__);
            return false;
        }
        if (mesh._material.Shader->GetProgramId() == 0) {
            Core::Logger::Logger::LogError("Shader program was not be created: "  + __LOGERROR__);
            return false;
        }

        return true;
    }

    void RenderEngine::GenerateVao(const Mesh &mesh) {
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        if (mesh.GetVertexVbo() != 0) {
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, mesh.GetVertexVbo());
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        }
        if (mesh.GetNormalsVbo() != 0) {
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, mesh.GetNormalsVbo());
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        }
        if (mesh.GetColorsVbo() != 0) {
            glEnableVertexAttribArray(2);
            glBindBuffer(GL_ARRAY_BUFFER, mesh.GetColorsVbo());
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        }
        if (mesh.GetTexCoordsVbo() != 0) {
            glEnableVertexAttribArray(3);
            glBindBuffer(GL_ARRAY_BUFFER, mesh.GetTexCoordsVbo());
            glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        }
    }

    void RenderEngine::RenderMeshes(Camera &camera, const MeshesBuffer &meshes) {
        for (auto& mesh : meshes._data) {
            if (!MeshChecker(*mesh))
                continue;

            GenerateVao(*mesh);

            glUseProgram(mesh->_material.Shader->GetProgramId());
            glBindVertexArray(_vao);

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
            glDeleteVertexArrays(1, &_vao);
        }
    }

    void RenderEngine::EntryPoint(std::vector<Core::SystemData *> &data) {
        if (data[0] == nullptr || data[1] == nullptr) {
            Core::Logger::LogError("Data was null: " + __LOGERROR__);
            return;
        }

        auto *meshesBuffer = reinterpret_cast<MeshesBuffer*>(data[0]);
        auto *camerasBuffer = reinterpret_cast<CamerasBuffer*>(data[1]);

        for (auto& camera : camerasBuffer->_data) {
            if (camera->_window == nullptr) {
                Core::Logger::LogWarning("Camera window was null");
                continue;
            }
            glfwMakeContextCurrent(camera->_window);

            ClearFrameBuffer();
            PrepareRender();

            SetWindowMatrix(camera->GetWidth(), camera->GetHeight());

            RenderMeshes(*camera, *meshesBuffer);

            glFinish();
        }

        //if (camera.window == nullptr) {
        //    Core::Logger::Logger::LogError("active camera was be null: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
        //    return;
        //}
    }
}
