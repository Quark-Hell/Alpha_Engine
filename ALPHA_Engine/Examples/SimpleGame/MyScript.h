#pragma once
#include "UserScriptsRegister/UserScriptConfig.h"

namespace WindowsManager {
	class Window;
}

class MyScript : public Register::UserScript {
	private:
	Core::Object* Player = nullptr;
	float moveSensitive = 10;

	WindowsManager::Window* win1 = nullptr;
	WindowsManager::Window* win2 = nullptr;

	WindowsManager::Window* win3 = nullptr;
	WindowsManager::Window* win4 = nullptr;

	public:
	MyScript() = default;

	void Start() override;
	void Update() override;
	void End() override;

	void Print();

    void CameraRotate();

	void LeftMoveCamera();
	void RightMoveCamera();
	void ForwardMoveCamera();
	void BackwardMoveCamera();
    void UpMoveCamera();
    void DownMoveCamera();

	void ShowCursor();
	void HideCursor();
};
