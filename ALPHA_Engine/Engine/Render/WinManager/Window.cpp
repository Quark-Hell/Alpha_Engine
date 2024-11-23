#include "Window.h"
#include  <cassert>

#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Core/Logger/Logger.h"

#include "AnomalyEngine/Components/Camera.h"

void APIENTRY openglCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    std::cout << "---------------------opengl-callback-start------------" << std::endl;
    std::cout << "message: "<< message << std::endl;
    std::cout << "type: ";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            std::cout << "ERROR";
        break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            std::cout << "DEPRECATED_BEHAVIOR";
        break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cout << "UNDEFINED_BEHAVIOR";
        break;
        case GL_DEBUG_TYPE_PORTABILITY:
            std::cout << "PORTABILITY";
        break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            std::cout << "PERFORMANCE";
        break;
        case GL_DEBUG_TYPE_OTHER:
            std::cout << "OTHER";
        break;
    }
    std::cout << std::endl;

    std::cout << "id: " << id << std::endl;
    std::cout << "severity: ";
    switch (severity){
        case GL_DEBUG_SEVERITY_LOW:
            std::cout << "LOW";
        break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cout << "MEDIUM";
        break;
        case GL_DEBUG_SEVERITY_HIGH:
            std::cout << "HIGH";
        break;
    }
    std::cout << std::endl;
    std::cout << "---------------------opengl-callback-end--------------" << std::endl;
}


namespace Render::WindowsManager {
    Window::~Window() {
        if (_window != nullptr) {
            free(_window);
        }
    }

    Window::Window(const int width, const int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        glfwWindowHint(GLFW_SAMPLES, 4);

        _window = glfwCreateWindow(width, height, title.c_str(), monitor, share);
        _width = width;
        _height = height;
        _title = title;

        if (_window == nullptr)
        {
            Core::Logger::LogCritical("Failed to create GLFW window: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            glfwTerminate();
            abort();
        }

        int bufferWidth, bufferHeight;
        glfwGetFramebufferSize(_window, &bufferWidth, &bufferHeight);
        //glViewport(0, 0, bufferWidth, bufferHeight);
        if (_width > _height) {
            glViewport(0, (_height - _width) / 2, bufferWidth, bufferHeight);
        }
        else {
            glViewport((_width - _height) / 2, 0, bufferWidth, bufferHeight);
        }

        glfwMakeContextCurrent(_window);
        glfwSwapInterval(1);

        glEnable(GL_MULTISAMPLE);

        if (glfwRawMouseMotionSupported())
            glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            Core::Logger::LogCritical("Critical: glew does not inited: " + std::string(__FILE__ ":") + std::to_string(__LINE__));
            fprintf(stderr, "%s\n", glewGetErrorString(err));
            glfwTerminate();
            abort();
        }

        glEnable(GL_DEBUG_OUTPUT );
        glDebugMessageCallback(openglCallbackFunction, 0);
    }

    void Window::Resize(int width, int height) {

    }
    void Window::SetSync(const bool sync) {
        _isSync = sync;

        glfwMakeContextCurrent(_window);
        if (_isSync == true) glfwSwapInterval(1);
        else glfwSwapInterval(0);
    }

    void Window::SetCamera(AnomalyEngine::Camera* camera) {
        _activeCamera = camera;
        _activeCamera->SetAspect(static_cast<float>(_width) / static_cast<float>(_height));
    }

    bool Window::GetCursorVisible() {
        return _isCursorVisible;
    }

    void Window::SetCursorVisible(const bool isVisible) {
        _isCursorVisible = isVisible;

        if (_isCursorVisible)
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        else
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    GLFWwindow *Window::GetGLFWwindow() const {
        return _window;
    }
}
