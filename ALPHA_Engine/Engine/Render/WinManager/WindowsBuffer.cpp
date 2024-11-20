#include "WindowsBuffer.h"
#include "Render/WinManager/Window.h"

namespace Render::WindowsManager {
    WindowsBuffer::WindowsBuffer() : Core::TSystemData<Window>("WindowsBuffer") {}

    WindowsBuffer* WindowsBuffer::GetInstance() {
        static WindowsBuffer buffer;
        return &buffer;
    }

    Window* WindowsBuffer::CreateWindow(const int width, const int height, const std::string& title) {
        const auto buffer = WindowsBuffer::GetInstance();

        if (buffer->GetAllData().size() >= 1) {
            buffer->_data.emplace_back(std::unique_ptr<Window>
        (new Window(width,height, title,nullptr, buffer->GetData(0)._window)));

            Logger::Logger::LogInfo("Created shared window");
        }
        else {
            buffer->_data.emplace_back(std::unique_ptr<Window>
        (new Window(width,height, title,nullptr,nullptr)));

            Logger::Logger::LogInfo("Window created");
        }

        return buffer->_data.back().get();
    }
}