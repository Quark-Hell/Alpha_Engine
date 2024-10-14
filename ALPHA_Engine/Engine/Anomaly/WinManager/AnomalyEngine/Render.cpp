#include "Render.h"
#include <GLEW/glew.h>
#include <GL/gl.h>
#include "GLFW/glfw3.h"

#include "Anomaly/WinManager/Window.h"

namespace AnomalyEngine::Render {
    Render& Render::GetInstance() {
        static Render* render = new Render();
        return *render;
    }

    void Render::ClearFrameBuffer() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void Render::PrepareRender() {
        glClearColor(0.3f, 0.3f, 0.3f, 0.f);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }


    void Render::RenderLoop(std::vector<std::unique_ptr<AnomalyEngine::WindowsManager::Window>>* windows) {
        for (auto& window : *windows) {
            int width, height;
            glfwGetFramebufferSize(window->_window, &width, &height);
            glViewport(0, 0, width, height);

            glfwMakeContextCurrent(window->_window);

            glfwPollEvents();
            Render::ClearFrameBuffer();
            Render::PrepareRender();

            glFinish();
            glfwSwapBuffers(window->_window);
        }
    }
}