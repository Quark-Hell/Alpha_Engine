// Game.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include "UserScriptsRegister/UserScriptConfig.h"

class MyScript : public Register::UserScript {

public:
	MyScript(enum Register::UserScriptType type) : Register::UserScript(type) {}

	void Start() override;
	void Update() override;
	void End() override;
};