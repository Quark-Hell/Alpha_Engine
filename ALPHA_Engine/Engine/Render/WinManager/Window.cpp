#include "Window.h"
#include  <cassert>

#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GL/gl.h>
#include "GLFW/glfw3.h"

#include <iostream>

#include "AnomalyEngine/Components/Camera.h"

namespace Render::WindowsManager {
    Window::~Window() {
        if (_window != nullptr) {
            free(_window);
        }
    }

    Window::Window(const int width, const int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
        _window = glfwCreateWindow(width, height, title, monitor, share);
        _width = width;
        _height = height;
        _title = title;

        if (_window == nullptr)
        {
            assert("Critical: Failed to create GLFW window");
            glfwTerminate();
            abort();
        }

        int bufferWidth, bufferHeight;
        glfwGetFramebufferSize(_window, &bufferWidth, &bufferHeight);
        glViewport(0, 0, bufferWidth, bufferHeight);

        glfwMakeContextCurrent(_window);
        glfwSwapInterval(1);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        glfwWindowHint(GLFW_SAMPLES, 4);
        glEnable(GL_MULTISAMPLE);

        if (glfwRawMouseMotionSupported())
            glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            std::cout << "Critical: glew does not inited" << std::endl;
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
            glfwTerminate();
            abort();
        }
        //glfwMakeContextCurrent(nullptr);
    }

    void Window::Resize(int width, int height) {

    }
    void Window::SetSync(const bool sync) {
        _isSync = sync;

        glfwMakeContextCurrent(_window);
        if (_isSync == true) glfwSwapInterval(1);
        else glfwSwapInterval(0);
    }

    void Window::SetCamera(Render::AnomalyEngine::Components::Camera* camera) {
        _activeCamera = camera;
    }

    bool Window::GetCursorVisible() {
        return _isCursorVisible;
    }

    void Window::SetCursorVisible(bool isVisible) {
        _isCursorVisible = isVisible;

        if (_isCursorVisible)
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        else
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

}
