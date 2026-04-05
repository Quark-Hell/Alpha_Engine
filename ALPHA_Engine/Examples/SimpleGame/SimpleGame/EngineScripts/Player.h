#pragma once

#include "UserScriptsRegister/UserScriptConfig.h"
#include "Core/Serialization/TSerialized.h"

class Player final : public Register::UserScript {
private:
	float moveSensitive = 10;

	float targetYaw = 0.0f;
	float targetPitch = 0.0f;

public:
	Player() = default;

	void Start() override;
	void Update() override;
	void End() override;

	void CameraRotate();

	void LeftMoveCamera();
	void RightMoveCamera();
	void ForwardMoveCamera();
	void BackwardMoveCamera();
	void UpMoveCamera();
	void DownMoveCamera();
};