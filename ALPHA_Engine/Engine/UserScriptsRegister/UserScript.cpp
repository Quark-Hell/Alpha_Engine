#include "UserScript.h"
#include "BaseConfig.h"
#include "Registry.h"

#include "Logger/Logger.h"

Register::UserScript::UserScript() {
	Logger::Logger::LogInfo("Creating new user script");
	Registry::RegisterActorWithComponent(this);
}

Register::UserScript::~UserScript() {
	Logger::Logger::LogInfo("Script deleted successfully");
}


void Register::UserScript::Start()  {

}
void Register::UserScript::Update() {

}
void Register::UserScript::End() {

}
