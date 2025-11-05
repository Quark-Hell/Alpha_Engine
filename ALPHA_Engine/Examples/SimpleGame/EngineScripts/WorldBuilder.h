#pragma once

#include "UserScriptsRegister/UserScriptConfig.h"
#include "Core/Serialization/TSerialized.h"

class WorldBuilder final : public Register::UserScript {
public:
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