#pragma once

#include "Render/WinManager/Window.h"
#include "Core/ECS/TSystemData.h"

namespace Render::WindowsManager {
    class WindowsBuffer final : public Core::TSystemData<Window> {
    private:
        WindowsBuffer();

    public:
        static WindowsBuffer *GetInstance();

        static Window *CreateWindow(int width = 100, int height = 100, const std::string &title = "Window");

        ~WindowsBuffer() override = default;
    };

    inline WindowsBuffer* windowsBuffer = WindowsBuffer::GetInstance();
}
