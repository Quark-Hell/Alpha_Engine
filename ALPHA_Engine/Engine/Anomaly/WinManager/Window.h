#pragma once

struct GLFWwindow;
struct GLFWmonitor;

namespace AnomalyEngine::Render {
    class Render;
}

namespace AnomalyEngine::WindowsManager {

class Window {
    friend class AnomalyEngine::Render::Render;

     private:
          GLFWwindow* _window;
          bool _isSync = true;

     public:
       Window() = delete;
       Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
       ~Window() = default;

       void Resize(int width, int height);
       void SetSync(bool sync);
};

}