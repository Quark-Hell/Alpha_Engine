#include "RenderEngine.h"
#include <glad/glad.h>

#include "WindowsManager/Buffers/WindowsBuffer.h"

#include "GLFW/glfw3.h"

#include "Core/Logger/Logger.h"
#include "Core/Object.h"

#include "Buffers/CamerasBuffer.h"
#include "Buffers/MeshesBuffer.h"
#include "Shaders/ShaderProgram.h"

namespace AnomalyEngine {
    RenderEngine::RenderEngine() : System({"MeshBuffer", "CamerasBuffer", "WindowsBuffer"}, 5000) {}

    void RenderEngine::ClearFrameBuffer() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderEngine::PrepareRender(const size_t width, const size_t height) {
        glViewport(0, 0, width, height);
        glDisable(GL_SCISSOR_TEST);

        glClearColor(0.3f, 0.3f, 0.3f, 0.f);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    void RenderEngine::PrepareRender(
        glm::vec2 size,
        glm::vec2 position) {

        glViewport(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y));
        glScissor(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y));
        glEnable(GL_SCISSOR_TEST);

        glClearColor(0.1f, 0.1f, 0.1f, 0.f);

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
        if (data[0] == nullptr || data[1] == nullptr || data[2] == nullptr) {
            Core::Logger::LogError("Data was null: " + __LOGERROR__);
            return;
        }

        auto *meshesBuffer = reinterpret_cast<MeshesBuffer*>(data[0]);
        auto *camerasBuffer = reinterpret_cast<CamerasBuffer*>(data[1]);
        auto *windowsBuffer = reinterpret_cast<WindowsManager::WindowsBuffer*>(data[2]);

        for (auto& window : windowsBuffer->GetAllData()) {
            glm::vec2 size = window->GetSize();
            PrepareRender(size.x, size.y);
            ClearFrameBuffer();
        }

        int i = 0;

        for (auto& camera : camerasBuffer->_data) {
            i++;
            if (camera->_window == nullptr) {
                Core::Logger::LogWarning("Camera window was null");
                continue;
            }
            if (camera->_window->GetGLFWwindow() == nullptr) {
                Core::Logger::LogWarning("Camera glfw window was null");
                continue;
            }

            glfwMakeContextCurrent(camera->_window->GetGLFWwindow());

            if (camera->GetUseRectangle()) {
                if (camera->_window->CheckRectangleExist(camera->GetRectangleIndex())) {
                    constexpr float epsilon = 0.0005f;

                    float xRealSize = camera->_window->GetRectangleSize(camera->GetRectangleIndex()).x * camera->_window->GetSize().x;
                    float yRealSize = camera->_window->GetRectangleSize(camera->GetRectangleIndex()).y * camera->_window->GetSize().y;

                    glm::vec2 realSize = {xRealSize + epsilon, yRealSize + epsilon};

                    float xRealPos = camera->_window->GetRectanglePosition(camera->GetRectangleIndex()).x * camera->_window->GetSize().x;
                    float yRealPos = camera->_window->GetRectanglePosition(camera->GetRectangleIndex()).y * camera->_window->GetSize().y;

                    glm::vec2 realPosition = {xRealPos + epsilon, yRealPos};

                    if (realSize.x + 0.5f > std::ceilf(realSize.x)) {
                        realSize.x = std::ceilf(realSize.x);
                    }
                    if (realPosition.x + 0.5f > std::ceilf(realPosition.x)) {
                        realPosition.x = std::ceilf(realPosition.x);
                    }

                    PrepareRender(
                            realSize,
                            realPosition
                        );
                }
                else {
                    Core::Logger::LogCritical("Index out of bounds: " + __LOGERROR__);
                }
            }
            else {
                PrepareRender(camera->GetWidth(), camera->GetHeight());
            }

            ClearFrameBuffer();

            RenderMeshes(*camera, *meshesBuffer);

            glFinish();
        }
    }
}
