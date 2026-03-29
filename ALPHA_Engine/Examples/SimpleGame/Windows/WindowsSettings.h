#pragma once

#include <vector>

#include "UserScriptsRegister/UserScriptConfig.h"
#include "Core/Serialization/TSerialized.h"

namespace Core {
    class GameObject;
}

namespace WindowsManager {
    class Window;
    class Rectangle;
}

class WindowsSettings  final : public Register::UserScript {
public:
    WindowsManager::Window* win1 = nullptr;
    WindowsManager::Rectangle* rect = nullptr;

    std::vector<WindowsManager::Rectangle*> rects;
    
public:
    void Awake() override;

    void ShowCursor();
    void HideCursor();

    void BaseWindow(Core::GameObject& Player);
};
