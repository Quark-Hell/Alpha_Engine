#pragma once

#include <vector>

namespace Core {
    class GameObject;
}

namespace WindowsManager {
    class Window;
    class Rectangle;
}

class WindowsSettings {
public:
    WindowsManager::Window* win1 = nullptr;
    WindowsManager::Rectangle* rect = nullptr;

    std::vector<WindowsManager::Rectangle*> rects;

    void ShowCursor();
    void HideCursor();

    void BaseWindow(Core::GameObject& Player);

    void WindowsTest1(Core::GameObject& Player);
    void WindowsTest2(Core::GameObject& Player);
    void WindowsTest3(Core::GameObject& Player);
    void WindowsTest4(Core::GameObject& Player);

    void WindowsTest5(Core::GameObject& Player);

};
