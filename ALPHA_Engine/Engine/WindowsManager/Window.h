#pragma once
#include <string>

struct GLFWwindow;
struct GLFWmonitor;

namespace WindowsManager {
    class Window {
        friend class WindowsManager;
        friend class WindowsBuffer;

    private:
        GLFWwindow *_window;

        int _width = 100;
        int _height = 100;

        std::string _title;

        bool _isSync = true;
        bool _isCursorVisible = true;

    private:
        Window(int width, int height, const std::string& title, GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr);

    public:
        Window() = delete;
        ~Window();

        void Resize(int width, int height);

        void SetSync(bool sync);

        bool GetCursorVisible();
        void SetCursorVisible(bool isVisible);

        GLFWwindow *GetGLFWwindow() const;
    };
}
