#include "WindowsBuffer.h"
#include "WindowsManager/Window.h"

namespace WindowsManager {
    WindowsBuffer::WindowsBuffer() : Core::TSystemData<Window>("WindowsBuffer") {}

    Window* WindowsBuffer::CreateWindow(const int width, const int height, const std::string& title) {
        if (GetAllData().size() >= 1) {
            _data.emplace_back(std::unique_ptr<Window>
        (new Window(width,height, title,nullptr, GetData(0)._window)));

            Core::Logger::LogInfo("Created shared window");
        }
        else {
            _data.emplace_back(std::unique_ptr<Window>
        (new Window(width,height, title,nullptr,nullptr)));

            Core::Logger::LogInfo("Window created");
        }

        return _data.back().get();
    }

    Window *WindowsBuffer::GetFocusedWindow() const {
        return _focusedWindow;
    }
}