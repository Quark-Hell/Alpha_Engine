#include "WindowsBuffer.h"
#include "WindowsManager/Components/Window.h"

namespace WindowsManager {
    WindowsBuffer::WindowsBuffer(size_t initialBufferSize) : Core::TSystemData<Window>("WindowsBuffer", initialBufferSize) {}

    Window* WindowsBuffer::CreateWindow(const int width, const int height, const std::string& title) {
        if (GetAllData().size() >= 1) {
            _data.emplace_back(std::unique_ptr<Window>
        (new Window({static_cast<float>(width), static_cast<float>(height)}, title,nullptr, GetData(0)._window)));

            Core::Logger::LogInfo("Created shared window");
        }
        else {
            _data.emplace_back(std::unique_ptr<Window>
        (new Window({static_cast<float>(width), static_cast<float>(height)}, title,nullptr,nullptr)));

            Core::Logger::LogInfo("Window created");
        }

        return _data.back().get();
    }

    Window *WindowsBuffer::GetFocusedWindow() const {
        return _focusedWindow;
    }
}