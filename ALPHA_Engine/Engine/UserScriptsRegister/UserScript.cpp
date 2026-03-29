#include "UserScript.h"
#include "Registry.h"

#include "Core/Logger/Logger.h"

namespace Register {
	UserScript::UserScript() {
		Core::Logger::LogInfo("Creating new user script");
	}

	UserScript::~UserScript() {
		Core::Logger::LogInfo("Script deleted successfully");
	}


	void UserScript::Awake() {

	}
	void UserScript::Start() {

	}
	void UserScript::Update() {

	}
	void UserScript::End() {

	}
}