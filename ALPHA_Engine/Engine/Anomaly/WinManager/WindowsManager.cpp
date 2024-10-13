#include "WindowsManager.h"

namespace AnomalyEngine::WindowsManager {
    WindowsManager::WindowsManager() = default;
    WindowsManager::~WindowsManager() = default;

    WindowsManager& WindowsManager::GetInstance() {
        WindowsManager& WinMan = *(new WindowsManager());
        return WinMan;
    }
}