#pragma once

#include "WindowsManager/Window.h"
#include "Core/ECS/TSystemData.h"

namespace WindowsManager {
    class WindowsBuffer final : public Core::TSystemData<Window> {
        friend class WindowsManager;
    private:
        Window* _focusedWindow = nullptr;

    public:
        WindowsBuffer();
        Window *CreateWindow(int width = 100, int height = 100, const std::string &title = "Window");

        [[nodiscard]] Window *GetFocusedWindow() const;

        ~WindowsBuffer() override = default;
    };
}