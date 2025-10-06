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

    void WindowsTest1(Core::Object& Player);
    void WindowsTest2(Core::Object& Player);
    void WindowsTest3(Core::Object& Player);
    void WindowsTest4(Core::Object& Player);

    void WindowsTest5(Core::Object& Player);

};
