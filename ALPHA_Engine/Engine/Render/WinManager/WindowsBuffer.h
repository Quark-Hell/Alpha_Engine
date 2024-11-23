#pragma once

#include "Render/WinManager/Window.h"
#include "Core/ECS/TSystemData.h"

namespace Render::WindowsManager {
    class WindowsBuffer final : public Core::TSystemData<Window> {
        friend class WindowsManager;
        Window* _focusedWindow = nullptr;

    public:
        WindowsBuffer();
        Window *CreateWindow(int width = 100, int height = 100, const std::string &title = "Window");

        [[nodiscard]] Window *GetFocusedWindow() const;

        ~WindowsBuffer() override = default;
    };
}
