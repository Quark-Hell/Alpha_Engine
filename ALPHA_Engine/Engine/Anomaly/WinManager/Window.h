#pragma once

struct GLFWwindow;
struct GLFWmonitor;

namespace AnomalyEngine::Render {
    class Render;
    class Camera;
}

namespace AnomalyEngine::WindowsManager {

class Window {
    friend class AnomalyEngine::Render::Render;

     private:
        GLFWwindow* _window;
        AnomalyEngine::Render::Camera* _activeCamera;

        int _width = 100;
        int _height = 100;

        bool _isSync = true;
        bool _initialized = false;

        void Init();

     public:
        Window() = delete;
        Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
        ~Window() = default;

        void Resize(int width, int height);
        void SetSync(bool sync);

        void SetCamera(AnomalyEngine::Render::Camera* camera);
};

}