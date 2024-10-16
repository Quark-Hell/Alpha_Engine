#include "Render.h"
#include <GLEW/glew.h>
#include <GL/gl.h>
#include "GLFW/glfw3.h"

#include "Anomaly/WinManager/Window.h"
#include <iostream>

namespace AnomalyEngine::Render {
    Render* Render::GetInstance() {
        static Render render;
        return &render;
    }

    void Render::ClearFrameBuffer() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Render::SetWindowMatrix(const int width, const int height) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
    }

    void Render::SetModelMatrix() {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }


    void Render::PrepareRender() {
        glClearColor(0.3f, 0.3f, 0.3f, 0.f);

        //TODO: I think I shouldn't do this here
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Render::SetActiveWindow(const AnomalyEngine::WindowsManager::Window& window) {
        glfwMakeContextCurrent(window._window);
    }

    void Render::RenderScene(const AnomalyEngine::WindowsManager::Window* window)
    {
        if (window->_activeCamera != nullptr)
        {
            Render::SetWindowMatrix(window->_width, window->_height);
            glViewport(0, 0, window->_width, window->_height);
            glOrtho(0, window->_width, window->_height, 0, -1, 1);

            Render::SetModelMatrix();

            glBegin(GL_TRIANGLES);

            glColor3f(0.5,0,0);

            glVertex2f(100.0,100.0);
            glVertex2f(380.0,250.0);
            glVertex2f(100.0,400.0);
        }
    }

    void Render::RenderLoop(std::vector<std::unique_ptr<AnomalyEngine::WindowsManager::Window>>* windows) {
        for (auto& window : *windows)
        {
            if (window->_initialized == false)
                window->Init();

            Render::SetActiveWindow(*window);

            glfwPollEvents();
            Render::ClearFrameBuffer();
            Render::PrepareRender();

            Render::RenderScene(window.get());

            glEnd();

            glFinish();
            glfwSwapBuffers(window->_window);
        }
    }
}