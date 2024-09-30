// Game.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "UserScriptsRegister/UserScriptConfig.h"

class MyScript : public Register::UserScript {

public:
	MyScript(enum Register::UserScriptType type) : Register::UserScript(type) {}
	//using Register::UserScript::UserScript;

	void Start() override;
	void Update() override;
	void End() override;
};

// TODO: Reference additional headers your program requires here.
