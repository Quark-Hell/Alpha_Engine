#include "WindowsSettings.h"

#include "Modules.h"

void WindowsSettings::ShowCursor() {
    win1->SetCursorVisible(true);
}

void WindowsSettings::HideCursor() {
    win1->SetCursorVisible(false);
}

void WindowsSettings::BaseWindow(Core::GameObject& Player) {
    auto& cam = camerasBuffer->CreateCamera();

    win1->CreateRectangle({ 0,0 }, { 1,1 });
    cam.SetRenderWindow(win1);
    cam.SetUseRectangle(true);
    cam.SetIndexRectangle(0);

    Player.AddComponent(cam);
}

void WindowsSettings::Awake() {
#if WINDOWS_MANAGER_INCLUDED
    const auto windowsBuffer = Core::World::GetSystemData<WindowsManager::WindowsBuffer>("WindowsBuffer");
    if (windowsBuffer == nullptr) {
        Core::Logger::LogError("Failed to get windows buffer: " + __LOGERROR__);
        return;
    }

    win1 = windowsBuffer->CreateWindow(1280, 720, "Windows 1");
    win1->SetCursorVisible(false);
#endif

#if BINDS_ENGINE_INCLUDED
    using namespace BindsEngine;

    auto* bindsBuffer = Core::World::GetSystemData<BindsBuffer>("BindsBuffer");
    if (bindsBuffer == nullptr) {
        Core::Logger::LogError("BindsBuffer does not exist: " + __LOGERROR__);
        return;
    }

    /*auto& showCursor =*/ bindsBuffer->CreateKeyboardBind(
        { std::bind(&WindowsSettings::ShowCursor, this) },
        { EnumKeyboardKeysStates::KeyPressed },
        { EnumKeyboardTable::LAlt },
        win1);

    /*auto& hideCursor =*/ bindsBuffer->CreateKeyboardBind(
        { std::bind(&WindowsSettings::HideCursor, this) },
        { EnumKeyboardKeysStates::KeyReleased },
        { EnumKeyboardTable::LAlt },
        win1
    );
#endif
}