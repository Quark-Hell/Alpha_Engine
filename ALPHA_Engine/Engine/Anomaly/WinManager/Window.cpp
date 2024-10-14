#include "Window.h"
#include  <cassert>

#include <GLEW/glew.h>
#include <GL/gl.h>
#include "GLFW/glfw3.h"

namespace AnomalyEngine::WindowsManager {
    Window::Window(const int width, const int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {

        if (!glfwInit()) {
            glfwTerminate();
            assert("glfw do not init");
        }

        _window = glfwCreateWindow(width, height, title, monitor, share);
        if (_window == nullptr)
        {
            assert("Failed to create GLFW window");
            glfwTerminate();
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
    }

    void Window::Resize(int width, int height) {

    }
    void Window::SetSync(const bool sync) {
        _isSync = sync;

        glfwMakeContextCurrent(_window);
        if (_isSync == true) glfwSwapInterval(1);
        else glfwSwapInterval(0);
    }

}
