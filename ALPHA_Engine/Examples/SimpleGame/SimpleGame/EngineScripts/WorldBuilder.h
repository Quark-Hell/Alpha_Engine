#pragma once

#include "UserScriptsRegister/UserScriptConfig.h"
#include "Core/Serialization/TSerialized.h"

class WorldBuilder final : public Register::UserScript {
public:
	Core::GameObject* plane;

	WorldBuilder() = default;

	void Start() override;
	void Update() override;
	void End() override;

	void GenerateCubeMap();
	void GenerateLightSource();
	void GenerateEarth();
	void GenerateSun();
	void GenerateCube();
};