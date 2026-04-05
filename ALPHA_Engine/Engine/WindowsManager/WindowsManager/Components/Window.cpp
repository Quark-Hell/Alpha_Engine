#include "Window.h"

#include <limits>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Core/Logger/Logger.h"

void APIENTRY openglCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    if (type == GL_DEBUG_TYPE_OTHER) {
        return;
    }

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


namespace WindowsManager {
    Window::~Window() {
        glfwDestroyWindow(_window);
    }

    void Window::SetWindowHints() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        glfwWindowHint(GLFW_SAMPLES, 4);
    }

    Window::Window(const glm::vec2& size, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share) {
        SetWindowHints();

        SetSize(size);
        SetTitle(title);

        const int width = static_cast<int>(_size.x);
        const int height = static_cast<int>(_size.y);
        _window = glfwCreateWindow(width, height, title.c_str(), monitor, share);

        if (_window == nullptr)
        {
            Core::Logger::LogCritical("Failed to create GLFW window: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            glfwTerminate();
            abort();
        }

        glfwMakeContextCurrent(_window);
        glfwSwapInterval(1);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            glfwTerminate();
            Core::Logger::LogCritical("Critical: glad does not inited: " + std::string(__FILE__ ":") + std::to_string(__LINE__));
        }

        glEnable(GL_MULTISAMPLE);

        int bufferWidth, bufferHeight;
        glfwGetFramebufferSize(_window, &bufferWidth, &bufferHeight);
        if (_size.x > _size.y) {
            glViewport(0, static_cast<int>(_size.y - _size.x) / 2, bufferWidth, bufferHeight);
        }
        else {
            glViewport(static_cast<int>(_size.x - _size.y) / 2, 0, bufferWidth, bufferHeight);
        }

        glEnable(GL_DEBUG_OUTPUT );
        glDebugMessageCallback(openglCallbackFunction, 0);
    }

    void Window::SetSync(const bool sync) {
        _isSync = sync;

        glfwMakeContextCurrent(_window);
        if (_isSync) glfwSwapInterval(1);
        else glfwSwapInterval(0);
    }

    bool Window::GetCursorVisible() const {
        return _isCursorVisible;
    }

    void Window::SetCursorVisible(const bool isVisible) {
        _isCursorVisible = isVisible;

        if (_isCursorVisible)
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        else
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void Window::SetTitle(const std::string& title) {
        _title = title;
    }

    std::string Window::GetTitle() {
        return _title;
    }


    glm::vec2 Window::GetSize() {
        return _size;
    }

    void Window::SetSize(const glm::vec2& size) {
        if (size.x < 0) {
            Core::Logger::LogError("X size should be positive: " + __LOGERROR__);
            return;
        }
        if (size.y < 0) {
            Core::Logger::LogError("Y size should be positive: " + __LOGERROR__);
            return;
        }

        _size = size;
    }

    GLFWwindow *Window::GetGLFWwindow() const {
        return _window;
    }

    void Window::ResizeRectangle(Rectangle& support, glm::vec2 newSize) {


    }

//=============================RECTANGLE SETTINGS=============================//

    Rectangle& Window::CreateRectangle(
            const glm::vec2& position,
            const glm::vec2& size) {

        if (position.x < 0) {
            Core::Logger::LogCritical("X position should be positive: " + __LOGERROR__);
            abort();
        }
        if (position.y < 0) {
            Core::Logger::LogCritical("Y position should be positive: " + __LOGERROR__);
            abort();
        }

        if (size.x <= 0) {
            Core::Logger::LogCritical("X size should be higher than zero: " + __LOGERROR__);
            abort();
        }
        if (size.y <= 0) {
            Core::Logger::LogCritical("Y size should be higher than zero: " + __LOGERROR__);
            abort();
        }

        if (position.x > 1) {
            Core::Logger::LogCritical("X position should be normalized: " + __LOGERROR__);
            abort();
        }
        if (position.y > 1) {
            Core::Logger::LogCritical("Y position should be normalized: " + __LOGERROR__);
            abort();
        }
        if (size.x > 1) {
            Core::Logger::LogCritical("X size should be normalized: " + __LOGERROR__);
            abort();
        }
        if (size.y > 1) {
            Core::Logger::LogCritical("Y size should be normalized: " + __LOGERROR__);
            abort();
        }

        _rectangles.emplace_back(std::unique_ptr<Rectangle>(new Rectangle(position, size)));

        return *_rectangles.back();
    }

    void Window::DestroyRectangle(const size_t index) {
        if (index >= _rectangles.size()) {
            Core::Logger::LogError("Index out of bounds: " + __LOGERROR__);
            return;
        }
    }

    Rectangle& Window::GetRectangle(size_t index) {
        if (index >= _rectangles.size()) {
            Core::Logger::LogCritical("Index out of bounds: " + __LOGERROR__);
            abort();
        }

        return *_rectangles[index];
    }

    glm::vec2 Window::GetRectangleSize(const size_t index) const {
        if (index >= _rectangles.size()) {
            Core::Logger::LogCritical("Index out of bounds: " + __LOGERROR__);
            return {0,0};
        }

        return _rectangles[index]->GetSize();
    }

    glm::vec2 Window::GetRectanglePosition(const size_t index) const {
        if (index >= _rectangles.size()) {
            Core::Logger::LogCritical("Index out of bounds: " + __LOGERROR__);
            return {0,0};
        }

        return _rectangles[index]->GetPosition();
    }

    bool Window::CheckRectangleExist(const size_t index) const {
        if (index >= _rectangles.size()) {
            return false;
        }
        return true;
    }
//=============================RECTANGLE SETTINGS=============================//
}
