#include "RenderEngine.h"
#include <GLEW/glew.h>
#include <GL/gl.h>
#include "GLFW/glfw3.h"

#include "Render/WinManager/Window.h"
#include <iostream>
#include <Core/Object.h>

#include "Components/Camera.h"
#include "Components/Mesh.h"
#include "Shaders/ShaderProgram.h"

namespace Render::AnomalyEngine {
    RenderEngine* RenderEngine::GetInstance() {
        static RenderEngine render;
        return &render;
    }

    void RenderEngine::ClearFrameBuffer() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderEngine::SetWindowMatrix(const int width, const int height) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glViewport(0, 0, width, height);
    }

    void RenderEngine::SetModelMatrix() {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    void RenderEngine::SetCameraProjection(const Render::WindowsManager::Window& window) {
        float Fov;
        float Aspect;
        float ZNear;
        float ZFar;

        window._activeCamera->GetCameraInfo(&Fov, &Aspect, &ZNear, &ZFar);

        gluPerspective(90, 1.333, ZNear, ZFar);
        //if (window->_activeCamera->GetProjection())
        //{
            //glOrtho(0, window->_width, window->_height, 0, ZNear, ZFar);
        //}
        //else
        //{
        //    gluPerspective(Fov, Aspect, ZNear, ZFar);
        //}
    }

    void RenderEngine::SetCameraTransform(Render::AnomalyEngine::Components::Camera* camera) {
        Core::Object* parent = camera->GetParentObject();

        //glMatrixMode(GL_PROJECTION);
        //glLoadIdentity();

        if (parent == nullptr) {
            glTranslatef(0, 0, 0);
        }
        else {
            glRotatef(0, 1.f, 0.f, 0.f);
            glRotatef(0, 0.f, 1.f, 0.f);
            glRotatef(0, 0.f, 0.f, 1.f);

            glTranslatef(
                parent->transform.GetPosition().X,
                parent->transform.GetPosition().Y,
                parent->transform.GetPosition().Z);
        }
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
            std::cout << "Error: active camera was be null" << std::endl;
            return;
        }

        RenderEngine::SetWindowMatrix(window._width, window._height);
        RenderEngine::SetCameraProjection(window);
        RenderEngine::SetCameraTransform(window._activeCamera);

        RenderEngine::SetModelMatrix();

        RenderMeshes(window._activeCamera);
    }

    int RenderEngine::GetRenderMode(Render::AnomalyEngine::Shaders::ShaderProgram& shader) {
        Shaders::RenderMode renderMode = shader.GetRenderMode();
        int glRenderMode = 0;

        switch (static_cast<int>(renderMode)) {
            case static_cast<int>(Shaders::RenderMode::Points):
                glRenderMode = GL_POINTS;
            break;
            case static_cast<int>(Shaders::RenderMode::Lines):
                glRenderMode = GL_LINES;
            break;
            case static_cast<int>(Shaders::RenderMode::LineStrip):
                glRenderMode = GL_LINE_STRIP;
            break;
            case static_cast<int>(Shaders::RenderMode::Triangles):
                glRenderMode = GL_TRIANGLES;
            break;
            default:
                std::cout << "Critical: Unknown render mode" << std::endl;
            abort();
            break;
        }

        return glRenderMode;
    }

    bool RenderEngine::MeshChecker(const Render::AnomalyEngine::Components::Mesh *mesh) {
        if (mesh == nullptr) {
            std::cout << "Error: Mesh was null" << std::endl;
            return false;
        }
        if (mesh->_material.Shader == nullptr) {
            std::cout << "Error: Shader was be null" << std::endl;
            return false;
        }
        if (mesh->_material.Shader->GetCompiledStatus() == false) {
            std::cout << "Error: Shader was not be compiled" << std::endl;
            return false;
        }
        if (mesh->_material.Shader->GetProgramId() == 0) {
            std::cout << "Error: Shader program was not be created" << std::endl;
            return false;
        }

        return true;
    }

    void RenderEngine::RenderMeshes(Render::AnomalyEngine::Components::Camera* camera) {
        if (_meshBuffer == nullptr) {
            std::cout << "Error: Mesh buffer was null" << std::endl;
            return;
        }
        if (camera == nullptr) {
            std::cout << "Error: Camera was null" << std::endl;
            return;
        }

        for (size_t i = 0; i < _meshBuffer->size(); i++) {

            Components::Mesh* mesh = _meshBuffer->at(i).get();
            if (!MeshChecker(mesh))
                continue;

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

            //SetModelMatrix();
            glDepthFunc(GL_LEQUAL);

            glUseProgram(mesh->_material.Shader->GetProgramId());
            glBindVertexArray(mesh->_vao);

            mesh->_material.Shader->ApplyShadersSettings(camera);
            const int renderMode = GetRenderMode(*mesh->_material.Shader);

            if (mesh->_isIndexed)
                glDrawElements(renderMode, mesh->_indices->size(), GL_UNSIGNED_INT, mesh->_indices->data());
            else
                glDrawArrays(renderMode, 0, mesh->_vertex->size() / 3);

            glDepthFunc(GL_LESS);
            glBindVertexArray(0);
            glDeleteVertexArrays(1, &mesh->_vao);
        }
    }

    void RenderEngine::LoadMeshArray(std::vector<std::unique_ptr<Render::AnomalyEngine::Components::Mesh>>* meshBuffer) {
        _meshBuffer = meshBuffer;
    }

    void RenderEngine::RenderLoop(Render::WindowsManager::Window& windows) {

       RenderEngine::ClearFrameBuffer();
       RenderEngine::PrepareRender();

       RenderEngine::RenderScene(windows);

       glFinish();

    }
}
